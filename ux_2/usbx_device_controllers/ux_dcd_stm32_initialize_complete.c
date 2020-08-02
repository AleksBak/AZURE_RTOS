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
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_dcd_stm32.h"
#include "ux_device_stack.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    _ux_dcd_stm32_initialize_complete                     PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function completes the initialization of the USB slave         */
/*    controller for the STM32 chip.                                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    (ux_slave_dcd_function)               Process the DCD function      */
/*    _ux_utility_descriptor_parse          Parse descriptor              */
/*    _ux_utility_memory_allocate           Allocate memory               */
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
UINT _ux_dcd_stm32_initialize_complete(VOID)
{
	/* Get the pointer to the DCD. */
	UX_SLAVE_DCD* dcd = &_ux_system_slave->ux_system_slave_dcd;

	/* Get the pointer to the STM32 DCD. */
	UX_DCD_STM32* dcd_stm32 = (UX_DCD_STM32*)dcd->ux_slave_dcd_controller_hardware;

	/* Get the pointer to the device. */
	UX_SLAVE_DEVICE* device = &_ux_system_slave->ux_system_slave_device;

	/* Are we in DFU mode ? If so, check if we are in a Reset mode. */
	if (_ux_system_slave->ux_system_slave_device_dfu_state_machine ==
			UX_SYSTEM_DFU_STATE_APP_DETACH)
	{
		/* The device is now in DFU reset mode. Switch to the DFU device framework. */
		_ux_system_slave->ux_system_slave_device_framework = _ux_system_slave
				->ux_system_slave_dfu_framework;
		_ux_system_slave->ux_system_slave_device_framework_length = _ux_system_slave
				->ux_system_slave_dfu_framework_length;
	}
	else
	{
		/* Set State to App Idle. */
		_ux_system_slave->ux_system_slave_device_dfu_state_machine = UX_SYSTEM_DFU_STATE_APP_IDLE;

		/* Check the speed and set the correct descriptor. */
		if (_ux_system_slave->ux_system_slave_speed == UX_FULL_SPEED_DEVICE)
		{
			/* The device is operating at full speed. */
			_ux_system_slave->ux_system_slave_device_framework = _ux_system_slave
					->ux_system_slave_device_framework_full_speed;
			_ux_system_slave->ux_system_slave_device_framework_length = _ux_system_slave
					->ux_system_slave_device_framework_length_full_speed;
		}
		else
		{
			/* The device is operating at high speed. */
			_ux_system_slave->ux_system_slave_device_framework = _ux_system_slave
					->ux_system_slave_device_framework_high_speed;
			_ux_system_slave->ux_system_slave_device_framework_length = _ux_system_slave
					->ux_system_slave_device_framework_length_high_speed;
		}
	}

	/* Flush the Endpoint Fifos. */
	_ux_dcd_stm32_fifo_flush(dcd_stm32, UX_DCD_STM32_FLUSH_TX_FIFO, UX_DCD_STM32_FLUSH_FIFO_ALL);
	_ux_dcd_stm32_fifo_flush(dcd_stm32, UX_DCD_STM32_FLUSH_RX_FIFO, UX_DCD_STM32_FLUSH_FIFO_ALL);

	/* Clear all pending device interrupts. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINT, 0xFFFFFFFF);

	/*--------------------------------------------------------------------------------------------*/

	ULONG ed_index;
	ULONG stm32_register;

	/* Reset the IN endpoints. */
	for (ed_index = 0; ed_index < UX_DCD_STM32_MAX_ED; ed_index++)
	{
		/* Read the current endpoint control register. */
		stm32_register = _ux_dcd_stm32_register_read(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

		/* Check if the endpoint is already enabled. */
		if (stm32_register & UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA)
		{
			/* Set the endpoint disabled bit and SNAK. */
			stm32_register = UX_DCD_STM32_OTG_FS_DIEPCTL_SNAK |
					UX_DCD_STM32_OTG_FS_DIEPCTL_EPDIS;
		}
		else
			/* Reset register. Nothing to do. */
			stm32_register = 0;

		/* Set the Endpoint register. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE), stm32_register);

		/* Reset the DIEPSIZ register of the endpoint. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTSIZ +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE), 0);

		/* Reset the interrupt register for the endpoint. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPINT +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE), UX_DCD_STM32_OTG_FS_DIEPINT_ALL);
	}

	/* Reset the OUT endpoints. */
	for (ed_index = 0; ed_index < UX_DCD_STM32_MAX_ED; ed_index++)
	{
		/* Read the current endpoint control register. */
		stm32_register = _ux_dcd_stm32_register_read(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPCTL +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

		/* Check if the endpoint is already enabled. */
		if (stm32_register & UX_DCD_STM32_OTG_FS_DOEPCTL_EPENA)
		{
			/* Set the endpoint disabled bit and SNAK. */
			stm32_register = UX_DCD_STM32_OTG_FS_DOEPCTL_SNAK |
					UX_DCD_STM32_OTG_FS_DOEPCTL_EPDIS;
		}
		else
			/* Reset register. Nothing to do. */
			stm32_register = 0;

		/* Set the Endpoint register. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPCTL +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE), stm32_register);

		/* Reset the DIEPSIZ register of the endpoint. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPTSIZ +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE), 0);

		/* Reset the interrupt register for the endpoint. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPINT +
				(ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE), UX_DCD_STM32_OTG_FS_DOEPINT_ALL);
	}

	/* Set the DOEPMSK register. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPMSK,
			UX_DCD_STM32_OTG_FS_DOEPMSK_XFRCM | UX_DCD_STM32_OTG_FS_DOEPMSK_STUPM |
			UX_DCD_STM32_OTG_FS_DOEPMSK_EPDM | UX_DCD_STM32_OTG_FS_DOEPMSK_B2BSTUP);

	/* Set the DIEPMSK register. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPMSK,
			UX_DCD_STM32_OTG_FS_DIEPMSK_XFRCM | UX_DCD_STM32_OTG_FS_DIEPMSK_EPDM |
			UX_DCD_STM32_OTG_FS_DIEPMSK_TOM);

	/* Reset the Global IN/OUT NAK. */
	_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DCTL,
			UX_DCD_STM32_OTG_FS_DCTL_CGONAK | UX_DCD_STM32_OTG_FS_DCTL_CGINAK);

	/* Reset the device address. */
	_ux_dcd_stm32_address_set(dcd_stm32, 0);

	/*--------------------------------------------------------------------------------------------*/

	/* Get the device framework pointer. */
	UCHAR* device_framework = _ux_system_slave->ux_system_slave_device_framework;

	/* And create the decompressed device descriptor structure. */
	_ux_utility_descriptor_parse(device_framework, _ux_system_device_descriptor_structure,
			UX_DEVICE_DESCRIPTOR_ENTRIES, (UCHAR*)&device->ux_slave_device_descriptor);

	/* Now we create a transfer request to accept the first SETUP packet and get the ball running.
	 * First get the address of the endpoint transfer request container. */
	UX_SLAVE_TRANSFER* transfer_request =
			&device->ux_slave_device_control_endpoint.ux_slave_endpoint_transfer_request;

	/* Set the timeout to be for Control Endpoint. */
	transfer_request->ux_slave_transfer_request_timeout = MS_TO_TICK(UX_CONTROL_TRANSFER_TIMEOUT);

	/* Adjust the current data pointer as well. */
	transfer_request->ux_slave_transfer_request_current_data_pointer =
			transfer_request->ux_slave_transfer_request_data_pointer;

	/* Update the transfer request endpoint pointer with the default endpoint. */
	transfer_request->ux_slave_transfer_request_endpoint =
			&device->ux_slave_device_control_endpoint;

	/* The control endpoint max packet size needs to be filled manually in its descriptor. */
	transfer_request->ux_slave_transfer_request_endpoint->ux_slave_endpoint_descriptor
			.wMaxPacketSize = device->ux_slave_device_descriptor.bMaxPacketSize0;

	/* On the control endpoint, always expect the maximum. */
	transfer_request->ux_slave_transfer_request_requested_length =
			device->ux_slave_device_descriptor.bMaxPacketSize0;

	/* Attach the control endpoint to the transfer request. */
	transfer_request->ux_slave_transfer_request_endpoint =
			&device->ux_slave_device_control_endpoint;

	/* Create the default control endpoint attached to the device. Once this endpoint is enabled,
	 * the host can then send a setup packet. The device controller will receive it and will call
	 * the setup function module. */
	dcd->ux_slave_dcd_function(dcd, UX_DCD_CREATE_ENDPOINT,
			(VOID*)&device->ux_slave_device_control_endpoint);

	/* Ensure the control endpoint is properly reset. */
	device->ux_slave_device_control_endpoint.ux_slave_endpoint_state = UX_ENDPOINT_RESET;

	/* Mark the phase as SETUP. */
	transfer_request->ux_slave_transfer_request_type = UX_TRANSFER_PHASE_SETUP;

	/* Mark this transfer request as pending. */
	transfer_request->ux_slave_transfer_request_status = UX_TRANSFER_STATUS_PENDING;

	/* Ask for 8 bytes of the SETUP packet. */
	transfer_request->ux_slave_transfer_request_requested_length = UX_SETUP_SIZE;
	transfer_request->ux_slave_transfer_request_in_transfer_length = UX_SETUP_SIZE;

	/* Reset the number of bytes sent/received. */
	transfer_request->ux_slave_transfer_request_actual_length = 0;

	/* Call the DCD driver transfer function. */
	dcd->ux_slave_dcd_function(dcd, UX_DCD_TRANSFER_REQUEST, transfer_request);

	/* Check the status change callback. */
	if (_ux_system_slave->ux_system_slave_change_function != UX_NULL)
	{
		/* Inform the application if a callback function was programmed. */
		_ux_system_slave->ux_system_slave_change_function(UX_DEVICE_ATTACHED);
	}

	/* If trace is enabled, insert this event into the trace buffer. */
	UX_TRACE_IN_LINE_INSERT(UX_TRACE_DEVICE_STACK_CONNECT, 0, 0, 0, 0, UX_TRACE_DEVICE_STACK_EVENTS,
			0, 0)

	/* If trace is enabled, register this object. */
	UX_TRACE_OBJECT_REGISTER(UX_TRACE_DEVICE_OBJECT_TYPE_DEVICE, device, 0, 0, 0)

	/* We are now ready for the USB device to accept the first packet when connected. */
	return (UX_SUCCESS);
}
