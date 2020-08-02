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
/*    _ux_hcd_stm32_interrupt_endpoint_create             PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function will create an interrupt endpoint. The interrupt      */ 
/*    endpoint has an interval of operation from 1 to 255. The STM32      */
/*    has no hardware scheduler but we still build an interrupt tree      */ 
/*    similar to the OHCI controller.                                     */
/*                                                                        */
/*    This routine will match the best interval for the STM32             */ 
/*    hardware. It will also determine the best node to hook the          */ 
/*    endpoint based on the load that already exists on the horizontal    */ 
/*    ED chain.                                                           */
/*                                                                        */
/*    For the ones curious about this coding. The tricky part is to       */
/*    understand how the interrupt matrix is constructed. We have used    */ 
/*    eds with the skip bit on to build a frame of anchor eds. Each ED    */ 
/*    creates a node for an appropriate combination of interval frequency */ 
/*    in the list.                                                        */ 
/*                                                                        */
/*    After obtaining a pointer to the list with the lowest traffic, we   */
/*    traverse the list from the highest interval until we reach the      */ 
/*    interval required. At that node, we anchor our real ED to the node  */ 
/*    and link the ED that was attached to the node to our ED.            */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                             Pointer to STM32 Controller   */ 
/*    endpoint                              Pointer to endpoint           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_ed_obtain               Obtain ED                     */ 
/*    _ux_hcd_stm32_regular_td_obtain       Obtain regular TD             */ 
/*    _ux_hcd_stm32_least_traffic_list_get  Get least traffic list        */ 
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
UINT  _ux_hcd_stm32_interrupt_endpoint_create(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint)
{

UX_HCD_STM32_ED     *ed;
UX_HCD_STM32_ED     *ed_list;
UX_HCD_STM32_ED     *next_ed;
UX_HCD_STM32_TD     *td;
UX_DEVICE           *device;
UINT                interval;
UINT                interval_index;
UINT                interval_stm32;
ULONG                channel_index;
ULONG                stm32_channel_register;

    /* Get the pointer to the device.  */
    device =  endpoint -> ux_endpoint_device;

    /* Obtain a ED for this new endpoint. This ED will live as long as
       the endpoint is active and will be the container for the tds.  */
    ed =  _ux_hcd_stm32_ed_obtain(hcd_stm32);
    if (ed == UX_NULL)
        return(UX_NO_ED_AVAILABLE);

    /* Obtain a dummy TD for terminating the ED transfer chain.  */
    td =  _ux_hcd_stm32_regular_td_obtain(hcd_stm32);
    if (td == UX_NULL)
    {

        ed -> ux_stm32_ed_status =  UX_UNUSED;
        return(UX_NO_TD_AVAILABLE);
    }

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

    /* Attach the ED to the endpoint container.  */
    endpoint -> ux_endpoint_ed =  (VOID *)ed;
    
    /* Now do the opposite, attach the ED container to the physical ED.  */
    ed -> ux_stm32_ed_endpoint =  endpoint;

    /* Hook the TD to both the tail and head of the ED.  */
    ed -> ux_stm32_ed_tail_td =  td;
    ed -> ux_stm32_ed_head_td =  td;

    /* Get the list index with the least traffic.  */
    ed_list =  _ux_hcd_stm32_least_traffic_list_get(hcd_stm32);
    
    /* Get the interval for the endpoint and match it to a STM32 list. We match anything 
       that is > 32ms to the 32ms interval list, the 32ms list is list 0, 16ms list is 1...
       the 1ms list is number 5.  */
    interval =          endpoint -> ux_endpoint_descriptor.bInterval;
    interval_index =  0x10;
    interval_stm32 =   1;

    /* Do a sanity check if the frequency is 0. That should not happen, so treat it as 1.  */
    if (interval == 0)
    {

        interval =  1;
    }

    /* If the frequency is beyond 32,  make it the maximum of 32.  */
    if (interval >= 32)
    {

        interval_stm32 =  0;
    }
    else
    {

        /* We parse the interval from the high bits. This gives us the first power of 2 entry in the tree.  */
        while (interval_index != 0)
        {

            /* When we find the first bit of the interval the current value of interval_stm32 is set to the the list index.  */
            if (interval & interval_index)
                break;
                
            /* Go down the tree one entry.  */
            interval_stm32++;
            
            /* And shift the bit of the device interval to check.  */
            interval_index =  interval_index >> 1;
        }
    }


    /* Now we need to scan the list of eds from the lowest load entry until we reach 
       the appropriate interval node. The depth index is the interval_stm32 value 
       and the 1st entry is pointed by the ED list entry.  */
    while (interval_stm32--)
    {

        ed_list =  ed_list -> ux_stm32_ed_next_ed;
        while (!(ed_list -> ux_stm32_ed_status & UX_HCD_STM32_ED_STATIC))
            ed_list =  ed_list -> ux_stm32_ed_next_ed;
    }       

    /* We found the node entry of the ED pointer that will be the anchor for this interrupt 
       endpoint. Now we attach this endpoint to the anchor and rebuild the chain .  */
    next_ed =                               ed_list -> ux_stm32_ed_next_ed;

    /* Check for end of tree which happens for devices with interval of 1. In this case
       there might not be a next_ed.  */
    if (next_ed != UX_NULL)
        next_ed -> ux_stm32_ed_previous_ed =  ed;

    ed -> ux_stm32_ed_next_ed =           next_ed;
    ed -> ux_stm32_ed_previous_ed =       ed_list;
    ed_list -> ux_stm32_ed_next_ed =      ed;

    /* Set the host channel characteristics register.  Device address
       is now set at zero. */
    stm32_channel_register = 0;
    
    /* Set the INTERRUPT Endpoint type.  */
    stm32_channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_EPTYP_INTERRUPT;

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
    
    /* There is activity in the periodic tree, the scheduler has to be active all the time.  */
    hcd_stm32 -> ux_hcd_stm32_periodic_scheduler_active++;

    /* Return successful completion.  */
    return(UX_SUCCESS);         
}

