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
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _ux_device_stack_transfer_request                   PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function performs a USB transaction. On entry the              */
/*    transfer request gives the endpoint pipe selected for this          */
/*    transaction and the parameters associated with the transfer         */
/*    (data payload, length of transaction).                              */
/*    This function is called when a class or the stack wants to          */
/*    transfer data to the host. The host always polls the device         */
/*    but the device can prepare data in advance.                         */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    transfer_request                      Pointer to transfer request   */
/*    slave_length                          Length returned by host       */
/*    host_length                           Length asked by host          */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    (ux_slave_dcd_function)               Slave DCD dispatch function   */
/*    _ux_utility_delay_ms                  Delay ms                      */
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
UINT _ux_device_stack_transfer_request(UX_SLAVE_TRANSFER* transfer_request, ULONG slave_length,
		ULONG host_length)
{
	TX_INTERRUPT_SAVE_AREA

	/* Do we have to skip this transfer?  */
	if (transfer_request->ux_slave_transfer_request_status_phase_ignore == UX_TRUE)
		return (UX_SUCCESS);

	/* Disable interrupts to prevent the disconnection ISR from preempting us
	 * while we check the device state and set the transfer status. */
	TX_DISABLE

	/* Get the device state. */
	ULONG device_state = _ux_system_slave->ux_system_slave_device.ux_slave_device_state;

	/* We can only transfer when the device is ATTACHED, ADDRESSED OR CONFIGURED. */
	if ((device_state == UX_DEVICE_ATTACHED) || (device_state == UX_DEVICE_ADDRESSED)
			|| (device_state == UX_DEVICE_CONFIGURED))
		/* Set the transfer to pending. */
		transfer_request->ux_slave_transfer_request_status = UX_TRANSFER_STATUS_PENDING;
	else
	{
		/* The device is in an invalid state. Restore interrupts and return error. */
		TX_RESTORE
		return (UX_TRANSFER_NOT_READY);
	}

	/* Restore interrupts. */
	TX_RESTORE

	/* If trace is enabled, insert this event into the trace buffer. */
	UX_TRACE_IN_LINE_INSERT(UX_TRACE_DEVICE_STACK_TRANSFER_REQUEST, transfer_request, 0, 0, 0,
			UX_TRACE_DEVICE_STACK_EVENTS, 0, 0)

	/* Get the pointer to the DCD. */
	UX_SLAVE_DCD* dcd = &_ux_system_slave->ux_system_slave_dcd;

	/* Get the endpoint associated with this transaction. */
	UX_SLAVE_ENDPOINT* endpoint = transfer_request->ux_slave_transfer_request_endpoint;

	/* If the endpoint is non Control, check the endpoint direction and set the data phase direction. */
	if ((endpoint->ux_slave_endpoint_descriptor.bmAttributes & UX_MASK_ENDPOINT_TYPE)
			!= UX_CONTROL_ENDPOINT)
	{
		/* Check if the endpoint is STALLED. In this case, we must refuse
		 * the transaction until the endpoint has been reset by the host. */
		while (endpoint->ux_slave_endpoint_state == UX_ENDPOINT_HALTED)
			/* Wait for 100ms for endpoint to be reset by a CLEAR_FEATURE command. */
			_ux_utility_delay_ms(100);

		/* Isolate the direction from the endpoint address. */
		if ((endpoint->ux_slave_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION)
				== UX_ENDPOINT_IN)
			transfer_request->ux_slave_transfer_request_phase = UX_TRANSFER_PHASE_DATA_OUT;
		else
			transfer_request->ux_slave_transfer_request_phase = UX_TRANSFER_PHASE_DATA_IN;
	}

	/* See if we need to force a zero length packet at the end of the transfer. This happens on
	 * a DATA IN and when the host requested length is not met and the last packet is on a boundary.
	 * If slave_length is zero, then it is a explicit ZLP request, no need to force ZLP. */
	if ((transfer_request->ux_slave_transfer_request_phase == UX_TRANSFER_PHASE_DATA_OUT) &&
			(slave_length != 0) && (host_length != slave_length) &&
			(slave_length % endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize) == 0)
	{
		/* If so force Zero Length Packet. */
		transfer_request->ux_slave_transfer_request_force_zlp = UX_TRUE;
	}
	else
	{
		/* Condition is not met, do not force a Zero Length Packet. */
		transfer_request->ux_slave_transfer_request_force_zlp = UX_FALSE;
	}

	/* Reset the number of bytes sent/received. */
	transfer_request->ux_slave_transfer_request_actual_length = 0;

	/* Determine how many bytes to send in this transaction.
	 * We keep track of the original length and have a working length. */
	transfer_request->ux_slave_transfer_request_requested_length = slave_length;
	transfer_request->ux_slave_transfer_request_in_transfer_length = slave_length;

	/* Save the buffer pointer. */
	transfer_request->ux_slave_transfer_request_current_data_pointer =
			transfer_request->ux_slave_transfer_request_data_pointer;

	/* Call the DCD driver transfer function.   */
	UINT status = dcd->ux_slave_dcd_function(dcd, UX_DCD_TRANSFER_REQUEST, transfer_request);

	/* And return the status. */
	return (status);
}
