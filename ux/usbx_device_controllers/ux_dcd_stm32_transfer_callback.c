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

/* Include necessary system files. */
#include "ux_api.h"
#include "ux_dcd_stm32.h"
#include "ux_device_stack.h"
#include "ux_utility.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                RELEASE       */
/*                                                                        */
/*    _ux_dcd_stm32_transfer_callback                      PORTABLE C     */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is invoked under ISR when an event happens on a       */
/*    specific endpoint.                                                  */
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
/*  CALLS                                                                 */
/*                                                                        */
/*    _ux_dcd_stm32_address_set             Set address                   */
/*    _ux_dcd_stm32_register_clear          Clear register                */
/*    _ux_dcd_stm32_register_read           Read register                 */
/*    _ux_dcd_stm32_register_write          Write register                */
/*    _ux_dcd_stm32_register_set            Set register                  */
/*    _ux_device_stack_control_request_process Process control request    */
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
UINT _ux_dcd_stm32_transfer_callback(UX_DCD_STM32* dcd_stm32, UX_SLAVE_TRANSFER* transfer_request)
{
//	ULONG stm32_register;
//	UX_SLAVE_ENDPOINT* endpoint;
//	UX_DCD_STM32_ED* ed;
//	UCHAR* data_pointer;
//	ULONG fifo_length;
//	ULONG stm32_endpoint_index;
//	ULONG endpoint_control_address;
//	ULONG endpoint_size_address;
//	ULONG endpoint_control;
//	ULONG endpoint_size;

	/* Get the pointer to the logical endpoint from the transfer request. */
	UX_SLAVE_ENDPOINT* endpoint = transfer_request->ux_slave_transfer_request_endpoint;

	/* Get the endpoint index. */
	ULONG stm32_endpoint_index = endpoint->ux_slave_endpoint_descriptor.bEndpointAddress
			& ~UX_ENDPOINT_DIRECTION;

	/* Get the STM32 endpoint. */
	UX_DCD_STM32_ED* ed = (UX_DCD_STM32_ED*)endpoint->ux_slave_endpoint_ed;

	/* Get the pointer to the data buffer of the transfer request. */
	UCHAR* data_pointer = transfer_request->ux_slave_transfer_request_data_pointer;

	/*--------------------------------------------------------------------------------------------*/

	ULONG fifo_length;
	ULONG endpoint_size;
	ULONG endpoint_control;

	/* Endpoint 0 is different. */
	if (stm32_endpoint_index == 0)
	{
		/* Check if we have received a SETUP command. */
		if (ed->ux_dcd_stm32_ed_transfer_status == UX_DCD_STM32_ED_TRANSFER_STATUS_SETUP)
		{
			/* The out FIFO of the control endpoint must be flushed now
			 * as there may have been a previous unfinished control transaction. */
			_ux_dcd_stm32_fifo_flush(dcd_stm32, UX_DCD_STM32_FLUSH_TX_FIFO, 0);

			/* Clear the length of the data received. */
			transfer_request->ux_slave_transfer_request_actual_length = 0;

			/* Mark the phase as SETUP. */
			transfer_request->ux_slave_transfer_request_type = UX_TRANSFER_PHASE_SETUP;

			/* Mark the transfer as successful. */
			transfer_request->ux_slave_transfer_request_completion_code = UX_SUCCESS;

			/* Set the status of the endpoint to not stalled. */
			ed->ux_dcd_stm32_ed_status &= ~UX_DCD_STM32_ED_STATUS_STALLED;

			/* Check if the transaction is IN. */
			if (*transfer_request->ux_slave_transfer_request_setup & UX_REQUEST_IN)
			{
				/* The endpoint is IN. This is important to memorize the direction
				 * for the control endpoint in case of a STALL. */
				ed->ux_dcd_stm32_ed_direction = UX_ENDPOINT_IN;

				/* Call the Control Transfer dispatcher. */
				_ux_device_stack_control_request_process(transfer_request);
			}
			else
			{
				/* The endpoint is OUT. This is important to memorize the direction
				 * for the control endpoint in case of a STALL. */
				ed->ux_dcd_stm32_ed_direction = UX_ENDPOINT_OUT;

				/* We are in a OUT transaction. Check if there is a data payload.
				 * If so, wait for the payload to be delivered. */
				if (*(transfer_request->ux_slave_transfer_request_setup + 6) == 0 &&
						*(transfer_request->ux_slave_transfer_request_setup + 7) == 0)
					/* Call the Control Transfer dispatcher. */
					_ux_device_stack_control_request_process(transfer_request);
			}

			/* Check if the transaction is OUT and there is no data payload. */
			if (((*transfer_request->ux_slave_transfer_request_setup & UX_REQUEST_IN) == 0) &&
					*(transfer_request->ux_slave_transfer_request_setup + 6) == 0 &&
					*(transfer_request->ux_slave_transfer_request_setup + 7) == 0)
			{
				/* In the case of a SETUP followed by NO data payload, we let the controller reply to the next 
				 zero length IN packet. Reset the length to transfer. */
				transfer_request->ux_slave_transfer_request_in_transfer_length = 0;
				transfer_request->ux_slave_transfer_request_requested_length = 0;

				/* Set the phase of the transfer to data OUT for status. */
				transfer_request->ux_slave_transfer_request_phase = UX_TRANSFER_PHASE_DATA_OUT;

				/* Set the state to STATUS RX. */
				ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_STATUS_RX;

				/* Arm a ZLP packet on IN. */
				/* Write the size of the FIFO.  1 packet, 0 XFERSIZ. */
				_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTSIZ,
						1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT);

				/* Write the Endpoint Control register. */
				_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL,
						UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK);
			}
			else
			{
				/* Check if data transfer is OUT. */
				if ((*transfer_request->ux_slave_transfer_request_setup & UX_REQUEST_IN) == 0)
				{
					/* Get the length we expect from the SETUP packet. */
					transfer_request->ux_slave_transfer_request_requested_length =
							_ux_utility_short_get(
									transfer_request->ux_slave_transfer_request_setup + 6);

					/* Check if we have enough space for the request. */
					if (transfer_request->ux_slave_transfer_request_requested_length
							> UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH)
					{
						/* No space available, stall the endpoint. */
						_ux_dcd_stm32_endpoint_stall(dcd_stm32, endpoint);

						/* Next phase is a SETUP. */
						ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_IDLE;

						/* We are done. */
						return (UX_SUCCESS);
					}
					else
					{
						/* Reset what we have received so far. */
						transfer_request->ux_slave_transfer_request_actual_length = 0;

						/* And reprogram the current buffer address to the beginning of the buffer. */
						transfer_request->ux_slave_transfer_request_current_data_pointer =
								transfer_request->ux_slave_transfer_request_data_pointer;

						/* Program the transfer size, only 1 packet is allowed on endpoint 0. */
						endpoint_size = endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

						/* And packet counts, only 1 packet is allowed for endpoint 0. */
						endpoint_size |= 1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;

						/* Write the size of the FIFO. */
						_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPTSIZ,
								endpoint_size);

						/* Set the state to RX. */
						ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_DATA_RX;
					}
				}
				else
					/* Set the state to TX. */
					ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_DATA_TX;
			}

			/* Rearm the OUT control endpoint. */
			_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPCTL,
					UX_DCD_STM32_OTG_FS_DOEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DOEPCTL_CNAK);
		}
		else
		{
			/* Check if we have received something on endpoint 0 during data phase . */
			if (ed->ux_dcd_stm32_ed_state == UX_DCD_STM32_ED_STATE_DATA_RX)
			{
				/* Read the fifo length for the Control endpoint. */
				fifo_length = ed->ux_dcd_stm32_ed_payload_length;

				/* Obtain the current data buffer address. */
				data_pointer = transfer_request->ux_slave_transfer_request_current_data_pointer;

				/* Can we accept this much?  */
				if (transfer_request->ux_slave_transfer_request_actual_length <=
						transfer_request->ux_slave_transfer_request_requested_length)
				{
					/* Are we done with this transfer ? */
					if ((transfer_request->ux_slave_transfer_request_actual_length ==
							transfer_request->ux_slave_transfer_request_requested_length) ||
							(fifo_length != endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize))
					{
						/* Set the completion code to no error. */
						transfer_request->ux_slave_transfer_request_completion_code = UX_SUCCESS;

						/* We are using a Control endpoint on a OUT transaction and there was a payload. */
						_ux_device_stack_control_request_process(transfer_request);

						/* Set the state to STATUS phase TX. */
						ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_STATUS_TX;

						/* Reset the length to transfer. */
						transfer_request->ux_slave_transfer_request_in_transfer_length = 0;
						transfer_request->ux_slave_transfer_request_requested_length = 0;

						/* Set the phase of the transfer to data OUT for status. */
						transfer_request->ux_slave_transfer_request_phase =
								UX_TRANSFER_PHASE_DATA_OUT;

						/* Arm a ZLP packet on IN. */
						/* Write the size of the FIFO.  1 packet, 0 XFERSIZ. */
						_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTSIZ,
								1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT);

						/* Write the Endpoint Control register. */
						_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL,
								UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK);
					}
					else
					{
						/* Rearm the OUT control endpoint for one packet. */
						endpoint_size = endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;
						endpoint_size |= 1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;
						_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPTSIZ,
								endpoint_size);
						_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPCTL,
								UX_DCD_STM32_OTG_FS_DOEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DOEPCTL_CNAK);
					}
				}
				else
				{
					/*  We have an overflow situation. Set the completion code to overflow. */
					transfer_request->ux_slave_transfer_request_completion_code =
							UX_TRANSFER_BUFFER_OVERFLOW;

					/* If trace is enabled, insert this event into the trace buffer. */
					UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_TRANSFER_BUFFER_OVERFLOW,
							transfer_request, 0, 0, UX_TRACE_ERRORS, 0, 0)

					/* We are using a Control endpoint, if there is a callback, invoke it. We are still under ISR. */
					if (transfer_request->ux_slave_transfer_request_completion_function)
						transfer_request->ux_slave_transfer_request_completion_function(
								transfer_request);
				}
			}
			else
			{

				/* Check if we have received something on endpoint 0 during status phase . */
				if (ed->ux_dcd_stm32_ed_state == UX_DCD_STM32_ED_STATE_STATUS_RX)
				{
					/* Next phase is a SETUP. */
					ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_IDLE;
				}
				else
				{
					/* Check if we need to send data again on control endpoint. */
					if (ed->ux_dcd_stm32_ed_state == UX_DCD_STM32_ED_STATE_DATA_TX)
					{
						/* Check if we have data to send. */
						if (transfer_request->ux_slave_transfer_request_in_transfer_length == 0)
						{
							/* There is no data to send but we may need to send a Zero Length Packet. */
							if (transfer_request->ux_slave_transfer_request_force_zlp == UX_TRUE)
							{
								/* Arm a ZLP packet on IN. */
								/* Write the size of the FIFO.  1 packet, 0 XFERSIZ. */
								_ux_dcd_stm32_register_write(dcd_stm32,
										UX_DCD_STM32_OTG_FS_DIEPTSIZ,
										1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT);

								/* Write the Endpoint Control register. */
								_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL,
										UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA
												| UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK);

								/* Reset the ZLP condition. */
								transfer_request->ux_slave_transfer_request_force_zlp = UX_FALSE;
							}
							else
							{
								/* Set the completion code to no error. */
								transfer_request->ux_slave_transfer_request_completion_code =
										UX_SUCCESS;

								/* The transfer is completed. */
								transfer_request->ux_slave_transfer_request_status =
										UX_TRANSFER_STATUS_COMPLETED;

								/* We are using a Control endpoint, if there is a callback,
								 * invoke it. We are still under ISR. */
								if (transfer_request->ux_slave_transfer_request_completion_function)
									transfer_request->ux_slave_transfer_request_completion_function(
											transfer_request);

								/* State is now STATUS RX. */
								ed->ux_dcd_stm32_ed_state = UX_DCD_STM32_ED_STATE_STATUS_RX;
							}
						}
						else
						{
							/* Get the size of the transfer, used for a IN transaction only. */
							fifo_length =
									transfer_request->ux_slave_transfer_request_in_transfer_length;

							/* Check if the endpoint size is bigger that data requested. */
							if (fifo_length > endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
							{
								/* Adjust the transfer size. */
								fifo_length = endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;
							}

							/* Keep the FIFO length in the endpoint. */
							ed->ux_dcd_stm32_ed_payload_length = fifo_length;

							/* Program the transfer size. */
							endpoint_size = fifo_length;

							/* And packet counts. */
							endpoint_size |= ((fifo_length - 1
									+ endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize) /
									endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
									<< UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;

							/* Write the size of the FIFO. */
							_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTSIZ,
									endpoint_size);

							/* Read the content of the control register. */
							endpoint_control = _ux_dcd_stm32_register_read(dcd_stm32,
									UX_DCD_STM32_OTG_FS_DIEPCTL);

							/* Enable the IN endpoint FIFO. */
							endpoint_control |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA
									| UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK;

							/* Write the Endpoint Control register. */
							_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL,
									endpoint_control);

							/* Point the FIFO buffer to the current transfer request buffer address. */
							data_pointer =
									transfer_request->ux_slave_transfer_request_current_data_pointer;

							/* Adjust the data pointer. */
							transfer_request->ux_slave_transfer_request_current_data_pointer +=
									fifo_length;

							/* Adjust the transfer length remaining. */
							transfer_request->ux_slave_transfer_request_in_transfer_length -=
									fifo_length;

							/* If this is the last packet, set data end as well. */
							if (transfer_request->ux_slave_transfer_request_in_transfer_length == 0)
								/* Write to the Fifo.  Last packet. */
								_ux_dcd_stm32_fifo_write(dcd_stm32, ed->ux_dcd_stm32_ed_index,
										data_pointer, fifo_length, UX_TRUE);
							else
								/* Write to the Fifo.  More packets to come. */
								_ux_dcd_stm32_fifo_write(dcd_stm32, ed->ux_dcd_stm32_ed_index,
										data_pointer, fifo_length, UX_FALSE);
						}
					}
				}
			}
		}
	}
	else
	{
		/* We treat non 0 endpoints here. Look at the direction and determine if this an OUT or IN endpoint. */
		if ((endpoint->ux_slave_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION)
				== UX_ENDPOINT_OUT)
		{
			/* Get the DOEPINT register. */
			ULONG stm32_register = _ux_dcd_stm32_register_read(dcd_stm32,
					UX_DCD_STM32_OTG_FS_DOEPINT +
					(stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE));

			/* Ensure there is no error. */
			if (stm32_register & UX_DCD_STM32_OTG_FS_DOEPINT_XFRC)
			{
				/* Read the fifo length for the endpoint. */
				fifo_length = ed->ux_dcd_stm32_ed_payload_length;

				/* Obtain the current data buffer address. */
				data_pointer = transfer_request->ux_slave_transfer_request_current_data_pointer;

				/* Can we accept this much?  */
				if (transfer_request->ux_slave_transfer_request_actual_length <=
						transfer_request->ux_slave_transfer_request_requested_length)
				{
					/* Are we done with this transfer ? */
					if ((transfer_request->ux_slave_transfer_request_actual_length ==
							transfer_request->ux_slave_transfer_request_requested_length) ||
							(fifo_length != endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize))
					{
						/* Set the completion code to no error. */
						transfer_request->ux_slave_transfer_request_completion_code = UX_SUCCESS;

						/* The transfer is completed. */
						transfer_request->ux_slave_transfer_request_status =
								UX_TRANSFER_STATUS_COMPLETED;

						/* Non control endpoint operation, use semaphore. */
						_ux_utility_semaphore_put(
								&transfer_request->ux_slave_transfer_request_semaphore);
					}
					else
					{
						/* We need to accept more packets. */
						fifo_length = transfer_request->ux_slave_transfer_request_requested_length;

						/* Check if the endpoint size is bigger that data requested. */
						if (fifo_length > endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
						{
							/* Adjust the transfer size. */
							fifo_length = endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;
						}

						/* Check if size is 0 as in ZLP. */
						if (fifo_length == 0)
							/* Still one packet count. */
							endpoint_size = 1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;
						else
						{
							/* Program the transfer size. */
							endpoint_size = ((fifo_length - 1
									+ endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize) /
									endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize) *
									endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

							/* And packet counts. */
							endpoint_size |= ((fifo_length - 1
									+ endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize) /
									endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
									<< UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;
						}

						/* Write the size of the FIFO. */
						_ux_dcd_stm32_register_write(dcd_stm32,
								UX_DCD_STM32_OTG_FS_DOEPTSIZ
										+ (stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE),
								endpoint_size);

						/* Read the content of the control register. */
						endpoint_control = _ux_dcd_stm32_register_read(dcd_stm32,
										UX_DCD_STM32_OTG_FS_DOEPCTL
												+ (stm32_endpoint_index
														* UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE));

						/* Enable the OUT endpoint FIFO. */
						endpoint_control |= UX_DCD_STM32_OTG_FS_DOEPCTL_EPENA
								| UX_DCD_STM32_OTG_FS_DOEPCTL_CNAK;

						/* Write the Endpoint Control register. */
						_ux_dcd_stm32_register_write(dcd_stm32,
								UX_DCD_STM32_OTG_FS_DOEPCTL
										+ (stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE),
								endpoint_control);
					}
				}
				else
				{
					/*  We have an overflow situation. Set the completion code to overflow. */
					transfer_request->ux_slave_transfer_request_completion_code =
							UX_TRANSFER_BUFFER_OVERFLOW;

					/* If trace is enabled, insert this event into the trace buffer. */
					UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_TRANSFER_BUFFER_OVERFLOW,
							transfer_request, 0, 0, UX_TRACE_ERRORS, 0, 0)

					/* The transfer is completed. */
					transfer_request->ux_slave_transfer_request_status =
							UX_TRANSFER_STATUS_COMPLETED;

					/* Non control endpoint operation, use semaphore. */
					_ux_utility_semaphore_put(
							&transfer_request->ux_slave_transfer_request_semaphore);
				}
			}
			else
			{
				/*  We have an error situation. Set the completion code to error. */
				transfer_request->ux_slave_transfer_request_completion_code = UX_TRANSFER_ERROR;

				/* The transfer is completed. */
				transfer_request->ux_slave_transfer_request_status = UX_TRANSFER_STATUS_COMPLETED;

				/* Non control endpoint operation, use semaphore. */
				_ux_utility_semaphore_put(&transfer_request->ux_slave_transfer_request_semaphore);
			}
		}
		else
		{
			/* Update the length of the data sent in previous transaction. */
			transfer_request->ux_slave_transfer_request_actual_length +=
					ed->ux_dcd_stm32_ed_payload_length;

			/* Check if we have data to send. */
			if (transfer_request->ux_slave_transfer_request_in_transfer_length == 0)
			{
				/* There is no data to send but we may need to send a Zero Length Packet. */
				if (transfer_request->ux_slave_transfer_request_force_zlp == UX_TRUE)
				{
					/* Arm a ZLP packet on IN. */
					/* Write the size of the FIFO.  1 packet, 0 XFERSIZ. */
					_ux_dcd_stm32_register_write(dcd_stm32,
							UX_DCD_STM32_OTG_FS_DIEPTSIZ
									+ (stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE),
							1 << UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT);

					/* Write the Endpoint Control register. */
					_ux_dcd_stm32_register_set(dcd_stm32,
							UX_DCD_STM32_OTG_FS_DIEPCTL
									+ (stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE),
							UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA | UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK);

					/* Reset the ZLP condition. */
					transfer_request->ux_slave_transfer_request_force_zlp = UX_FALSE;
				}
				else
				{
					/* Set the completion code to no error. */
					transfer_request->ux_slave_transfer_request_completion_code = UX_SUCCESS;

					/* The transfer is completed. */
					transfer_request->ux_slave_transfer_request_status =
							UX_TRANSFER_STATUS_COMPLETED;

					/* Non control endpoint operation, use semaphore. */
					_ux_utility_semaphore_put(
							&transfer_request->ux_slave_transfer_request_semaphore);
				}
			}
			else
			{
				/* Compute the endpoint address. */
				ULONG endpoint_control_address = (UX_DCD_STM32_OTG_FS_DIEPCTL
						+ (stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

				/* And the size register. */
				ULONG endpoint_size_address = (UX_DCD_STM32_OTG_FS_DIEPTSIZ
						+ (stm32_endpoint_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

				/* Read the content of the control register. */
				endpoint_control = _ux_dcd_stm32_register_read(dcd_stm32, endpoint_control_address);

				/* Get the size of the transfer, used for a IN transaction only. */
				fifo_length = transfer_request->ux_slave_transfer_request_in_transfer_length;

				/* Check if the endpoint size is bigger that data requested. */
				if (fifo_length > endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
				{
					/* Adjust the transfer size. */
					fifo_length = endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;
				}

				/* Keep the FIFO length in the endpoint. */
				ed->ux_dcd_stm32_ed_payload_length = fifo_length;

				/* Program the transfer size. */
				endpoint_size = fifo_length;

				/* And packet counts. */
				endpoint_size |= ((fifo_length - 1
						+ endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize) /
						endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
						<< UX_DCD_STM32_OTG_FS_DIEPTSIZ_PKTCNT_SHIFT;

				/* Write the size of the FIFO. */
				_ux_dcd_stm32_register_write(dcd_stm32, endpoint_size_address, endpoint_size);

				/* Enable the IN endpoint FIFO. */
				endpoint_control |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA
						| UX_DCD_STM32_OTG_FS_DIEPCTL_CNAK;

				/* Write the Endpoint Control register. */
				_ux_dcd_stm32_register_write(dcd_stm32, endpoint_control_address, endpoint_control);

				/* Point the FIFO buffer to the current transfer request buffer address. */
				data_pointer = transfer_request->ux_slave_transfer_request_current_data_pointer;

				/* Adjust the data pointer. */
				transfer_request->ux_slave_transfer_request_current_data_pointer += fifo_length;

				/* Adjust the transfer length remaining. */
				transfer_request->ux_slave_transfer_request_in_transfer_length -= fifo_length;

				/* If this is the last packet, set data end as well. */
				if (transfer_request->ux_slave_transfer_request_in_transfer_length == 0)
					/* Write to the Fifo.  Last packet. */
					_ux_dcd_stm32_fifo_write(dcd_stm32, ed->ux_dcd_stm32_ed_index, data_pointer,
							fifo_length, UX_TRUE);
				else
					/* Write to the Fifo.  More packets to come. */
					_ux_dcd_stm32_fifo_write(dcd_stm32, ed->ux_dcd_stm32_ed_index, data_pointer,
							fifo_length, UX_FALSE);
			}
		}
	}

	/* We are done. */
	return (UX_SUCCESS);
}
