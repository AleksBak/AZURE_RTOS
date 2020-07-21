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
/**   Host Stack                                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_host_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_host_stack_hcd_thread_entry                     PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function is the entry point of the host controller thread.     */
/*    The HCD thread is initialized at the system level and the thread    */ 
/*    entry routine is invoked right away. This thread suspends until     */ 
/*    one of the HCD resumes it due to HCD activities.                    */
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    input                                 Not used input                */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_semaphore_get             Get signal semaphore          */ 
/*    (ux_hcd_entry_function)               HCD's entry function          */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    ThreadX                                                             */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
VOID  _ux_host_stack_hcd_thread_entry(ULONG input)
{

UINT        hcd_index;
UX_HCD      *hcd;
UX_INT_SAVE_AREA
    
    UX_PARAMETER_NOT_USED(input);

    /* Loop forever on the semaphore. The semaphore is used to signal that 
       there is work for one or more HCDs.  */     
    while (1)
    {   

        /* Get the semaphore that signals something is available for this
           thread to process.  */
        _ux_utility_semaphore_get(&_ux_system_host -> ux_system_host_hcd_semaphore, UX_WAIT_FOREVER);

        /* This thread was awaken by one or more HCD controllers. Check each of the HCDs 
           to see who posted work to do. */  
        for(hcd_index = 0; hcd_index < _ux_system_host -> ux_system_host_registered_hcd; hcd_index++)
        {

            /* Pickup HCD pointer.  */
            hcd =  &_ux_system_host -> ux_system_host_hcd_array[hcd_index];

            /* Is there work to do for this HCD?  */
            if((hcd -> ux_hcd_status == UX_HCD_STATUS_OPERATIONAL) && (hcd -> ux_hcd_thread_signal !=0))
            {

                /* Yes, call the HCD function to process the work.  */
                hcd -> ux_hcd_entry_function(hcd, UX_HCD_PROCESS_DONE_QUEUE, UX_NULL);
                UX_DISABLE_INTS
                hcd -> ux_hcd_thread_signal--;
                UX_RESTORE_INTS
            }               
        }
    }
}

