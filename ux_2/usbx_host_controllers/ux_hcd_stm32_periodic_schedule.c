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
/*    _ux_hcd_stm32_periodic_schedule                     PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*     This function schedules new transfers from the periodic interrupt  */ 
/*     list.                                                              */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                           Pointer to STM32 controller     */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    TRUE or FALSE                                                       */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_frame_number_get      Get frame number                */ 
/*    _ux_hcd_stm32_td_schedule           Insert TD into list             */ 
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
UINT  _ux_hcd_stm32_periodic_schedule(UX_HCD_STM32 *hcd_stm32)
{

UX_HCD_STM32_ED     *ed;
ULONG               frame_number;

    /* Get the current frame number.  */
    _ux_hcd_stm32_frame_number_get(hcd_stm32, &frame_number);
    
    /* Isolate the low bits to match an entry in the upper periodic entry list.  */
    frame_number &=  UX_HCD_STM32_PERIODIC_ENTRY_MASK;

    /* Get the first ED in the periodic list.  */
    ed =  hcd_stm32 -> ux_hcd_stm32_interrupt_ed_list[frame_number];

    /* Search for an entry in the periodic tree.  */
    while (ed != UX_NULL) 
    {

        /* Ensure this ED does not have the SKIP bit set and no TD are in progress. */
        if ((ed -> ux_stm32_ed_head_td -> ux_stm32_td_status & UX_HCD_STM32_TD_ACK_PENDING) == 0)
        {

            /* The ED has to be a real ED (not static) and has to have a different tail and head TD.  */
            if ((ed -> ux_stm32_ed_status != UX_HCD_STM32_ED_STATIC) && (ed -> ux_stm32_ed_tail_td != ed -> ux_stm32_ed_head_td))
            {

                    /* Insert this transfer in the list of scheduled TDs if possible.  */
                    _ux_hcd_stm32_td_schedule(hcd_stm32, ed);
            }
        }

        /* Point to the next ED in the list.  */
        ed =  ed -> ux_stm32_ed_next_ed;
    }

    /* Return to caller.  */
    return(UX_FALSE);
}

