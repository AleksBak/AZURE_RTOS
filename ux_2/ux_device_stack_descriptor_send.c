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
/**   Device Stack                                                        */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define UX_SOURCE_CODE

/* Include necessary system files. */
#include "ux_api.h"
#include "ux_device_stack.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    _ux_device_stack_descriptor_send                      PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is used by the device side to return a descriptor     */
/*    to the host. This descriptor can be a device descriptor,            */
/*    a configuration descriptor or a string descriptor.                  */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    descriptor_type                The nature of the descriptor:        */
/*                                   UX_DEVICE_DESCRIPTOR_ITEM            */
/*                                   UX_CONFIGURATION_DESCRIPTOR_ITEM     */
/*                                   UX_STRING_DESCRIPTOR_ITEM            */
/*                                   UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM  */
/*                                   UX_OTHER_SPEED_DESCRIPTOR_ITEM       */
/*    descriptor_index               Index of descriptor                  */
/*    host_length                    Length requested by host             */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    (ux_slave_dcd_function)               DCD dispatch function         */
/*    _ux_device_stack_transfer_request     Process transfer request      */
/*    _ux_utility_descriptor_parse          Parse descriptor              */
/*    _ux_utility_memory_copy               Memory copy                   */
/*    _ux_utility_short_get                 Get short value               */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application                                                         */
/*    Device Stack                                                        */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT _ux_device_stack_descriptor_send(ULONG descriptor_type, ULONG request_index, ULONG host_length)
{
	/* If trace is enabled, insert this event into the trace buffer. */
	UX_TRACE_IN_LINE_INSERT(UX_TRACE_DEVICE_STACK_DESCRIPTOR_SEND, descriptor_type, request_index,
			0, 0, UX_TRACE_DEVICE_STACK_EVENTS, 0, 0)

	/* Get the pointer to the DCD. */
	UX_SLAVE_DCD* dcd = &_ux_system_slave->ux_system_slave_dcd;

	/* Get the pointer to the device. */
	UX_SLAVE_DEVICE* device = &_ux_system_slave->ux_system_slave_device;

	/* Get the control endpoint associated with the device. */
	UX_SLAVE_ENDPOINT* endpoint = &device->ux_slave_device_control_endpoint;

	/* Get the pointer to the transfer request associated with the endpoint. */
	UX_SLAVE_TRANSFER* transfer_request = &endpoint->ux_slave_endpoint_transfer_request;

	/* Set the direction to OUT. */
	transfer_request->ux_slave_transfer_request_phase = UX_TRANSFER_PHASE_DATA_OUT;

	/* Isolate the descriptor index. */
	ULONG descriptor_index = descriptor_type & 0xff;

	/* Reset the parsed index. */
	ULONG parsed_descriptor_index = 0;

	/* Shift the descriptor type in the low byte field. */
	descriptor_type = (UCHAR)((descriptor_type >> 8) & 0xff);

	/*--------------------------------------------------------------------------------------------*/

	ULONG length;
	UINT status = UX_ERROR;

	UCHAR* device_framework;
	UCHAR* device_framework_end;
	ULONG device_framework_length;
	ULONG descriptor_length;

	UX_CONFIGURATION_DESCRIPTOR configuration_descriptor;
	ULONG configuration_descriptor_length;

	UCHAR* string_memory;

	/* What type of descriptor do we need to return?  */
	switch (descriptor_type)
	{
		case UX_DEVICE_DESCRIPTOR_ITEM:						// 1
			/* Setup the length appropriately. */
			length = (host_length > UX_DEVICE_DESCRIPTOR_LENGTH) ? UX_DEVICE_DESCRIPTOR_LENGTH :
					host_length;

			/* Copy the device descriptor into the transfer request memory. */
			_ux_utility_memory_copy(transfer_request->ux_slave_transfer_request_data_pointer,
					_ux_system_slave->ux_system_slave_device_framework, length);

			/* Perform the data transfer.
			 * transfer_request->ux_slave_transfer_request_endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize == 0 ?*/
			status = _ux_device_stack_transfer_request(transfer_request, length, host_length);
			break;

		case UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM:			// 6
			/* Setup the length appropriately. */
			length = (host_length > UX_DEVICE_QUALIFIER_DESCRIPTOR_LENGTH) ?
					UX_DEVICE_QUALIFIER_DESCRIPTOR_LENGTH : host_length;

			/* We may or may not have a device qualifier descriptor. */
			device_framework = _ux_system_slave->ux_system_slave_device_framework;
			device_framework_length = _ux_system_slave->ux_system_slave_device_framework_length;
			device_framework_end = device_framework + device_framework_length;

			/* Parse the device framework and locate a device qualifier descriptor. */
			while (device_framework < device_framework_end)
			{
				/* Get the type of the current descriptor. */
				descriptor_type = *(device_framework + 1);

				/* And its length. */
				descriptor_length = (ULONG)*device_framework;

				/* Check if this is a device qualifier descriptor. */
				if (descriptor_type == UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM)
				{
					/* Copy the device qualifier descriptor into the transfer request memory. */
					_ux_utility_memory_copy(
							transfer_request->ux_slave_transfer_request_data_pointer,
							device_framework, length);

					/* Perform the data transfer. */
					status = _ux_device_stack_transfer_request(transfer_request, length,
							host_length);
					break;
				}

				/* Adjust what is left of the device framework. (optional calculation) */
				device_framework_length -= descriptor_length;

				/* Point to the next descriptor. */
				device_framework += descriptor_length;
			}

			break;

		case UX_OTG_DESCRIPTOR_ITEM:						// 9
			/* Setup the length appropriately. */
			length = (host_length > UX_OTG_DESCRIPTOR_LENGTH) ? UX_OTG_DESCRIPTOR_LENGTH :
					host_length;

			/* We may or may not have a OTG descriptor. */
			device_framework = _ux_system_slave->ux_system_slave_device_framework;
			device_framework_length = _ux_system_slave->ux_system_slave_device_framework_length;
			device_framework_end = device_framework + device_framework_length;

			/* Parse the device framework and locate a OTG descriptor. */
			while (device_framework < device_framework_end)
			{
				/* Get the type of the current descriptor. */
				descriptor_type = *(device_framework + 1);

				/* And its length. */
				descriptor_length = (ULONG)*device_framework;

				/* Check if this is a OTG descriptor. */
				if (descriptor_type == UX_OTG_DESCRIPTOR_ITEM)
				{
					/* Copy the device OTG descriptor into the transfer request memory. */
					_ux_utility_memory_copy(
							transfer_request->ux_slave_transfer_request_data_pointer,
							device_framework, length);

					/* Perform the data transfer. */
					status = _ux_device_stack_transfer_request(transfer_request, length,
							host_length);
					break;
				}

				/* Adjust what is left of the device framework. (optional calculation) */
				device_framework_length -= descriptor_length;

				/* Point to the next descriptor. */
				device_framework += descriptor_length;
			}
			break;

		case UX_BOS_DESCRIPTOR_ITEM:						// F
			/* We may or may not have a BOS descriptor. */
			device_framework = _ux_system_slave->ux_system_slave_device_framework;
			device_framework_length = _ux_system_slave->ux_system_slave_device_framework_length;
			device_framework_end = device_framework + device_framework_length;

			/* Parse the device framework and locate a device qualifier descriptor. */
			while (device_framework < device_framework_end)
			{
				/* Get the type of the current descriptor. */
				descriptor_type = *(device_framework + 1);

				/* And its length. */
				descriptor_length = (ULONG)*device_framework;

				/* Check if this is a device qualifier descriptor. */
				if (descriptor_type == UX_BOS_DESCRIPTOR_ITEM)
				{
					/* wTotalLength - Length of this BOS descriptor and all of its sub descriptors */
					length = _ux_utility_short_get(device_framework + 2);

//					/* Setup the length appropriately. */
//					if (host_length > length)
//						length = host_length;

					/* Copy the device qualifier descriptor into the transfer request memory. */
					_ux_utility_memory_copy(
							transfer_request->ux_slave_transfer_request_data_pointer,
							device_framework, length);

					/* Perform the data transfer. */
					status = _ux_device_stack_transfer_request(transfer_request, length,
							host_length);
					break;
				}

				/* Adjust what is left of the device framework. (optional calculation) */
				device_framework_length -= descriptor_length;

				/* Point to the next descriptor. */
				device_framework += descriptor_length;
			}

			break;

		case UX_OTHER_SPEED_DESCRIPTOR_ITEM:				// 7
			/* This request is used by the host to find out the capability of this device if it was
			 * running at full speed. The behavior is the same as in a GET_CONFIGURATIOn descriptor
			 * but we do not use the current device framework but rather the full speed framework. */
			device_framework = _ux_system_slave->ux_system_slave_device_framework_full_speed;
			device_framework_length =
					_ux_system_slave->ux_system_slave_device_framework_length_full_speed;
			device_framework_end = device_framework + device_framework_length;

			/* Parse the device framework and locate a configuration descriptor. */
			while (device_framework < device_framework_end)
			{
				/* Get the type of the current descriptor. */
				descriptor_type = *(device_framework + 1);

				/* And its length. */
				descriptor_length = (ULONG)*device_framework;

				/* Check if this is a configuration descriptor. We are cheating here. Instead of
				 * creating a OTHER SPEED descriptor, we simply scan the configuration descriptor
				 * for the Full Speed framework and return this configuration after we manually
				 * changed the configuration descriptor item into a Other Speed Descriptor. */
				if (descriptor_type == UX_CONFIGURATION_DESCRIPTOR_ITEM)
				{
					/* Check the index. It must be the same as the one requested. */
					if (parsed_descriptor_index == descriptor_index)
					{
						/* Parse the configuration descriptor. */
						_ux_utility_descriptor_parse(device_framework,
								_ux_system_configuration_descriptor_structure,
								UX_CONFIGURATION_DESCRIPTOR_ENTRIES,
								(UCHAR*)&configuration_descriptor);

						/* Get the length of entire configuration descriptor. */
						configuration_descriptor_length = configuration_descriptor.wTotalLength;

						/* Ensure the host does not demand a length beyond our descriptor
						 * (Windows does that) and do not return more than what is allowed. */
						length = (configuration_descriptor_length < host_length) ?
								configuration_descriptor_length : host_length;

						/* Check buffer length, since total descriptors length may exceed buffer... */
						if (length > UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH)
						{
							/* Error trap. */
							_ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD,
									UX_SYSTEM_CONTEXT_DEVICE_STACK, UX_MEMORY_INSUFFICIENT);

							/* If trace is enabled, insert this event into the trace buffer. */
							UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_MEMORY_INSUFFICIENT, device,
									0, 0, UX_TRACE_ERRORS, 0, 0)

							/* Stall the endpoint. */
							status = dcd->ux_slave_dcd_function(dcd, UX_DCD_STALL_ENDPOINT,
									endpoint);
							break;
						}

						/* Copy the device descriptor into the transfer request memory. */
						_ux_utility_memory_copy(
								transfer_request->ux_slave_transfer_request_data_pointer,
								device_framework, length);

						/* Now we need to hack the found descriptor because this request expect a
						 * OTHER_SPEED descriptor instead of the regular CONFIGURATION descriptor. */
						*(transfer_request->ux_slave_transfer_request_data_pointer + 1) =
								UX_OTHER_SPEED_DESCRIPTOR_ITEM;

						/* We can return the configuration descriptor. */
						status = _ux_device_stack_transfer_request(transfer_request, length,
								host_length);
						break;
					}
					else
					{
						/* There may be more configuration descriptors in this framework. */
						parsed_descriptor_index++;
					}
				}

				/* Adjust what is left of the device framework. (optional calculation) */
				device_framework_length -= descriptor_length;

				/* Point to the next descriptor. */
				device_framework += descriptor_length;
			}
			break;

		case UX_CONFIGURATION_DESCRIPTOR_ITEM:				// 2
			/* We may have multiple configurations !, the index will tell us what
			 * configuration descriptor we need to return. */
			device_framework = _ux_system_slave->ux_system_slave_device_framework;
			device_framework_length = _ux_system_slave->ux_system_slave_device_framework_length;
			device_framework_end = device_framework + device_framework_length;

			/* Parse the device framework and locate a configuration descriptor. */
			while (device_framework < device_framework_end)
			{
				/* Get the type of the current descriptor. */
				descriptor_type = *(device_framework + 1);

				/* And its length. */
				descriptor_length = (ULONG)*device_framework;

				/* Check if this is a configuration descriptor. */
				if (descriptor_type == UX_CONFIGURATION_DESCRIPTOR_ITEM)
				{
					/* Check the index. It must be the same as the one requested. */
					if (parsed_descriptor_index == descriptor_index)
					{
						/* Parse the configuration descriptor. */
						_ux_utility_descriptor_parse(device_framework,
								_ux_system_configuration_descriptor_structure,
								UX_CONFIGURATION_DESCRIPTOR_ENTRIES,
								(UCHAR*)&configuration_descriptor);

						/* Get the length of entire configuration descriptor. */
						configuration_descriptor_length = configuration_descriptor.wTotalLength;

						/* Ensure the host does not demand a length beyond our descriptor
						 * (Windows does that) and do not return more than what is allowed. */
						length = (configuration_descriptor_length < host_length) ?
								configuration_descriptor_length : host_length;

						/* Check buffer length, since total descriptors length may exceed buffer... */
						if (length > UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH)
						{
							/* Error trap. */
							_ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD,
									UX_SYSTEM_CONTEXT_DEVICE_STACK, UX_MEMORY_INSUFFICIENT);

							/* If trace is enabled, insert this event into the trace buffer. */
							UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_MEMORY_INSUFFICIENT, device,
									0, 0, UX_TRACE_ERRORS, 0, 0)

							/* Stall the endpoint. */
							status = dcd->ux_slave_dcd_function(dcd, UX_DCD_STALL_ENDPOINT,
									endpoint);
							break;
						}

						/* Copy the device descriptor into the transfer request memory. */
						_ux_utility_memory_copy(
								transfer_request->ux_slave_transfer_request_data_pointer,
								device_framework, length);

						/* We can return the configuration descriptor. */
						status = _ux_device_stack_transfer_request(transfer_request, length,
								host_length);
						break;
					}
					else
					{
						/* There may be more configuration descriptors in this framework. */
						parsed_descriptor_index++;
					}
				}

				/* Adjust what is left of the device framework. (optional calculation) */
				device_framework_length -= descriptor_length;

				/* Point to the next descriptor. */
				device_framework += descriptor_length;
			}
			break;

		case UX_STRING_DESCRIPTOR_ITEM:						// 3
			/* We need to filter for the index 0 which is the language ID string. */
			if (descriptor_index == 0)
			{
				/* We need to check request buffer size in case it's possible exceed. */
				if (_ux_system_slave->ux_system_slave_language_id_framework_length
						+ 2> UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH)
				{
					/* Error trap. */
					_ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD, UX_SYSTEM_CONTEXT_DEVICE_STACK,
							UX_MEMORY_INSUFFICIENT);

					/* If trace is enabled, insert this event into the trace buffer. */
					UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_MEMORY_INSUFFICIENT, device, 0, 0,
							UX_TRACE_ERRORS, 0, 0)

					/* Stall the endpoint. */
					status = dcd->ux_slave_dcd_function(dcd, UX_DCD_STALL_ENDPOINT, endpoint);
					break;
				}

				/* We have a request to send back the language ID list. Use the transfer request buffer. */
				string_memory = transfer_request->ux_slave_transfer_request_data_pointer;

				/* Store the total length of the response. */
				*string_memory =
						(UCHAR)(_ux_system_slave->ux_system_slave_language_id_framework_length + 2);

				/* Store the descriptor type. */
				*(string_memory + 1) = UX_STRING_DESCRIPTOR_ITEM;

				/* Store the language ID into the buffer. */
				_ux_utility_memory_copy(string_memory + 2,
						_ux_system_slave->ux_system_slave_language_id_framework,
						_ux_system_slave->ux_system_slave_language_id_framework_length);

				/* Filter the length asked/required. */
				if (host_length
						> _ux_system_slave->ux_system_slave_language_id_framework_length + 2)
					length = _ux_system_slave->ux_system_slave_language_id_framework_length + 2;
				else
					length = host_length;

				/* We can return the string language ID descriptor. */
				status = _ux_device_stack_transfer_request(transfer_request, length, host_length);
			}
			else
			{
				/* The host wants a specific string index returned.
				 * Get the string framework pointer and length. */
				UCHAR* string_framework = _ux_system_slave->ux_system_slave_string_framework;
				ULONG string_framework_length =
						_ux_system_slave->ux_system_slave_string_framework_length;

				/* We search through the string framework until we find the right index.
				 * The index is in the lower byte of the descriptor type. */
				while (string_framework_length != 0)
				{
					/* Ensure we have the correct language page. */
					ULONG curr_index = _ux_utility_short_get(string_framework);
					if (curr_index == request_index)
					{
						/* Check the index. */
						if (*(string_framework + 2) == descriptor_index)
						{
							/* We need to check request buffer size in case it's possible exceed. */
							if (((*(string_framework + 3) * 2) + 2)
									> UX_SLAVE_REQUEST_CONTROL_MAX_LENGTH)
							{
								/* Error trap. */
								_ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD,
										UX_SYSTEM_CONTEXT_DEVICE_STACK, UX_MEMORY_INSUFFICIENT);

								/* If trace is enabled, insert this event into the trace buffer. */
								UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_MEMORY_INSUFFICIENT,
										device, 0, 0, UX_TRACE_ERRORS, 0, 0)

								/* Stall the endpoint. */
								status = dcd->ux_slave_dcd_function(dcd, UX_DCD_STALL_ENDPOINT,
										endpoint);
								break;
							}

							/* We have a request to send back a string. Use the transfer request buffer. */
							string_memory =
									transfer_request->ux_slave_transfer_request_data_pointer;

							/* Store the length in the string buffer. The length of the string
							 * descriptor is stored in the third byte, hence the ' + 3'.
							 * The encoding must be in 16-bit unicode, hence the '*2'.
							 * The length includes the size of the length itself
							 * as well as the descriptor type, hence the ' + 2'. */
							*string_memory = (UCHAR)((*(string_framework + 3) * 2) + 2);

							/* Store the Descriptor type. */
							*(string_memory + 1) = UX_STRING_DESCRIPTOR_ITEM;

							/* Create the Unicode string. */
							ULONG string_length;
							for (string_length = 0; string_length < *(string_framework + 3);
									string_length++)
							{
								/* Insert a Unicode byte. */
								*(string_memory + 2 + (string_length * 2)) = *(string_framework + 4
										+ string_length);

								/* Insert a zero after the Unicode byte. */
								*(string_memory + 2 + (string_length * 2) + 1) = 0;
							}

							/* Filter the length asked/required. */
							if (host_length > (UINT)((*(string_framework + 3) * 2) + 2))
								length = (ULONG)((*(string_framework + 3) * 2) + 2);
							else
								length = host_length;

							/* We can return the string descriptor. */
							status = _ux_device_stack_transfer_request(transfer_request, length,
									host_length);
							break;
						}
					}

					/* This is the wrong string descriptor, jump to the next. */
					string_framework_length -= (ULONG)*(string_framework + 3) + 4;
					string_framework += (ULONG)*(string_framework + 3) + 4;
				}

				/* Have we exhausted all the string descriptors? */
				if (string_framework_length == 0)
				{
					/* Could not find the required string index. Stall the endpoint. */
					dcd->ux_slave_dcd_function(dcd, UX_DCD_STALL_ENDPOINT, endpoint);
					return (UX_ERROR);
				}
			}
			break;

		default:
			/* Stall the endpoint. */
			dcd->ux_slave_dcd_function(dcd, UX_DCD_STALL_ENDPOINT, endpoint);
			return (UX_ERROR);
	}

	/* Return the status to the caller. */
	return (status);
}
