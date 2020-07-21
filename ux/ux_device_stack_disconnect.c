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
/*    _ux_device_stack_disconnect                           PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is called when the device gets disconnected from the  */
/*    host. All the device resources are freed.                           */
/*                                                                        */
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
/*    (ux_slave_class_entry_function)       Device class entry function   */
/*    (ux_slave_dcd_function)               DCD dispatch function         */
/*    _ux_device_stack_interface_delete     Delete interface              */
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
UINT _ux_device_stack_disconnect(VOID)
{
	/* Get the pointer to the DCD. */
	UX_SLAVE_DCD* dcd = &_ux_system_slave->ux_system_slave_dcd;

	/* Get the pointer to the device. */
	UX_SLAVE_DEVICE* device = &_ux_system_slave->ux_system_slave_device;

	/* If trace is enabled, insert this event into the trace buffer. */
	UX_TRACE_IN_LINE_INSERT(UX_TRACE_DEVICE_STACK_DISCONNECT, device, 0, 0, 0,
			UX_TRACE_DEVICE_STACK_EVENTS, 0, 0)

	/* If trace is enabled, register this object. */
	UX_TRACE_OBJECT_UNREGISTER(device);

	/* If the device was in the configured state, there may be interfaces attached to the configuration. */
	if (device->ux_slave_device_state == UX_DEVICE_CONFIGURED)
	{
		/* Get the pointer to the first interface. */
		UX_SLAVE_INTERFACE* interface = device->ux_slave_device_first_interface;

		UX_SLAVE_CLASS_COMMAND class_command;

		/* Parse all the interfaces if any. */
		while (interface != UX_NULL)
		{
			/* Build all the fields of the Class Command. */
			class_command.ux_slave_class_command_request = UX_SLAVE_CLASS_COMMAND_DEACTIVATE;
			class_command.ux_slave_class_command_interface = (VOID*)interface;

			/* Get the pointer to the class container of this interface. */
			UX_SLAVE_CLASS* class = interface->ux_slave_interface_class;

			/* Store the class container. */
			class_command.ux_slave_class_command_class_ptr = class;

			/* If there is a class container for this instance, deactivate it. */
			if (class != UX_NULL)
				/* Call the class with the DEACTIVATE signal. */
				class->ux_slave_class_entry_function(&class_command);

			/* Get the next interface. */
			UX_SLAVE_INTERFACE* next_interface = interface->ux_slave_interface_next_interface;

			/* Remove the interface and all endpoints associated with it. */
			_ux_device_stack_interface_delete(interface);

			/* Now we refresh the interface pointer. */
			interface = next_interface;
		}

		/* Mark the device as attached now. */
		device->ux_slave_device_state = UX_DEVICE_ATTACHED;
	}

	/*--------------------------------------------------------------------------------------------*/

	UINT status = UX_ERROR;

	/* If the device was attached, we need to destroy the control endpoint. */
	if (device->ux_slave_device_state == UX_DEVICE_ATTACHED)
		/* Now we can destroy the default control endpoint. */
		status = dcd->ux_slave_dcd_function(dcd, UX_DCD_DESTROY_ENDPOINT,
				(VOID*)&device->ux_slave_device_control_endpoint);

	/* We are reverting to configuration 0. */
	device->ux_slave_device_configuration_selected = 0;

	/* Set the device to be non attached. */
	device->ux_slave_device_state = UX_DEVICE_RESET;

	/* Check the status change callback. */
	if (_ux_system_slave->ux_system_slave_change_function != UX_NULL)
	{
		/* Inform the application if a callback function was programmed. */
		_ux_system_slave->ux_system_slave_change_function(UX_DEVICE_REMOVED);
	}

	/* Return the status to the caller. */
	return (status);
}
