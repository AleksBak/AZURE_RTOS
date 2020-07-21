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
/*    _ux_hcd_stm32_asynch_queue_process                  PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function process the asynchronous transactions that happened   */ 
/*    in the last frame.                                                  */
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                           Pointer to STM32 controller     */ 
/*    channel_index                       Index of channel.               */ 
/*    channel_interrupt_source            Source of interrupt.            */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    (ux_transfer_request_completion_function) Transfer req completion   */ 
/*    _ux_hcd_stm32_atl_buffer_read             Read to the ATL buffer    */ 
/*    _ux_hcd_stm32_ed_td_clean                 Clean STM32 TD            */ 
/*    _ux_hcd_stm32_register_read               Read STM32 register       */ 
/*    _ux_utility_semaphore_put                 Put semaphore             */ 
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
VOID  _ux_hcd_stm32_asynch_queue_process(UX_HCD_STM32 *hcd_stm32, ULONG channel_index,
                                        ULONG channel_interrupt_source)
{

UX_HCD_STM32_TD     *next_td;
UX_HCD_STM32_TD     *td;
UX_HCD_STM32_ED     *ed;
UX_TRANSFER         *transfer_request;
ULONG               actual_length;
UINT                short_packet;
UX_ENDPOINT         *endpoint;
UCHAR                *buffer;
ULONG                td_phase;
ULONG                channel_register;
ULONG                dword_count;
ULONG                byte_count;
ULONG                fifo_value;
ULONG                stm32_grxstp_register;
ULONG                transfer_status;
ULONG                transfer_size;
ULONG                hctsiz_register;
ULONG                hcintmsk_register;
        
    /* Load the ED for the channel.  */
    ed =  hcd_stm32 -> ux_hcd_stm32_channels_ed[channel_index];
    
    /* Do a sanity test. The ED should be legal and non zero.  */
    if (ed == UX_NULL)
    {    

        /* We have a major problem here. Should not happen !  */
        return;
    }
    
    /* Get the endpoint container.  */
    endpoint =  ed -> ux_stm32_ed_endpoint;
    
    /* Get the TD associated with this transfer. */
    td = ed -> ux_stm32_ed_head_td;
    
    /* Get the transfer request associated with the TD.  */                          
    transfer_request =  td -> ux_stm32_td_transfer_request;

    /* Unmask the Chanel Halt interrupt.  */
    hcintmsk_register = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCINT + 
                       (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    

    /* Set the Halt bit to unmask.  */
    hcintmsk_register |=  UX_HCD_STM32_OTG_FS_HCINT_CHHM;

    /* Save the channel register.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCINT + 
                            (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), hcintmsk_register);                    

    /* Look at the content of the interrupt register and determine the reason for completion of the transaction.  */
    /* Was it a RXFLVL interrupt ? */
    if (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_RXFLVL)
    {

        /* Get the GRXSTSP register. This tells us on what endpoint the INT happened.  
           Here we use the POP register, not the read.  */
        stm32_grxstp_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_GRXSTSP);
                    
        /* Isolate the transfer status.  */
        transfer_status = (stm32_grxstp_register & UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_MASK) >> UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_SHIFT;  
        
        /* Isolate the transfer length.  */
        transfer_size =  (stm32_grxstp_register & UX_HCD_STM32_OTG_FS_GRXSTSP_BCNT_MASK) >> UX_HCD_STM32_OTG_FS_GRXSTSP_BCNT_SHIFT;
        
        /* Is this is a IN transfer.  We filter only IN transfers to read the content of the FIFO. */
        if (transfer_status == UX_HCD_STM32_OTG_FS_GRXSTSP_PKTSTS_IN_RCVD)
        {
    
            /* Adjust the length in the TD.  */
            td -> ux_stm32_td_actual_length += transfer_size;

            /* Calculate the DWORD count to transmit from DWORD aligned FIFO.  */
            dword_count =  transfer_size / sizeof(ULONG);
            
            /* Get the byte count left. */
            byte_count =  transfer_size % sizeof(ULONG);

            /* Check if we have space to receive.  */
            if (transfer_size > td -> ux_stm32_td_length)
            {

                /* No space for receiving.  */
                /* Increase the DWORD count if there is any remaining bytes.  */
                if (byte_count != 0)
                    dword_count ++;
                
                /* Loop to read data in the FIFO.  */
                while (dword_count-- != 0)
                {
                    /* Discard data in the FIFO.  */
                    _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_FIFO + 
                                    (ed -> ux_stm32_ed_channel * UX_HCD_STM32_FIFO_CHANNEL_SIZE));
                }
            }
            else
            {
                
                /* Get the beginning of the transfer buffer.  */
                buffer =  td -> ux_stm32_td_buffer;
                
                /* Update the buffer pointer with the length received.  */
                td -> ux_stm32_td_buffer += transfer_size;
        
                /* Transfer a dword at a time from FIFO.  */
                while (dword_count-- != 0)
                {
        
                    /* Read from the FIFO.  */
                    fifo_value =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_FIFO + 
                                    (ed -> ux_stm32_ed_channel * UX_HCD_STM32_FIFO_CHANNEL_SIZE));
        
                    /* We can write a DWORD.  */
                    _ux_utility_long_put(buffer, fifo_value);
                        
            
                    /* Point to the next DWORD.  */
                    buffer += sizeof(ULONG);
                }
        
                /* We are done with the DWORD count.  See if leftover.  */
                if (byte_count != 0)
                {
        
                    /* We have something left.  Read from the fifo.  */
                    fifo_value =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_FIFO + 
                                    (ed -> ux_stm32_ed_channel * UX_HCD_STM32_FIFO_CHANNEL_SIZE));
        
                    /* Can we fit a word.  */
                    if (byte_count >= sizeof(USHORT))
                    {
            
                        /* Yes. Store it.  */
                        _ux_utility_short_put(buffer, fifo_value);
                        
                        /* Decrement the byte count.  */
                        byte_count -= sizeof(USHORT);
                        
                        /* Shift the value.  */
                        fifo_value = fifo_value >> (sizeof(USHORT) * 8);
                        
                        /* Point to the next WORD.  */
                        buffer += sizeof(USHORT);
                    } 
        
                    /* Byte left ? */
                    if (byte_count != 0)
                    {
            
                        /* Yes. Store it.  */
                        *buffer = (UCHAR) fifo_value;
                        
                        /* Decrement the byte count.  */
                        byte_count -= 1;
                        
                    } 
                }

        
                /* Read the HCTSIZ register. */
                hctsiz_register = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCTSIZ + 
                                   (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    

                /* See if there is more packets expected by checking PKTCNT.  */
                if (((hctsiz_register & UX_HCD_STM32_OTG_FS_HCTSIZ_PKTCNT_MASK) >> UX_HCD_STM32_OTG_FS_HCTSIZ_PKTCNT_SHIFT) != 0)
                {

                    /* Read the HCCAR register.  */
                    channel_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                            (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    
        
                    
                    /* Reset the Disable bit.  */
                    channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS;
        
                    /* Set Channel enabled bit to restart the transfer.  */
                    channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_CHENA;

                    /* Save the channel register.  */
                    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                            (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), channel_register);                    
        
                }
            }
        }
    }

    /* Look at the content of the interrupt register and determine the reason for completion of the transaction.  */
    /* Was the transaction completed successfully ? */
    if (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_XFRC)
    {
    
        /* The XFRC bit is raised. We have a completion with no errors.  
           Get the transfer length for that transaction. For IN packet,
           we take the field from the actual size. */
        if (td -> ux_stm32_td_direction ==  UX_HCD_STM32_TD_IN)
        
            /* Length is actual length.  */
            actual_length = td -> ux_stm32_td_actual_length;
            
        else
            /* Transfer is out. Length is in td_length.  */
            actual_length = td -> ux_stm32_td_length;
    
    
        /* The toggle bit expected for the next transfer.  */
        if (td -> ux_stm32_td_toggle ==  UX_HCD_STM32_TD_TOGGLE_FROM_ED)
        {

            /* Read the HCTSIZ register. It contains the Data Toggle.  */
            hctsiz_register = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCTSIZ + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    

            /* Isolate the Data Toggle.  */
            hctsiz_register &= UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_MASK;
            
            /* Decode and keep data toggle.  */
            switch (hctsiz_register)
            {

                case    UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA0    :
        
                    /* The toggle for next time is DATA0.  */
                       ed -> ux_stm32_ed_toggle = 0;
                    break;
                
                case    UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA2    :

                    /* The toggle for next time is DATA2.  */
                       ed -> ux_stm32_ed_toggle = 2;
                    break;
                
                case    UX_HCD_STM32_OTG_FS_HCTSIZ_DPID_DATA1    :

                    /* The toggle for next time is DATA1.  */
                       ed -> ux_stm32_ed_toggle = 1;
                    break;

            }
        }
                            
        /* Decide if this is a short packet or not.  */
        if (((actual_length % ed -> ux_stm32_ed_endpoint -> ux_endpoint_descriptor.wMaxPacketSize) != 0) || actual_length == 0)
        
            /* This is a short packet.  */
            short_packet = UX_TRUE;
            
        else
        
            /* This is not a short packet.  */
            short_packet = UX_FALSE;            
        
        /* If this a data phase either on a control endpoint or any transfer on a bulk endpoint,
           the transfer request actual length must be updated.  */
        if (td -> ux_stm32_td_status & UX_HCD_STM32_TD_DATA_PHASE)
            transfer_request -> ux_transfer_request_actual_length +=  actual_length;
    
        /* Get the TD status and isolate the Phase.  */
        td_phase =    td -> ux_stm32_td_status & UX_HCD_STM32_TD_PHASE_MASK;
    
        /* Check for control endpoint.  */
        if ((endpoint -> ux_endpoint_descriptor.bmAttributes & UX_MASK_ENDPOINT_TYPE) == UX_CONTROL_ENDPOINT) 
        {
            
            /* Check if we have received too much data.  */
            if (transfer_request -> ux_transfer_request_actual_length > transfer_request -> ux_transfer_request_requested_length)
            {

                /* Set the completion code to error.  */
                transfer_request -> ux_transfer_request_completion_code =  UX_TRANSFER_ERROR;
            }
            else
            {

                /* Set the completion code to SUCCESS.  */
                transfer_request -> ux_transfer_request_completion_code =  UX_SUCCESS;
            }

            /* Take the TD out of the Endpoint.  */
            ed -> ux_stm32_ed_head_td =  td -> ux_stm32_td_next_td;
        
            /* We can now free the TD used in this PTD.  */
            td -> ux_stm32_td_status =  UX_UNUSED;
    
            /* Check for phase.  */
            switch (td_phase)
            {
    
                case UX_HCD_STM32_TD_SETUP_PHASE :
    
                break;    
            
                case UX_HCD_STM32_TD_DATA_PHASE  :
    
                    /* If there is a short packet, we need to take out all the pending DATA phases
                          linked to the ED. We leave the STATUS phase.  If transfer error occurred, we take out all the pending TDs.  */
                    if (short_packet == UX_TRUE || transfer_request -> ux_transfer_request_completion_code != UX_SUCCESS)
                    {
    
                        /* Get the TD attached to the head and traverse the linked list.  */
                        td =  ed -> ux_stm32_ed_head_td;
    
                        /* Check if we have reached the end.  */
                        while (td != ed -> ux_stm32_ed_tail_td)
                        {
                                
                            /* Check the TD phase. On error, we also remove the TD for status phase.  */
                            if ((td -> ux_stm32_td_status & UX_HCD_STM32_TD_DATA_PHASE) || 
                                (transfer_request -> ux_transfer_request_completion_code != UX_SUCCESS))
                            {
    
                                /* Memorize this TD.  */
                                next_td =  td -> ux_stm32_td_next_td;                     
        
                                /* This is a DATA phase, take it out of the chain.  */
                                ed -> ux_stm32_ed_head_td =  next_td;                     
        
                                /* We can now free the TD.  */
                                td -> ux_stm32_td_status =  UX_UNUSED;
    
                                /* Next TD.  */
                                td =  next_td;
                            }
                            else
                                /* Next TD.  */
                                td =  td -> ux_stm32_td_next_td;                      
                                                            
                        }
                        
                    }
                    
                    /* If transfer error occurred, we need to retire the transfer request.  */
                    if (transfer_request -> ux_transfer_request_completion_code == UX_SUCCESS)
                    {

                        /* We are done here. */
                        break;
                    }
    
                default :
    
                    /* Status Phase or error occurred.  Wake up the transfer request. */
                    if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
                        transfer_request -> ux_transfer_request_completion_function(transfer_request);
    
                    /* Wake up the transfer request thread.  */
                    _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);
            
                    break;    
            }                    
        }                        
        else
        {
        

            /* We come here when this is a non control endpoint,
            Check the transmitted length and see if we have a short packet or if we are finished with this transfer.  */
            if ((transfer_request -> ux_transfer_request_actual_length >= transfer_request -> ux_transfer_request_requested_length) ||
                (short_packet == UX_TRUE))
            {
        
                /* Remove all the TDs attached.  */
                while (td != ed -> ux_stm32_ed_tail_td)
                {
                                        
                    /* Memorize this TD.  */
                    next_td =  td -> ux_stm32_td_next_td;                     
        
                    /* Take it out of the chain.  */
                    ed -> ux_stm32_ed_head_td =  next_td;                     
        
                    /* We can now free the TD.  */
                    td -> ux_stm32_td_status =  UX_UNUSED;
        
                    /* Next TD.  */
                    td =  next_td;
                }
                
                /* Check if we received more data than expected.  */
                if (transfer_request -> ux_transfer_request_actual_length > transfer_request -> ux_transfer_request_requested_length)
                {

                    /* Set the completion code to error.  */                                
                    transfer_request -> ux_transfer_request_completion_code =  UX_TRANSFER_ERROR;
                }
                else
                {

                    /* Set the completion code to SUCCESS.  */
                    transfer_request -> ux_transfer_request_completion_code =  UX_SUCCESS;
                }
                
                /* All transfer completion default to this section. */
                if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
                    transfer_request -> ux_transfer_request_completion_function(transfer_request);
        
                /* Wake up the transfer request thread.  */
                _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);
            }        
            else
            {
                
                /* We only remove the first td and leave the other TDs attached to the ED.  */
                ed -> ux_stm32_ed_head_td =  td -> ux_stm32_td_next_td;                     
        
                /* We can now free the TD.  */
                td -> ux_stm32_td_status =  UX_UNUSED;
        
            }
        }
    
    }

    /* Check for ACK reception. We ignore this interrupt.  But reset the error count.  */
    if (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_ACK)
    {

        /* Reset the error count.  */
        ed -> ux_stm32_ed_command_retry    = 0;

    }
    
    /* Check for NAK reception. Differentiate the IN/OUT and Bulk/Control and Interrupt pipes. Reset the error count.  */
    if (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_NAK)
    {

        /* Reset the error count.  */
        ed -> ux_stm32_ed_command_retry    = 0;

        /* Check for direction of transfer.  */
        channel_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    
    
        /* Check the direction.  */
        if (channel_register & UX_HCD_STM32_OTG_FS_HCCHAR_EPDIR_IN)
        {

            /* IN direction.  */
            /* Check the type of endpoint. Interrupt and Bulk/Control are treated differently.  */
            if ((endpoint -> ux_endpoint_descriptor.bmAttributes & UX_MASK_ENDPOINT_TYPE) == UX_INTERRUPT_ENDPOINT)
            {
    
                /* Reset TD into response pending state. */
                td -> ux_stm32_td_status &=  ~UX_HCD_STM32_TD_ACK_PENDING;
    
                /* Halt Channel.  */
                _ux_hcd_stm32_channel_halt(hcd_stm32, ed);
                
            }
            else
            {

                /* Check the NAK counter.  */
                if (ed -> ux_stm32_ed_nak_counter == UX_HCD_STM32_ASYNCH_NAK_COUNTER)
                {
                    
                    /* We have exhausted our NAK counts, skip this transaction.  */
                    /* Reset TD into response pending state. */
                    td -> ux_stm32_td_status &=  ~UX_HCD_STM32_TD_ACK_PENDING;
    
                    /* Halt Channel.  */
                    _ux_hcd_stm32_channel_halt(hcd_stm32, ed);

                }
                else
                {
    
                    /* Increment the NAK counter.  */
                    ed -> ux_stm32_ed_nak_counter++;
                    
                    /* Treat Control and Bulk NAK status.  */
                    /* Clear the Channel disable flag.  */
                    channel_register &=  ~UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS;
                    
                    /* Set Channel enabled bit to restart the transfer.  */
                    channel_register |=  UX_HCD_STM32_OTG_FS_HCCHAR_CHENA;
                        
                    /* Write the channel register. This will restart the transaction.  */
                    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                        (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), channel_register);                    
                }
            }
        }
        else
        {

            /* OUT direction.  */
            /* Reset TD into response pending state. */
            td -> ux_stm32_td_status &=  ~UX_HCD_STM32_TD_ACK_PENDING;
    
            /* Halt Channel.  */
            _ux_hcd_stm32_channel_halt(hcd_stm32, ed);
                
        }
    }
    
    /* Check for halted channel.  */
    if (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_CHH)    
    {
        

        /* Read the channel register.*/
        channel_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));                    


        /* Reset the channel to halted.  */
        ed -> ux_stm32_ed_channel_status = UX_HCD_STM32_ED_CHANNEL_RESET;

    }
    
    /* Check for errors in the transmission.  */
    if ((channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_STALL) || (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_TXERR)    
                                                                     || (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_BBERR)    
                                                                     || (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_DTERR)    
                                                                     || (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_FRMOR))
    {
    
        /* Set the channel register with Channel Disable bit on.  */
        _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS);                    

        /* Set the channel to halted.  */
        ed -> ux_stm32_ed_channel_status = UX_HCD_STM32_ED_CHANNEL_HALTED;

        /* We get here when there is an error. If the error is not a STALL or Channel halted,
           we will repeat 3 times. If the number of errors has been reached, the command
           has definitively failed and the transfer is retired.  */
        if (channel_interrupt_source & UX_HCD_STM32_OTG_FS_HCINT_STALL)
            
            /* Mark the STALL.  */
            transfer_request -> ux_transfer_request_completion_code =  UX_TRANSFER_STALLED;

        else
        {

            /* This is a transmission error or channel halted.  Mark the ERROR.  */
            transfer_request -> ux_transfer_request_completion_code =  UX_TRANSFER_ERROR;
    
            /* This command may need to be retried.  */
            if (ed -> ux_stm32_ed_command_retry++ !=  UX_HCD_STM32_COMMAND_RETRY)
            {
            
                /* Reset the status, it is irrelevant until we have retried.  */
                transfer_request -> ux_transfer_request_completion_code =  UX_TRANSFER_STATUS_PENDING;
            
                /* Reset TD into response pending state. */
                td -> ux_stm32_td_status &=  ~UX_HCD_STM32_TD_ACK_PENDING;
    
                /* Indeed we have not exhausted the number of retries.  */
                return;                  
            }
        }
                
        /* Either the command is a stall or we have exhausted our retry count.
           Remove all the TDs attached.  */
        while (td != ed -> ux_stm32_ed_tail_td)
        {
                                
            /* Memorize this TD.  */
            next_td =  td -> ux_stm32_td_next_td;                     
        
            /* Take it out of the chain.  */
            ed -> ux_stm32_ed_head_td =  next_td;                     
        
            /* We can now free the TD.  */
            td -> ux_stm32_td_status =  UX_UNUSED;
        
            /* Next TD.  */
            td =  next_td;
        }
        
        /* All errors\transfer completion default to this section. The command has been repeated 3 times 
           and there is still a problem. The endpoint probably should be reset.  .  */
        if (transfer_request -> ux_transfer_request_completion_function != UX_NULL)
            transfer_request -> ux_transfer_request_completion_function(transfer_request);
        
        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, transfer_request -> ux_transfer_request_completion_code, transfer_request, 0, 0, UX_TRACE_ERRORS, 0, 0)
        
        /* Wake up the transfer request thread.  */
        _ux_utility_semaphore_put(&transfer_request -> ux_transfer_request_semaphore);
    }    
    
    /* Return to caller.  */
    return;
}

