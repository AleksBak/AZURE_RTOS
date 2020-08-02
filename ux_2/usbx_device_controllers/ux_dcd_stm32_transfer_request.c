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

#define UX_SOURCE_CODE


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_dcd_stm32.h"
#include "ux_utility.h"
#include "ux_device_stack.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                RELEASE       */
/*                                                                        */
/*    _ux_dcd_stm32_transfer_request                       PORTABLE C     */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will initiate a transfer to a specific endpoint.      */
/*    If the endpoint is IN, the endpoint register will be set to accept  */
/*    the request.                                                        */
/*                                                                        */
/*    If the endpoint is IN, the endpoint FIFO will be filled with the    */
/*    buffer and the endpoint register set.                               */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_stm32                             Pointer to device controller  */
/*    transfer_request                      Pointer to transfer request   */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_dcd_stm32_register_read           Read register                 */ 
/*    _ux_dcd_stm32_register_set            Set register                  */ 
/*    _ux_dcd_stm32_register_write          Write register                */ 
/*    _ux_utility_semaphore_get             Get semaphore                 */ 
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
UINT  _ux_dcd_stm32_transfer_request(UX_DCD_STM32 *dcd_stm32, UX_SLAVE_TRANSFER *transfer_request)
{

UX_DCD_STM32_ED          *ed;
UCHAR *                 fifo_buffer;
ULONG                   fifo_length;
UX_SLAVE_ENDPOINT       *endpoint;
ULONG                    endpoint_control_address;
ULONG                    endpoint_size_address;
ULONG                    endpoint_control;
ULONG                    endpoint_size;
UINT                    status;                            

    /* Get the pointer to the logical endpoint from the transfer request.  */
    endpoint =  transfer_request -> ux_slave_transfer_request_endpoint;

    /* Get the physical endpoint from the logical endpoint.  */
    ed =  (UX_DCD_STM32_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Check for transfer direction.  Is this a IN endpoint ? */
    if (transfer_request -> ux_slave_transfer_request_phase == UX_TRANSFER_PHASE_DATA_OUT)
    {

        /* Compute the endpoint address.  */
        endpoint_control_address = (UX_DCD_STM32_OTG_FS_DIEPCTL + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

        /* And the size register.  */
        endpoint_size_address = (UX_DCD_STM32_OTG_FS_DIEPTSIZ + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));
        
        /* Read the content of the control register.  */
        endpoint_control  =  _ux_dcd_stm32_register_read(dcd_stm32, endpoint_control_address);

        /* Get the size of the transfer, used for a IN transaction only.  */
        fifo_length =  transfer_request -> ux_slave_transfer_request_requested_length;

        /* Check if the endpoint size is bigger that data requested. */
        if(fifo_length > endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)
        {

            /* Adjust the transfer size.  */
            fifo_length =  endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
        }

        /* Check if size is 0 as in ZLP.  */
        if (fifo_length == 0)
            
            /* Still one packet count.  */
            endpoint_size = 1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;                        
        
        else
        {

            /* Program the transfer size.  */
            endpoint_size = fifo_length;
            
            /* And packet counts.  */
            endpoint_size |= ((fifo_length - 1 + endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) / 
                                    endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;                         

        }
        
        /* Write the size of the FIFO.  */
        _ux_dcd_stm32_register_write(dcd_stm32, endpoint_size_address, endpoint_size); 
        
        /* Enable the IN endpoint FIFO.  */
        endpoint_control |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK; 
        
        /* Write the Endpoint Control register.  */
          _ux_dcd_stm32_register_write(dcd_stm32, endpoint_control_address, endpoint_control);
        
        /* Keep the FIFO length in the endpoint.  */
        ed -> ux_dcd_stm32_ed_payload_length =  fifo_length;

        /* Point the FIFO buffer to the current transfer request buffer address.  */
        fifo_buffer =  transfer_request -> ux_slave_transfer_request_data_pointer;
        
        /* Adjust the data pointer.  */
        transfer_request -> ux_slave_transfer_request_current_data_pointer += fifo_length;
        
        /* Adjust the transfer length remaining.  */
        transfer_request -> ux_slave_transfer_request_in_transfer_length -= fifo_length;

        /* If this is the last packet, set data end as well.  */
        if (transfer_request -> ux_slave_transfer_request_in_transfer_length == 0)

            /* Write to the Fifo.  last packet. */
            _ux_dcd_stm32_fifo_write(dcd_stm32, ed -> ux_dcd_stm32_ed_index, fifo_buffer, fifo_length, UX_TRUE);

        else
        
            /* Write to the Fifo.  More packets to come. */
            _ux_dcd_stm32_fifo_write(dcd_stm32, ed -> ux_dcd_stm32_ed_index, fifo_buffer, fifo_length, UX_FALSE);

        /* If the endpoint is a Control endpoint, all this is happening under Interrupt and there is no
           thread to suspend.  */
        if (ed -> ux_dcd_stm32_ed_index != 0)
        {

            /* We should wait for the semaphore to wake us up.  */
            status =  _ux_utility_semaphore_get(&transfer_request -> ux_slave_transfer_request_semaphore, UX_WAIT_FOREVER);
    
            /* Check the completion code. */
            if (status != UX_SUCCESS)
                return(status);
            
            /* Check the transfer request completion code. We may have had a BUS reset or
               a device disconnection.  */
            if (transfer_request -> ux_slave_transfer_request_completion_code != UX_SUCCESS)
                return(transfer_request -> ux_slave_transfer_request_completion_code);
    
            /* Return to caller with success.  */
            return(UX_SUCCESS);
        }
    }
    else
    {

        /* We have a request for a SETUP or OUT Endpoint.  */

        /* Compute the endpoint address.  */
        endpoint_control_address = (UX_DCD_STM32_OTG_FS_DOEPCTL + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

        /* And the size register.  */
        endpoint_size_address = (UX_DCD_STM32_OTG_FS_DOEPTSIZ + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));
        
        /* Read the content of the control register.  */
        endpoint_control  =  _ux_dcd_stm32_register_read(dcd_stm32, endpoint_control_address);

        /* Get the size of the transfer, used for a IN transaction only.  */
        fifo_length =  transfer_request -> ux_slave_transfer_request_requested_length;

        /* Check if the endpoint size is bigger that data requested. */
        if(fifo_length > endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize)
        {

            /* Adjust the transfer size.  */
            fifo_length =  endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
        }

        /* Check if size is 0 as in ZLP.  */
        if (fifo_length == 0)
            
            /* Still one packet count.  */
            endpoint_size = 1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;                        
        
        else
        {

            /* If this is a SETUP phase, we need to have 3 packets in the pipe possible.  */
            if (transfer_request -> ux_slave_transfer_request_type ==  UX_TRANSFER_PHASE_SETUP)
            {

                /* Program the transfer size.  */
                endpoint_size =  UX_SETUP_SIZE * 3;
                
                /* And packet counts.  */
                endpoint_size |= 1 << UX_DCD_STM32_OTG_FS_DOEPTSIZ_PKTCNT_SHIFT;                         
                
                /* Add the Value for STUPCNT.  */
                endpoint_size |=  UX_DCD_STM32_OTG_FS_DOEPTSIZ_STUPCNT_DEFAULT << UX_DCD_STM32_OTG_FS_DOEPTSIZ_STUPCNT_SHIFT;
                
            }
            else
            {
            
                /* Program the transfer size.  */
                endpoint_size = ((fifo_length - 1 + endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) / 
                                    endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) * 
                                    endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize;
                
                /* And packet counts.  */
                endpoint_size |= ((fifo_length - 1 + endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) / 
                                    endpoint -> ux_slave_endpoint_descriptor.wMaxPacketSize) << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;                         
            }
        }
        
        /* Write the size of the FIFO.  */
        _ux_dcd_stm32_register_write(dcd_stm32, endpoint_size_address, endpoint_size); 

        /* Reset the fifo length for the endpoint.  */
        ed -> ux_dcd_stm32_ed_payload_length = 0;
    
        /* Enable the OUT endpoint FIFO.  */
        endpoint_control |= UX_DCD_STM32_OTG_FS_DOEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DOEPCTL_CNAK; 

        /* Write the Endpoint Control register.  */
        _ux_dcd_stm32_register_write(dcd_stm32, endpoint_control_address, endpoint_control);

        /* If the endpoint is a Control endpoint, all this is happening under Interrupt and there is no
           thread to suspend.  */
        if (ed -> ux_dcd_stm32_ed_index != 0)
        {

            /* We should wait for the semaphore to wake us up.  */
            status =  _ux_utility_semaphore_get(&transfer_request -> ux_slave_transfer_request_semaphore, UX_WAIT_FOREVER);
                
            /* Check the completion code. */
            if (status != UX_SUCCESS)
                return(status);
            
            /* Check the transfer request completion code. We may have had a BUS reset or
               a device disconnection.  */
            if (transfer_request -> ux_slave_transfer_request_completion_code != UX_SUCCESS)
                return(transfer_request -> ux_slave_transfer_request_completion_code);
        
            /* Return to caller with success.  */
            return(UX_SUCCESS);
        }
    }

    /* Return to caller with success.  */
    return(UX_SUCCESS);
}

