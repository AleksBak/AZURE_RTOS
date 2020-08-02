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
/*    _ux_hcd_stm32_request_interrupt_transfer            PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*     This function performs an interrupt transfer request. An interrupt */ 
/*     transfer can only be as large as the MaxpacketField in the         */ 
/*     endpoint descriptor. This was verified at the USB layer and does   */ 
/*     not need to be reverified here.                                    */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                             Pointer to STM32 controller   */ 
/*    transfer_request                      Pointer to transfer request   */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_regular_td_obtain       Obtain regular TD             */ 
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
UINT  _ux_hcd_stm32_request_interrupt_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request)
{

UX_ENDPOINT             *endpoint;
UX_HCD_STM32_ED           *ed;
UX_HCD_STM32_TD           *data_td;
UX_HCD_STM32_TD           *tail_td;
    
    /* Get the pointer to the Endpoint.  */
    endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;

    /* Now get the physical ED attached to this endpoint.  */
    ed =  endpoint -> ux_endpoint_ed;

    /* The endpoint may be active. If so, set the skip bit.  */
    ed -> ux_stm32_ed_status |=  UX_HCD_STM32_ED_SKIP;

    /* Reset the error retry count.  */
    ed -> ux_stm32_ed_command_retry =  0;

    /* Use the TD pointer by ed -> tail for the first TD of this transfer
        and chain from this one on.  */
    data_td =  ed -> ux_stm32_ed_tail_td;

    /* Set the direction of the transfer.  */
    if ((transfer_request -> ux_transfer_request_type & UX_REQUEST_DIRECTION) == UX_REQUEST_IN)
        data_td -> ux_stm32_td_direction =  UX_HCD_STM32_TD_IN;
    else
        data_td -> ux_stm32_td_direction =  UX_HCD_STM32_TD_OUT;

    /* Mark the TD with the DATA phase.  */
    data_td -> ux_stm32_td_status |=  UX_HCD_STM32_TD_DATA_PHASE;

    /* The Toggle value is in the ED.  */
    data_td -> ux_stm32_td_toggle =  UX_HCD_STM32_TD_TOGGLE_FROM_ED;

    /* Store the beginning of the buffer address in the TD.  */
    data_td -> ux_stm32_td_buffer =  transfer_request -> ux_transfer_request_data_pointer;

    /* Update the length of the transfer for this TD.  */
    data_td -> ux_stm32_td_length =  transfer_request -> ux_transfer_request_requested_length;

    /* Attach the endpoint and transfer request to the TD.  */
    data_td -> ux_stm32_td_transfer_request =  transfer_request;
    data_td -> ux_stm32_td_ed =  ed;

    /* At this stage, the Head and Tail in the ED are still the same and
       the STM32 controller will skip this ED until we have hooked the new
       tail TD.  */
    tail_td =  _ux_hcd_stm32_regular_td_obtain(hcd_stm32);
    if (tail_td == UX_NULL)
    {

        /* Clear the skip bit.  */
        ed -> ux_stm32_ed_status &= ~UX_HCD_STM32_ED_SKIP;

        return(UX_NO_TD_AVAILABLE);
    }

    /* Attach the tail TD to the last data TD.  */
    data_td -> ux_stm32_td_next_td =  tail_td;

    /* Store the new tail TD.  */
    ed -> ux_stm32_ed_tail_td =  tail_td;

    /* Clear the skip bit.  */
    ed -> ux_stm32_ed_status &= ~UX_HCD_STM32_ED_SKIP;

    /* Now we can tell the scheduler to wake up.  */
    hcd_stm32 -> ux_hcd_stm32_queue_empty =  UX_FALSE;

    /* There is no need to wake up the stm32 controller on this transfer
       since periodic transactions will be picked up when the interrupt
       tree is scanned.  */
    return(UX_SUCCESS);           
}

