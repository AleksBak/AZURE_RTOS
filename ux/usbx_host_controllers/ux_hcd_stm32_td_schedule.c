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
/*    _ux_hcd_stm32_td_schedule                           PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function schedules a new TD.                                   */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                           Pointer to STM32 controller     */ 
/*    ed                                  ed to be scheduled              */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    status                                                              */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
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
UINT  _ux_hcd_stm32_td_schedule(UX_HCD_STM32 *hcd_stm32, UX_HCD_STM32_ED *ed)
{


UX_HCD_STM32_TD     *td;
UX_ENDPOINT         *endpoint;
UX_DEVICE           *device;
ULONG                stm32_hctsiz_register;
ULONG                number_packets;
ULONG                stm32_channel_register;
ULONG                dword_count;
UCHAR                *buffer;
ULONG                toggle;
UX_INT_SAVE_AREA

    /* Get the pointer to the endpoint.  */
    endpoint =  ed -> ux_stm32_ed_endpoint;

    /* Get the pointer to the device.  */
    device =  endpoint -> ux_endpoint_device;

    /* Get the pointer to the candidate TD.  */
    td =  ed -> ux_stm32_ed_head_td;
    
    /* Set TD into response pending state. */
    UX_DISABLE_INTS
    td -> ux_stm32_td_status |=  UX_HCD_STM32_TD_ACK_PENDING;

    /* Reset NAK count.  */
    ed -> ux_stm32_ed_nak_counter = 0;

    /* Reset the actual length.  */
    td -> ux_stm32_td_actual_length = 0;
    UX_RESTORE_INTS

    /* Set the transfer size for the transaction.  */
    stm32_hctsiz_register = td -> ux_stm32_td_length;

    /* Calculate the number of packets.  Isolate for ZLP. */
    if (td -> ux_stm32_td_length != 0)

        /* Number of packets = transfer length / max packet count rounded to the
           next pack if necessary.  */
        number_packets =  (td -> ux_stm32_td_length + endpoint -> ux_endpoint_descriptor.wMaxPacketSize - 1) / endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    else
    
        /* ZLP transfer. Make it one packet only.  */
        number_packets =  1;

    /* Check the transfer direction. For IN transfers, we program the maximum transfer.  */    
    if (td -> ux_stm32_td_direction == UX_HCD_STM32_TD_IN)

        /* Transfer is IN.  */
        stm32_hctsiz_register = number_packets * endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Add the Number of packets.  */
    stm32_hctsiz_register |=  (number_packets << UX_HCD_STM32_OTG_FS_HCTSIZ_PKTCNT_SHIFT);

    /* Identify the PID for this transaction.  */
    if (td -> ux_stm32_td_status & UX_HCD_STM32_TD_SETUP_PHASE)
        
        /* PID is SETUP.  */
        stm32_hctsiz_register |=  UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_SETUP ;
            
    /* Find the toggle, the toggle may be coming from the ED.  */
    if (td -> ux_stm32_td_toggle & UX_HCD_STM32_TD_TOGGLE_FROM_ED)

        toggle =  ed -> ux_stm32_ed_toggle & 1;
    else

        toggle =  td -> ux_stm32_td_toggle & 1;


    /* Check value of Data Toggle : DATA0 or DATA1. */
    if (toggle != 0)

        /* Set the PID to DATA1.  */
        stm32_hctsiz_register |=  UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA1;

    /* Store the HCTSIZ register.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCTSIZ + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), stm32_hctsiz_register);                    
    
    /* Read the Channel register.  */
    stm32_channel_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    
    
    /* Enable Channel.  */
    stm32_channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_CHENA;
    
    /* Clear the Channel disable flag.  */
    stm32_channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS;
                
    /* Check the transfer direction. For IN transfers, we program the direction bit.  */    
    if (td -> ux_stm32_td_direction == UX_HCD_STM32_TD_IN)
    
        /* Set the DIR bit for IN.  */
        stm32_channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_EPDIR_IN;

    else
    
        /* Reset the DIR bit for out, it could have been set during the previous transaction.  */
        stm32_channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_EPDIR_IN;

    /* Set the device address which can change after the SET_ADDRESS command for control endpoint.  */
    stm32_channel_register |=  device -> ux_device_address << UX_HCD_STM32_OTG_FS_HCCHAR_DAD_SHIFT;

    /* Set the Max Packet Size which can also change when the Device descriptor is read the first time.  */
    stm32_channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_MPSIZ_MASK;
    stm32_channel_register |=  endpoint -> ux_endpoint_descriptor.wMaxPacketSize;

    /* Set the host channel characteristics register to enable the channel. */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), stm32_channel_register);                    

    /* If the transfer is OUT and not a ZLP, push the buffer into the appropriate FIFO.  */
    if ((td -> ux_stm32_td_direction == UX_HCD_STM32_TD_OUT) &&
        (td -> ux_stm32_td_length != 0))
    {
    
        /* Calculate the DWORD count to transmit to DWORD aligned FIFO.  */
        dword_count =  (td -> ux_stm32_td_length + 3) / sizeof(ULONG);
    
        /* Get the beginning of the transfer buffer.  */
        buffer =  td -> ux_stm32_td_buffer;
        
        /* Transfer a dword at a time.  */
        while (dword_count-- != 0)
        {

            /* Write a DWORD from the transaction buffer.  */                
            _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_FIFO + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_FIFO_CHANNEL_SIZE), 
                                _ux_utility_long_get(buffer));                    
            
            /* Point to the next DWORD.  */
            buffer += sizeof(ULONG);

        }
    }        

    /* Save the ed being scheduled now.  We will need it when the transaction
       is completed.  */
    hcd_stm32 -> ux_hcd_stm32_scheduled_ed =  ed;
    
    /* We have completed the schedule.  */
    return(UX_SUCCESS);
}

