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
/*    _ux_hcd_stm32_frame_number_get                      PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function will return the frame number currently used by the    */
/*    controller. This function is mostly used for isochronous purposes.  */ 
/*                                                                        */
/*    Note since ThreadX delay is used, the function must not be used in  */
/*    interrupts.                                                         */
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                             Pointer to STM32 controller   */ 
/*    frame_number                          Frame number to set           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
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
UINT  _ux_hcd_stm32_frame_number_get(UX_HCD_STM32 *hcd_stm32, ULONG *frame_number)
{
    
ULONG    port_status;

    /* Check the port status. If the port is not enabled, the SOF value is meaningless.  */
    port_status =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT);

    /* Check Port status enabled bit.  */
    if (port_status & UX_HCD_STM32_OTG_FS_HPRT_PENA)    
    {

        /* Save the frame # in the controller structure.  */
        hcd_stm32 -> ux_hcd_stm32_frame_number = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HFNUM) & UX_HCD_STM32_OTG_FS_HFNUM_FRNUM_MASK; 

        /* Return the frame number.  */
        *frame_number =  hcd_stm32 -> ux_hcd_stm32_frame_number;

    }
    else
    {

        /* We come here when the port is not enabled and the frame # is not incrementing every ms.
           So we wait for 1ms with the delay function.  */
        _ux_utility_delay_ms(1);
           
        /* Save the frame # in the controller structure.  */
        hcd_stm32 -> ux_hcd_stm32_frame_number++;

        /* Return the frame number.  */
        *frame_number =  hcd_stm32 -> ux_hcd_stm32_frame_number;

    }
    
    return(UX_SUCCESS);
}

