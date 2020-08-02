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
#include "ux_device_stack.h"
#include "ux_system.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    _ux_dcd_stm32_interrupt_handler                       PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function is the interrupt handler for the STM32 controller.    */
/*    The controller will trigger an interrupt when something happens on  */
/*    an endpoint whose mask has been set in the interrupt enable         */
/*    register, or when a bus reset is detected.                          */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _ux_dcd_stm32_initialize_complete     Complete initialization       */
/*    _ux_dcd_stm32_register_read           Read register                 */
/*    _ux_dcd_stm32_register_write          Write register                */
/*    _ux_dcd_stm32_transfer_callback       Process callback              */
/*    _ux_device_stack_disconnect           Disconnect device             */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    USBX Device Stack                                                   */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
VOID _ux_dcd_stm32_interrupt_handler(VOID)
{
//	ULONG stm32_pending_interrupt;
//	ULONG stm32_masked_interrupt;
//	ULONG endpoint_index;
//	ULONG endpoint_mask;
//	ULONG transfer_length;
//	ULONG transfer_status;
//	ULONG stm32_daint_interrupt;
//	ULONG stm32_dsts_register;
//	ULONG stm32_grxstp_register;
//	ULONG stm32_doepint_register;
//	ULONG stm32_diepint_register;
//	UX_SLAVE_TRANSFER* transfer_request;
//	UX_DCD_STM32_ED* ed;
//	UX_SLAVE_ENDPOINT* endpoint;
//	UX_SLAVE_DCD* dcd;
//	UX_DCD_STM32* dcd_stm32;
//	UX_SLAVE_DEVICE* device;

	/* Get the pointer to the DCD. */
	UX_SLAVE_DCD* dcd = &_ux_system_slave->ux_system_slave_dcd;

	/* Get the pointer to the STM32 DCD. */
	UX_DCD_STM32* dcd_stm32 = (UX_DCD_STM32*)dcd->ux_slave_dcd_controller_hardware;

	/* Get the pointer to the device. */
	UX_SLAVE_DEVICE* device = &_ux_system_slave->ux_system_slave_device;

	/* Read the interrupt status register from the controller. */
	ULONG stm32_pending_interrupt = _ux_dcd_stm32_register_read(dcd_stm32,
			UX_DCD_STM32_OTG_FS_GINTSTS);

	/* Mask only with the interrupts we have programmed. */
	ULONG stm32_masked_interrupt = _ux_dcd_stm32_register_read(dcd_stm32,
			UX_DCD_STM32_OTG_FS_GINTMSK);

	/* Source of interrupt must be masked. */
	stm32_pending_interrupt &= stm32_masked_interrupt;

	/*----- see 'stm32f7xx_hal_pcd.c' -> 'void HAL_PCD_IRQHandler(PCD_HandleTypeDef* hpcd)' ------*/

	/* Check if we have a SUSPEND. */
	if (stm32_pending_interrupt & UX_DCD_STM32_OTG_FS_GINTSTS_USBSUSP)
	{
		/* Clear the SUSPEND interrupt. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTSTS,
				UX_DCD_STM32_OTG_FS_GINTSTS_USBSUSP);

		/* Check the status change callback. */
		if (_ux_system_slave->ux_system_slave_change_function != UX_NULL)
		{
			/* Inform the application if a callback function was programmed. */
			_ux_system_slave->ux_system_slave_change_function(UX_DEVICE_SUSPENDED);
		}

		/* If the device is attached or configured, we have a disconnection signal. */
		if (device->ux_slave_device_state != UX_DEVICE_RESET)
			/* Device is reset, the behavior is the same as disconnection. */
			_ux_device_stack_disconnect();
	}

	/* Check if we have an RESUME. */
	if (stm32_pending_interrupt & UX_DCD_STM32_OTG_FS_GINTSTS_WKUINT)
	{
		/* Clear the RESUME interrupt. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTSTS,
				UX_DCD_STM32_OTG_FS_GINTSTS_WKUINT);

		/* Check the status change callback. */
		if (_ux_system_slave->ux_system_slave_change_function != UX_NULL)
		{
			/* Inform the application if a callback function was programmed. */
			_ux_system_slave->ux_system_slave_change_function(UX_DEVICE_RESUMED);
		}
	}

	/* Check the source of the interrupt. Is it Enumeration Done Interrupt (End of Bus Reset) ? */
	if (stm32_pending_interrupt & UX_DCD_STM32_OTG_FS_GINTSTS_ENUMDNE)
	{
		/* Clear the Enumeration done interrupt. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTSTS,
				UX_DCD_STM32_OTG_FS_GINTSTS_ENUMDNE);

		/* Check for bouncing RESET. */
		if (device->ux_slave_device_state != UX_DEVICE_ATTACHED
				&& device->ux_slave_device_state != UX_DEVICE_CONFIGURED)
		{
			/* Read the DSTS register to isolate speed. */
			ULONG stm32_dsts_register = _ux_dcd_stm32_register_read(dcd_stm32, UX_DCD_STM32_OTG_FS_DSTS);

			/* We have a device connection, read at what speed we are connected. */
			if ((stm32_dsts_register & UX_DCD_STM32_OTG_FS_DSTS_ENUMSPD_MASK)
					== UX_DCD_STM32_OTG_FS_DSTS_ENUMSPD_HS)
				/* We are connected at high speed. */
				_ux_system_slave->ux_system_slave_speed = UX_HIGH_SPEED_DEVICE;
			else
				/* We are connected at lower full speed. */
				_ux_system_slave->ux_system_slave_speed = UX_FULL_SPEED_DEVICE;

			/* Complete the device initialization. */
			_ux_dcd_stm32_initialize_complete();

			/* Mark the device as attached now. */
			device->ux_slave_device_state = UX_DEVICE_ATTACHED;
		}
	}

	/* Check the source of the interrupt. Is it RESET ? */
	if (stm32_pending_interrupt & UX_DCD_STM32_OTG_FS_GINTSTS_USBRST)
	{
		/* Clear the Reset interrupt. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTSTS,
				UX_DCD_STM32_OTG_FS_GINTSTS_USBRST);

		/* If the device is attached or configured, we have a disconnection signal. */
		if (device->ux_slave_device_state != UX_DEVICE_RESET)
			/* Device is reset, the behavior is the same as disconnection. */
			_ux_device_stack_disconnect();

		/* Mark the device as RESET now. */
		device->ux_slave_device_state = UX_DEVICE_RESET;
	}

	/*--------------------------------------------------------------------------------------------*/

	ULONG endpoint_index;
	UX_DCD_STM32_ED* ed;
	UX_SLAVE_TRANSFER* transfer_request;
	UX_SLAVE_ENDPOINT* endpoint;

	/* Check the source of the interrupt. Is RX FIFO non Empty interrupt ?
	 * Meaning we have received an OUT or SETUP token.
	 * Reading the FIFO will trigger a Transfer complete interrupt. */
	if (stm32_pending_interrupt & UX_DCD_STM32_OTG_FS_GINTSTS_RFXLVL)
	{
		/* Clear the RX FIFO non Empty interrupt. */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTSTS,
				UX_DCD_STM32_OTG_FS_GINTSTS_RFXLVL);

		/* Mask this interrupt for now. */
		_ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTMSK,
				UX_DCD_STM32_OTG_FS_GINTMSK_RFXLVLM);

		/* Get the GRXSTSP register. This tells us on what endpoint the INT happened. */
		ULONG stm32_grxstp_register = _ux_dcd_stm32_register_read(dcd_stm32,
				UX_DCD_STM32_OTG_FS_GRXSTSP);

		/* Calculate the endpoint index. */
		endpoint_index = stm32_grxstp_register & UX_DCD_STM32_OTG_FS_GRXSTSP_EPNUM_MASK;

		/* Get the physical endpoint associated with this endpoint. */
		ed = &dcd_stm32->ux_dcd_stm32_ed[endpoint_index];

		/* Get the logical endpoint from the physical endpoint. */
		endpoint = ed->ux_dcd_stm32_ed_endpoint;

		/* Isolate the transfer status. */
		ULONG transfer_status = (stm32_grxstp_register & UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_MASK)
				>> UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_SHIFT;

		/* Isolate the transfer length. */
		ULONG transfer_length = (stm32_grxstp_register & UX_DCD_STM32_OTG_FS_GRXSTSP_BCNT_MASK)
				>> UX_DCD_STM32_OTG_FS_GRXSTSP_BCNT_SHIFT;

		/* Get the pointer to the transfer request. */
		transfer_request = &endpoint->ux_slave_endpoint_transfer_request;

		/* Is this for a OUT endpoint or a SETUP packet ? */
		switch (transfer_status)
		{
			case UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_SETUP_RCVD:
				/* Read the Fifo and store the data into the setup buffer. */
				_ux_dcd_stm32_fifo_read(dcd_stm32, endpoint_index,
						transfer_request->ux_slave_transfer_request_setup, UX_SETUP_SIZE);

				/* Save the length in the ED payload. */
				ed->ux_dcd_stm32_ed_payload_length = transfer_length;

				break;

			case UX_DCD_STM32_OTG_FS_GRXSTSP_PKTSTS_OUT_RCVD:
				/* This is for a regular OUT endpoint. */
				_ux_dcd_stm32_fifo_read(dcd_stm32, endpoint_index,
						transfer_request->ux_slave_transfer_request_current_data_pointer,
						transfer_length);

				/* Adjust the buffer address. */
				transfer_request->ux_slave_transfer_request_current_data_pointer += transfer_length;

				/* Update the length of the data received. */
				transfer_request->ux_slave_transfer_request_actual_length += transfer_length;

				/* Save the length in the ED payload. */
				ed->ux_dcd_stm32_ed_payload_length = transfer_length;

				break;

			default:
				break;
		}

		/* Reenable this interrupt. */
		_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTMSK,
				UX_DCD_STM32_OTG_FS_GINTMSK_RFXLVLM);
	}

	/*----- see 'stm32f7xx_hal_pcd.c' -> 'void HAL_PCD_IRQHandler(PCD_HandleTypeDef* hpcd)' ------*/

	ULONG endpoint_mask;
	ULONG stm32_doepint_register;
	ULONG stm32_diepint_register;

	/* Check the source of the interrupt. Is it a IN or OUT endpoint interrupt ? */
	if (stm32_pending_interrupt & (UX_DCD_STM32_OTG_FS_GINTSTS_IEPINT |
			UX_DCD_STM32_OTG_FS_GINTSTS_OEPINT))
	{
		/* Read the DAINT register. Stored the IN/OUT individual endpoint interrupts. */
		ULONG stm32_daint_interrupt = _ux_dcd_stm32_register_read(dcd_stm32,
				UX_DCD_STM32_OTG_FS_DAINT);

		/* Parse the 32 bit indexed register. It is split in IEPINT/OEPINT. */
		for (endpoint_mask = 0; endpoint_mask < 32; endpoint_mask++)
		{
			/* Check for an interrupt to have occurred on a specific endpoint. */
			if (stm32_daint_interrupt & (1 << endpoint_mask))
			{
				/* Build the endpoint index adjusting the endpoint mask. */
				endpoint_index = endpoint_mask;

				/* If the endpoint mask is >= 16 we are in the OUT endpoints. */
				if (endpoint_mask >= 16)
				{
					/* Adjust the index. */
					endpoint_index -= 16;

					/* Get the physical endpoint associated with this endpoint. */
					ed = &dcd_stm32->ux_dcd_stm32_ed[endpoint_index];

					/* Reset the endpoint transfer status. */
					ed->ux_dcd_stm32_ed_transfer_status = UX_DCD_STM32_ED_TRANSFER_STATUS_IDLE;

					/* Get the register for the DOEPTINT. */
					stm32_doepint_register = _ux_dcd_stm32_register_read(dcd_stm32,
							UX_DCD_STM32_OTG_FS_DOEPINT +
									(endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE));

					/* Find out what triggered the interrupt.  Maybe SETUP ? */
					if (stm32_doepint_register & UX_DCD_STM32_OTG_FS_DOEPINT_STUP)
					{
						/* Flag the setup. */
						ed->ux_dcd_stm32_ed_transfer_status = UX_DCD_STM32_ED_TRANSFER_STATUS_SETUP;
					}

					/* Find out what triggered the interrupt.  Maybe XFRC ? */
					if (stm32_doepint_register & UX_DCD_STM32_OTG_FS_DOEPINT_XFRC)
					{
						/* Flag the transfer completion. */
						ed->ux_dcd_stm32_ed_transfer_status =
								UX_DCD_STM32_ED_TRANSFER_STATUS_OUT_COMPLETION;
					}
				}
				else
				{
					/* Get the physical endpoint associated with this endpoint. */
					ed = &dcd_stm32->ux_dcd_stm32_ed[endpoint_index];

					/* Reset the endpoint transfer status. */
					ed->ux_dcd_stm32_ed_transfer_status = UX_DCD_STM32_ED_TRANSFER_STATUS_IDLE;

					/* Get the register for the DIEPINT. */
					stm32_diepint_register = _ux_dcd_stm32_register_read(dcd_stm32,
							UX_DCD_STM32_OTG_FS_DIEPINT +
									(endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE));

					/* Find out what triggered the interrupt.  Maybe XFRC ? */
					if (stm32_diepint_register & UX_DCD_STM32_OTG_FS_DIEPINT_XFRC)
						/* Flag the transfer completion. */
						ed->ux_dcd_stm32_ed_transfer_status =
								UX_DCD_STM32_ED_TRANSFER_STATUS_IN_COMPLETION;
				}

				/* Get the logical endpoint from the physical endpoint. */
				endpoint = ed->ux_dcd_stm32_ed_endpoint;

				/* Get the pointer to the transfer request. */
				transfer_request = &endpoint->ux_slave_endpoint_transfer_request;

				/*--------------------------------------------------------------------------------*/

				/* Process the call back.  */
				_ux_dcd_stm32_transfer_callback(dcd_stm32, transfer_request);

				/*--------------------------------------------------------------------------------*/

				/* Now clean the interrupt that started this.  */
				/* If the endpoint mask is >= 16 we are in the OUT endpoints.  */
				if (endpoint_mask >= 16)
					/* Clean the interrupt in the register for the DOEPTINT.  */
					_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPINT +
							(endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE),
							stm32_doepint_register);
				else
					/* Clean the interrupt in the register for the DIEPTINT. */
					_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPINT +
							(endpoint_index * UX_DCD_STM32_ENDPOINT_CHANNEL_SIZE),
							stm32_diepint_register);
			}
		}
	}
}
