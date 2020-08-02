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
/*    _ux_hcd_stm32_channel_halt                          PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function halts a channel.                                      */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                           Pointer to STM32 controller     */ 
/*    ed                                  ED to be halted.                */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
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
VOID  _ux_hcd_stm32_channel_halt(UX_HCD_STM32 *hcd_stm32, UX_HCD_STM32_ED *ed)
{

UX_ENDPOINT         *endpoint;
ULONG                channel_register;
ULONG                gnptxsts_register;
ULONG                hptxsts_register;
        
    /* Get the endpoint container.  */
    endpoint =  ed -> ux_stm32_ed_endpoint;
    
    /* Read the channel register. */
    channel_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                            (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    
    
    /* Set the Disable bit.  */
    channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS;
    
    /* Set Channel enabled bit to restart the transfer.  */
    channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_CHENA;
                
    /* Check for space in the request queue to issue the halt. */
    /* Check the type of endpoint. Interrupt and Bulk/Control are treated differently.  */
    switch (endpoint -> ux_endpoint_descriptor.bmAttributes & UX_MASK_ENDPOINT_TYPE)
    {

        case UX_CONTROL_ENDPOINT    :
        case UX_BULK_ENDPOINT        :

            /* Read the non periodic transmit FIFO/Queue register. */
            gnptxsts_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_GNPTXSTS);

            /* Check if the queue is full or not.  */
            if ((gnptxsts_register & UX_HCD_STM32_OTG_FS_GNPTXSTS_NPTQFSAV_MASK) == 0)

                /* Queue full. Reset Channel enabled bit.  */
                channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_CHENA;

            break;    

        case UX_INTERRUPT_ENDPOINT    :

            /* Read the periodic transmit FIFO/Queue register. */
            hptxsts_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HPTXSTS);

            /* Check if the queue is full or not.  */
            if ((hptxsts_register & UX_HCD_STM32_OTG_FS_HPTXSTS_PTQFSAV_MASK) == 0)

                /* Queue full. Reset Channel enabled bit.  */
                channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_CHENA;

            break;    

    
    }

    /* Save the channel register.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), channel_register);                    
    
    /* Set the channel to halted.  */
    ed -> ux_stm32_ed_channel_status = UX_HCD_STM32_ED_CHANNEL_HALTED;
    
    /* Return to caller.  */
    return;
}

