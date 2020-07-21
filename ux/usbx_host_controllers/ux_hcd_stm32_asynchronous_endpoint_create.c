/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   STM32 Controller Driver                                             */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_hcd_stm32.h"
#include "ux_host_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_asynchronous_endpoint_create          PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function will create an asynchronous endpoint. The control     */
/*    and bulk endpoints fall into this category.                         */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                               Pointer to STM32 controller */ 
/*    endpoint                                Pointer to endpoint         */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_ed_obtain                 Obtain STM32 ED             */ 
/*    _ux_hcd_stm32_regular_td_obtain         Obtain STM32 regular TD     */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    STM32 Controller Driver                                             */
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_hcd_stm32_asynchronous_endpoint_create(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint)
{

UX_HCD                    *hcd;
UX_HCD_STM32_ED           *ed;
UX_HCD_STM32_ED           *head_ed;
UX_HCD_STM32_TD           *td;
UX_DEVICE               *device;
ULONG                    stm32_channel_register;
ULONG                    channel_index;

    /* Get pointer to generic controller.  */
    hcd = hcd_stm32 -> ux_hcd_stm32_hcd_owner;
    
    /* We need to take into account the nature of the HCD to define the max size
       of any transfer in the transfer request.  */
    if (hcd -> ux_hcd_controller_type ==  UX_HCD_STM32_CONTROLLER_HS)
    
        /* Set HS MAX PAYLOAD.  */
        endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length =  UX_HCD_STM32_HS_MAX_PAYLOAD;

    else
    
        /* Set FS MAX PAYLOAD.  */
        endpoint -> ux_endpoint_transfer_request.ux_transfer_request_maximum_length =  UX_HCD_STM32_FS_MAX_PAYLOAD;

    
    /* Get the pointer to the device.  */
    device =  endpoint -> ux_endpoint_device;

    /* Obtain a ED for this new endpoint. This ED will live as long as the endpoint is active 
       and will be the container for the tds.  */
    ed =  _ux_hcd_stm32_ed_obtain(hcd_stm32);
    if (ed == UX_NULL)
        return(UX_NO_ED_AVAILABLE);

    /* And get a channel. */
    for (channel_index = 0; channel_index < hcd_stm32 -> ux_hcd_stm32_nb_channels; channel_index++)
    {

        /* Check if that Channel is free.  */
        if (hcd_stm32 -> ux_hcd_stm32_channels_ed[channel_index]  == UX_NULL)
        {
    
            /* We have a channel. Save it. */
            hcd_stm32 -> ux_hcd_stm32_channels_ed[channel_index] = ed;
            
            /* And in the endpoint too. */
            ed -> ux_stm32_ed_channel = channel_index;
            
            /* Done here.  */
            break;

        }
    }
    
    /* Check for channel assignment.  */
    if (ed -> ux_stm32_ed_channel ==  UX_HCD_STM32_NO_CHANNEL_ASSIGNED)

        /* Could not allocate a channel.  */
        return(UX_NO_ED_AVAILABLE);
            
    /* Reset the channel to halted.  */
    ed -> ux_stm32_ed_channel_status = UX_HCD_STM32_ED_CHANNEL_RESET;

    /* Obtain a dummy TD for terminating the ED transfer chain.  */
    td =  _ux_hcd_stm32_regular_td_obtain(hcd_stm32);
    if (td == UX_NULL)
    {

        ed -> ux_stm32_ed_status =  UX_UNUSED;
        return(UX_NO_TD_AVAILABLE);
    }

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *) ed;

    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_stm32_ed_endpoint =  endpoint;
    
    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_stm32_ed_tail_td =  td;
    ed -> ux_stm32_ed_head_td =  td;
    
    /* Attach this ED to the asynch list.  */
    head_ed =  hcd_stm32 -> ux_hcd_stm32_asynch_head_ed;
    ed -> ux_stm32_ed_next_ed =  head_ed;
    hcd_stm32 -> ux_hcd_stm32_asynch_head_ed =  ed;

    /* Build the back chaining pointer. The previous head ED needs to know about the
       inserted ED. */
    if (head_ed != UX_NULL)
        head_ed -> ux_stm32_ed_previous_ed =  ed;

    /* Set the host channel characteristics register.  Device address
       is now set at zero. */
    stm32_channel_register = 0;
    
    /* Set the EPTYP field.  Control or bulk.  Default is Control.  */
    if ((endpoint -> ux_endpoint_descriptor.bmAttributes & UX_MASK_ENDPOINT_TYPE) == UX_BULK_ENDPOINT)

        /* Set the BULK Endpoint type.  */
        stm32_channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_BULK;

    /* Check if this is a Low Speed device. */
    if (device -> ux_device_speed == UX_LOW_SPEED_DEVICE)
    
        /* Set the LSDEV flag.  */
        stm32_channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_LSDEV;

    /* Set the device address.  */
    stm32_channel_register |=  device -> ux_device_address << UX_HCD_STM32_OTG_FS_HCCHAR_DAD_SHIFT;

    /* Set the endpoint number.  */
    stm32_channel_register |=  (endpoint -> ux_endpoint_descriptor.bEndpointAddress & ~UX_ENDPOINT_DIRECTION) << UX_HCD_STM32_OTG_FS_HCCHAR_EPNUM_SHIFT;
    
       /* Set the MaxPacketSize MPSIZ field.  */
    stm32_channel_register |=  endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Set the endpoint direction.  Default is OUT.  */
    if ((endpoint -> ux_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION) == UX_ENDPOINT_IN)
    
        /* Endpoint is IN.  */
        stm32_channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_EPDIR_IN;  
    
    /* Write the channel register.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), stm32_channel_register);                    

    /* Enable the Host channel interrupt mask register.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCINTMSK + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), UX_HCD_STM32_OTG_FS_HCINT_DEFAULT);                    

    /* Enable the interrupt for this channel.  */
    _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_HAINTMSK, 1 << ed -> ux_stm32_ed_channel);                    
    

    /* Return successful completion.  */
    return(UX_SUCCESS);         
}

