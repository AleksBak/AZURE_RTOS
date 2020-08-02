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
/*    _ux_hcd_stm32_request_bulk_transfer                 PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*     This function performs a bulk transfer request. A bulk transfer    */ 
/*     can be larger than the size of the stm32 buffer so it may be       */ 
/*     required to chain multiple tds to accommodate this transfer        */ 
/*     request. A bulk transfer is non blocking, so we return before the  */ 
/*     transfer request is completed.                                     */ 
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
/*    _ux_hcd_stm32_regular_td_obtain     Obtain regular TD               */ 
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
UINT  _ux_hcd_stm32_request_bulk_transfer(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request)
{

UX_ENDPOINT         *endpoint;
UX_HCD_STM32_TD     *data_td;
UX_HCD_STM32_TD     *start_data_td;
UX_HCD_STM32_TD     *next_data_td;
UX_HCD_STM32_TD     *previous_td;
UX_HCD_STM32_TD     *tail_td;
UX_HCD_STM32_ED     *ed;
ULONG               transfer_request_payload_length;
ULONG               bulk_packet_payload_length;
UCHAR                 *data_pointer;
ULONG               zlp_flag;
    
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
    previous_td =  data_td;

    /* Reset the first obtained data TD in case there is a TD shortage while building 
       the list of tds.  */
    start_data_td =  0;

    /* It may take more than one TD if the transfer_request length is more than the
       maximum length of the endpoint. */
    transfer_request_payload_length =  transfer_request -> ux_transfer_request_requested_length;
    data_pointer =  transfer_request -> ux_transfer_request_data_pointer;
    
    /* Check for ZLP condition.  */
    if (transfer_request_payload_length == 0)
        
        /* We have a zlp condition.  */
        zlp_flag = UX_TRUE;
    else
    
        /* We do not have a zlp.  */
        zlp_flag = UX_FALSE;
                
    /* Build all necessary TDs.  */
    while ((transfer_request_payload_length != 0) || zlp_flag == UX_TRUE)
    {

        /* Reset ZLP now.  */
        zlp_flag = UX_FALSE;        
      
        /* Do we have a full packet ?  */
        if (transfer_request_payload_length > ed -> ux_stm32_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize)


            /* Yes, use MaxPacketSize.  */
            bulk_packet_payload_length =  ed -> ux_stm32_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize;
        else

            /* No, use whatever is left to transmit/receive.  */
            bulk_packet_payload_length =  transfer_request_payload_length;

        /* Store the beginning of the buffer address in the TD.  */
        data_td -> ux_stm32_td_buffer =  data_pointer;

        /* Update the length of the transfer for this TD.  */
        data_td -> ux_stm32_td_length =  bulk_packet_payload_length;

        /* Attach the endpoint and transfer_request to the TD.  */
        data_td -> ux_stm32_td_transfer_request =  transfer_request;
        data_td -> ux_stm32_td_ed =  ed;

        /* Adjust the data payload length and the data payload pointer.  */
        transfer_request_payload_length -=  bulk_packet_payload_length;
        data_pointer +=  bulk_packet_payload_length;

        /* The direction of the transaction is set in the TD.  */
        if ((transfer_request -> ux_transfer_request_type & UX_REQUEST_DIRECTION) == UX_REQUEST_IN)

            data_td -> ux_stm32_td_direction =  UX_HCD_STM32_TD_IN;
        else
            data_td -> ux_stm32_td_direction =  UX_HCD_STM32_TD_OUT;

        /* Mark the TD with the DATA phase.  */
        data_td -> ux_stm32_td_status |=  UX_HCD_STM32_TD_DATA_PHASE;

        /* The Toggle value is in the ED.  */
        data_td -> ux_stm32_td_toggle =  UX_HCD_STM32_TD_TOGGLE_FROM_ED;

        /* Check if there will be another transaction.  */
        if (transfer_request_payload_length != 0)
        {

            /* Get a new TD to hook this payload.  */
            data_td =  _ux_hcd_stm32_regular_td_obtain(hcd_stm32);
            if (data_td == UX_NULL)
            {

                /* If there was already a TD chain in progress, free it.  */
                if (start_data_td != UX_NULL)
                {

                    data_td =  start_data_td;
                    while (data_td)
                    {

                        next_data_td =  data_td -> ux_stm32_td_next_td;
                        data_td -> ux_stm32_td_status =  UX_UNUSED;
                        data_td =  next_data_td;
                    }
                }

                /* Clear the skip bit.  */
                ed -> ux_stm32_ed_status &= ~UX_HCD_STM32_ED_SKIP;

                return(UX_NO_TD_AVAILABLE);
            }

            /* the first obtained TD in the chain has to be remembered.  */
            if (start_data_td == UX_NULL)
                start_data_td =  data_td;

            /* Attach this new TD to the previous one.  */                                
            previous_td -> ux_stm32_td_next_td =  data_td;
            previous_td -> ux_stm32_td_next_td_transfer_request =  data_td;
            previous_td =  data_td;
        }
    }
        
    /* At this stage, the Head and Tail in the ED are still the same and the STM32 
       controller will skip this ED until we have hooked the new tail TD.  */
    tail_td =  _ux_hcd_stm32_regular_td_obtain(hcd_stm32);
    if (tail_td == UX_NULL)
    {

        /* If there was already a TD chain in progress, free it.  */
        if (start_data_td != UX_NULL)
        {
 
            data_td =  start_data_td;
            while (data_td)
            {

                next_data_td =  data_td -> ux_stm32_td_next_td;
                data_td -> ux_stm32_td_status =  UX_UNUSED;
                data_td =  next_data_td;
            }
        }

        /* Clear the skip bit.  */
        ed -> ux_stm32_ed_status &= ~UX_HCD_STM32_ED_SKIP;

        return(UX_NO_TD_AVAILABLE);
    }

    /* Attach the tail TD to the last data TD.  */
    data_td -> ux_stm32_td_next_td =  tail_td;

    /* Store the new tail TD.  */
    ed -> ux_stm32_ed_tail_td =  tail_td;

    /* Now we can tell the scheduler to wake up.  */
    hcd_stm32 -> ux_hcd_stm32_queue_empty =  UX_FALSE;
    
    /* Clear the skip bit.  */
    ed -> ux_stm32_ed_status &= ~UX_HCD_STM32_ED_SKIP;

    /* Return successful completion.  */
    return(UX_SUCCESS);           
}

