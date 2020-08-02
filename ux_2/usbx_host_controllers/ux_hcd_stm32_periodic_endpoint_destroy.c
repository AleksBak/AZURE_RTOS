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
/*    _ux_hcd_stm32_periodic_endpoint_destroy             PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*     This function will destroy an interrupt or isochronous endpoint.   */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                             Pointer to stm32 controller   */ 
/*    endpoint                              Pointer to endpoint           */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_delay_ms                  Delay ms                      */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    stm32 Controller Driver                                             */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_hcd_stm32_periodic_endpoint_destroy(UX_HCD_STM32 *hcd_stm32, UX_ENDPOINT *endpoint)
{

UX_HCD_STM32_ED      *ed;
UX_HCD_STM32_ED      *previous_ed;
UX_HCD_STM32_ED      *next_ed;
UX_HCD_STM32_TD      *tail_td;
UX_HCD_STM32_TD      *head_td;

    
    /* From the endpoint container fetch the stm32 ED descriptor.  */
    ed =  (UX_HCD_STM32_ED*) endpoint -> ux_endpoint_ed;

    /* Check if this physical endpoint has been initialized properly!  */
    if (ed == UX_NULL)
    {

        /* Error trap. */
        _ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD, UX_SYSTEM_CONTEXT_HCD, UX_ENDPOINT_HANDLE_UNKNOWN);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_ENDPOINT_HANDLE_UNKNOWN, endpoint, 0, 0, UX_TRACE_ERRORS, 0, 0)

        return(UX_ENDPOINT_HANDLE_UNKNOWN);
    }

    /* The endpoint may be active. If so, set the skip bit.  */
    ed -> ux_stm32_ed_status |=  UX_HCD_STM32_ED_SKIP;
    
    /* Wait for the controller to finish the current frame processing.  */
    _ux_utility_delay_ms(1);

    /* Get the previous ED in the list for this ED.  */
    previous_ed =  ed -> ux_stm32_ed_previous_ed;

    /* Get the next ED in the list for this ED.  */
    next_ed =  ed -> ux_stm32_ed_next_ed;

    /* The previous ED points now to the ED after the ED we are removing.  */
    previous_ed -> ux_stm32_ed_next_ed =  next_ed;

    /* There may not be any next endpoint.  But if there is one, link it
       to the previous ED. */
    if (next_ed != UX_NULL)
    
        /* Update the previous ED pointer in the next ED.  */
        next_ed -> ux_stm32_ed_previous_ed =  previous_ed;

    /* Remove all the tds from this ED and leave the head and tail pointing to the dummy TD.  */
    head_td =  ed -> ux_stm32_ed_head_td;
    tail_td =  ed -> ux_stm32_ed_tail_td;

    /* Free all tds attached to the ED.  */
    while (head_td != tail_td)
    {

        /* Mark the current head TD as free. */
        head_td -> ux_stm32_td_status =  UX_UNUSED;

        /* Update the head TD with the next TD.  */
        ed -> ux_stm32_ed_head_td =  head_td -> ux_stm32_td_next_td;

        /* Now the new head_td is the next TD in the chain.  */
        head_td =  ed -> ux_stm32_ed_head_td;
    }

    /* We need to free the dummy TD that was attached to the ED.  */
    tail_td -> ux_stm32_td_status =  UX_UNUSED;

    /* We need to free the channel.  */
    hcd_stm32 -> ux_hcd_stm32_channels_ed[ed -> ux_stm32_ed_channel] =  UX_NULL;
    
    /* Now we can safely make the ED free.  */
    ed -> ux_stm32_ed_status =  UX_UNUSED;

    /* Decrement the number of interrupt endpoints active. When the counter
       reaches 0, the periodic scheduler will be turned off.  */
    hcd_stm32 -> ux_hcd_stm32_periodic_scheduler_active--;

    /* Return successful completion.  */
    return(UX_SUCCESS);         
}

