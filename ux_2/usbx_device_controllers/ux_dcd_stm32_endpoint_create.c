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

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _ux_dcd_stm32_endpoint_create                       PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will create a physical endpoint.                      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_stm32                             Pointer to device controller  */
/*    endpoint                              Pointer to endpoint container */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _ux_dcd_stm32_endpoint_reset          Reset endpoint                */
/*    _ux_dcd_stm32_register_read           Read register                 */
/*    _ux_dcd_stm32_register_write          Write register                */
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
UINT _ux_dcd_stm32_endpoint_create(UX_DCD_STM32* dcd_stm32, UX_SLAVE_ENDPOINT* endpoint)
{
//	UX_DCD_STM32_ED* ed;
//	ULONG stm32_endpoint_index;
//	ULONG stm32_endpoint_register;
//	ULONG stm32_endpoint_address;

	/* The endpoint index in the array of the STM32 must match the endpoint number.
	 * The STM32 has 4 endpoints maximum. Each can be IN/OUT. */
	ULONG stm32_endpoint_index = endpoint->ux_slave_endpoint_descriptor.bEndpointAddress
			& ~UX_ENDPOINT_DIRECTION;

	/* Fetch the address of the physical endpoint. */
	UX_DCD_STM32_ED* ed = &dcd_stm32->ux_dcd_stm32_ed[stm32_endpoint_index];

	/*--------------------------------------------------------------------------------------------*/

	ULONG stm32_endpoint_register;
	ULONG stm32_endpoint_address;

	/* Check the endpoint status, if it is free, reserve it. If not reject this endpoint. */
	if ((ed->ux_dcd_stm32_ed_status & UX_DCD_STM32_ED_STATUS_USED) == 0)
	{
		/* We can use this endpoint. */
		ed->ux_dcd_stm32_ed_status |= UX_DCD_STM32_ED_STATUS_USED;

		/* Keep the physical endpoint address in the endpoint container. */
		endpoint->ux_slave_endpoint_ed = (VOID*)ed;

		/* Save the endpoint pointer. */
		ed->ux_dcd_stm32_ed_endpoint = endpoint;

		/* And its index. */
		ed->ux_dcd_stm32_ed_index = stm32_endpoint_index;

		/* And its direction. */
		ed->ux_dcd_stm32_ed_direction = endpoint->ux_slave_endpoint_descriptor.bEndpointAddress
				& UX_ENDPOINT_DIRECTION;

		/* And its type. */
		ed->ux_dcd_stm32_ed_type = endpoint->ux_slave_endpoint_descriptor.bmAttributes
				& UX_MASK_ENDPOINT_TYPE;

		/* Reset the endpoint. */
		_ux_dcd_stm32_endpoint_reset(dcd_stm32, endpoint);

		/* Reset the endpoint register. */
		stm32_endpoint_register = 0;

		/* For IN endpoint, the FIFO number is stored in the DIEPCTL register. */
		if (ed->ux_dcd_stm32_ed_direction == UX_ENDPOINT_IN)
			/* Set the FIFO number based on the endpoint index. */
			stm32_endpoint_register |= stm32_endpoint_index
					<< UX_DCD_STM32_OTG_FS_DIEPCTL_TXFNUM_SHIFT;

		/* Set USBAEP Active endpoint bit. */
		stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_USBAEP;

		/* Build the endpoint DIEP or DOEP register. */
		switch (ed->ux_dcd_stm32_ed_type)
		{
			case UX_CONTROL_ENDPOINT:
				/* Set the MaxPacketSize. This is different for Control endpoints and other endpoints. */
				switch (endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize)
				{
					/* Is it 64 bytes ? */
					case 64:
						stm32_endpoint_register = 0;
						break;

					/* Is it 32 bytes ? */
					case 32:
						stm32_endpoint_register = 1;
						break;

					/* Is it 16 bytes ? */
					case 16:
						stm32_endpoint_register = 2;
						break;

					/* Is it 8 bytes ? */
					case 8:
						stm32_endpoint_register = 3;
						break;

					default:
						break;
				}

				/* Set the UX_DCD_STM32_OTG_FS_DIEPCTL register. */
				_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPCTL,
						stm32_endpoint_register);

				/* Set the DAINTMSK field for control endpoint IN. */
				_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK,
						1 << stm32_endpoint_index);

				/* Set the UX_DCD_STM32_OTG_FS_DOEPCTL register. */
				_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPCTL,
						stm32_endpoint_register);

				/* Set the DAINTMSK field for control endpoint OUT. */
				_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK,
						0x10000 << stm32_endpoint_index);

				break;

			case UX_BULK_ENDPOINT:
				/* Set the MPS field. */
				stm32_endpoint_register |= endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

				/* Set the SD0PID flag. */
				stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_SD0PID;

				/* Bulk endpoint. Set the USBAEP and SNAK fields. */
				stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_BULK
						| UX_DCD_STM32_OTG_FS_DIEPCTL0_USBAEP | UX_DCD_STM32_OTG_FS_DIEPCTL0_SNAK;

				break;

			case UX_INTERRUPT_ENDPOINT:
				/* Set the MPS field. */
				stm32_endpoint_register |= endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

				/* Set the SD0PID flag. */
				stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_SD0PID;

				/* Interrupt endpoint. Set the USBAEP and SNAK fields. */
				stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_INTERRUPT
						| UX_DCD_STM32_OTG_FS_DIEPCTL0_USBAEP | UX_DCD_STM32_OTG_FS_DIEPCTL0_SNAK;

				break;

			case UX_ISOCHRONOUS_ENDPOINT:
				/* Set the MPS field. */
				stm32_endpoint_register |= endpoint->ux_slave_endpoint_descriptor.wMaxPacketSize;

				/* Iso endpoint. */
				stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPTYP_ISO
						| UX_DCD_STM32_OTG_FS_DIEPCTL0_USBAEP;

				break;

			default:
				return (UX_ERROR);
		}

		/* Continue initialization for non control endpoints. */
		if (ed->ux_dcd_stm32_ed_type != UX_CONTROL_ENDPOINT)
		{
			/* Set the endpoint direction. */
			if ((endpoint->ux_slave_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION)
					== UX_ENDPOINT_IN)
			{
				/* Reset FIFO for endpoint IN. */
				_ux_dcd_stm32_fifo_flush(dcd_stm32, UX_DCD_STM32_FLUSH_TX_FIFO,
						stm32_endpoint_index);

				/* Set the DAINTMSK field for endpoint IN. */
				_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK,
						1 << stm32_endpoint_index);
			}
			else
				/* Set the DAINTMSK field for endpoint OUT. */
				_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK,
						0x10000 << stm32_endpoint_index);

			/* Get the endpoint address. */
			stm32_endpoint_address = _ux_dcd_stm32_endpoint_register_address_get(ed);

			/* Set the endpoint register at the EP address. */
			_ux_dcd_stm32_register_write(dcd_stm32, stm32_endpoint_address,
					stm32_endpoint_register);
		}

		/* Return successful completion. */
		return (UX_SUCCESS);
	}

	/* Return an error. */
	return (UX_NO_ED_AVAILABLE);
}
