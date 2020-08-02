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
/*    _ux_hcd_stm32_asynch_schedule                       PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function schedules a new transfer from the control/bulk lists. */ 
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
UINT  _ux_hcd_stm32_asynch_schedule(UX_HCD_STM32 *hcd_stm32)
{

UX_HCD_STM32_ED       *ed;
UX_HCD_STM32_ED       *first_ed;
ULONG                 count_ed_scheduled;    

    /* Get the pointer to the current ED in the asynchronous list.  */
    ed =  hcd_stm32 -> ux_hcd_stm32_asynch_current_ed;

    /* Check if there is any eds candidate in the asynch list.  */
    if (ed == UX_NULL)
    {

        /* Check if there is any ED in the asynch list. If none, nothing to do.  */
        if (hcd_stm32 -> ux_hcd_stm32_asynch_head_ed == UX_NULL)
            return(UX_FALSE);
        else
            ed = hcd_stm32 -> ux_hcd_stm32_asynch_head_ed;
    }

    /* Remember this ED.  */
    first_ed =  ed;
    
    /*     Reset the count of scheduled EDs.  */
    count_ed_scheduled = 0;

    /* Parse the endpoint list in search for a transaction that needs to be posted. 
       we can from both the control list and the bulk list.  */
    do 
    {

        /* Ensure this ED does not have the SKIP bit set and no TD are in progress. */
        if ((ed -> ux_stm32_ed_head_td -> ux_stm32_td_status & UX_HCD_STM32_TD_ACK_PENDING) == 0)
        {

            /* Check if this ED has a tail and head TD different.  */
            if ((ed -> ux_stm32_ed_tail_td != ed -> ux_stm32_ed_head_td) && (ed -> ux_stm32_ed_status &  UX_HCD_STM32_ED_SKIP) == 0)
            {

                /* Keep the scheduler active.  */
                count_ed_scheduled++;

                /* Insert this transfer in the list of PTDs if possible.  */
                _ux_hcd_stm32_td_schedule(hcd_stm32, ed);
    
                /* If the TD has been added to the list, we can memorize this ED has 
                   being served and make the next ED as the one to be first scanned 
                   when this transaction is completed.  */
    
                if (ed -> ux_stm32_ed_next_ed == UX_NULL)
                    hcd_stm32 -> ux_hcd_stm32_asynch_current_ed =  hcd_stm32 -> ux_hcd_stm32_asynch_head_ed;
                else            
                    hcd_stm32 -> ux_hcd_stm32_asynch_current_ed =  ed -> ux_stm32_ed_next_ed;
            }
        }
        else
        {

            /* Keep the scheduler active to check pending status.  */
            count_ed_scheduled++;
        }

        /* Point to the next ED in the list. Check if at end of list.  */
        if (ed -> ux_stm32_ed_next_ed == UX_NULL)
            ed =  hcd_stm32 -> ux_hcd_stm32_asynch_head_ed;
        else            
            ed =  ed -> ux_stm32_ed_next_ed;

    } while (ed != first_ed);
    
    /*     Any ED scheduled or do we need to keep the scheduler running ?  */
    if (count_ed_scheduled == 0)
    
        /* It seems the scheduler is empty, so turn it off.  */
        hcd_stm32 -> ux_hcd_stm32_queue_empty =  UX_TRUE;

    /* We have not found anything to do.  */
    return(UX_FALSE);
}
