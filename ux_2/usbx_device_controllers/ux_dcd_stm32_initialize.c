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
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    _ux_dcd_stm32_initialize                              PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function initializes the USB slave controller of the STM32     */
/*    microcontroller from ST.                                            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd                                   Address of DCD                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    _ux_dcd_stm32_register_write          Read register                 */
/*    _ux_utility_memory_allocate           Allocate memory               */
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
UINT _ux_dcd_stm32_initialize(ULONG dcd_io, ULONG parameter)
{
	/* Get the pointer to the DCD. */
	UX_SLAVE_DCD* dcd = &_ux_system_slave->ux_system_slave_dcd;

	/* The controller initialized here is of STM32 type. */
	dcd->ux_slave_dcd_controller_type = UX_DCD_STM32_SLAVE_CONTROLLER;

	/* Allocate memory for this STM32 DCD instance. */
	UX_DCD_STM32* dcd_stm32 = _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY,
			sizeof(UX_DCD_STM32));

	/* Check if memory was properly allocated. */
	if (dcd_stm32 == UX_NULL)
		return (UX_MEMORY_INSUFFICIENT);

	/* Set the pointer to the STM32 DCD. */
	dcd->ux_slave_dcd_controller_hardware = (VOID*)dcd_stm32;

	/* Save the base address of the controller. */
	dcd->ux_slave_dcd_io = dcd_io;
	dcd_stm32->ux_dcd_stm32_base = dcd_io;

	/* Set the generic DCD owner for the STM32 DCD. */
	dcd_stm32->ux_dcd_stm32_dcd_owner = dcd;

	/* Initialize the function collector for this DCD. */
	dcd->ux_slave_dcd_function = _ux_dcd_stm32_function;

	/* Reset the GINT Global Interrupt Mask register. */
	_ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_GAHBCFG,
			UX_DCD_STM32_OTG_FS_GAHBCFG_GINT);

	/* Check the controller. Full Speed or HighSpeed initialization. */
	if (dcd_stm32->ux_dcd_stm32_base == UX_DCD_STM32_OTG_FS_FULL_SPEED)
	{
		/* PHY Selection in FS mode. */
		_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GUSBCFG,
				UX_DCD_STM32_OTG_FS_GUSBCFG_PHYSEL);

#ifdef STM32F767ZI_NUCLEO_USBX
		/* Initialize the PHY Power options. In device mode, set B-VBUS */
		_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GCCFG ,
				UX_DCD_STM32_OTG_FS_GCCFG_PWRDWN |
				UX_DCD_STM32_OTG_FS_GCCFG_VBDEN);
#else
		/* Initialize the PHY Power options. In device mode, set B-VBUS */
		_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GCCFG,
				UX_DCD_STM32_OTG_FS_GCCFG_PWRDWN |
				UX_DCD_STM32_OTG_FS_GCCFG_VBUSSENSINGB);
#endif
	}
	else
	{
		/* PHY Selection in HS mode. */
		_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GUSBCFG,
				UX_DCD_STM32_OTG_FS_GUSBCFG_ULPI_UTMI_SEL);
	}

	/* Spec says wait for 50 cycles. */
	_ux_dcd_stm32_delay(50);

	/*--------------------------------------------------------------------------------------------*/

	ULONG stm32_register;

	/* Wait for AHB master Idle State. */
	do
	{
		/* Spec says wait for 5 cycles. */
		_ux_dcd_stm32_delay(5);

		/* Read the RST Control register. */
		stm32_register = _ux_dcd_stm32_register_read(dcd_stm32, UX_DCD_STM32_OTG_FS_GRSTCTL);
	} while ((stm32_register & UX_DCD_STM32_OTG_FS_GRSTCTL_AHBIDL) == 0);

	/* Perform the core soft reset. */
	_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GRSTCTL,
			UX_DCD_STM32_OTG_FS_GRSTCTL_CSRST);

	/* Wait for Soft Reset to be completed. */
	do
	{
		/* Read the RST Control register. */
		stm32_register = _ux_dcd_stm32_register_read(dcd_stm32, UX_DCD_STM32_OTG_FS_GRSTCTL);
	} while (stm32_register & UX_DCD_STM32_OTG_FS_GRSTCTL_CSRST);

	/* Spec says wait for 10 cycles. */
	_ux_dcd_stm32_delay(10);

	/* Set the controller to device mode. */
	_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GUSBCFG,
			UX_DCD_STM32_OTG_FS_GUSBCFG_FDMOD);

	/* Spec says wait for 50 cycles. */
	_ux_dcd_stm32_delay(50);

	/*--------------------------------------------------------------------------------------------*/

	/* Check the controller. Full Speed or HighSpeed initialization. */
	if (dcd_stm32->ux_dcd_stm32_base == UX_DCD_STM32_OTG_FS_FULL_SPEED)
		/* Set the PHY speed to full speed. */
		_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DCFG,
				UX_DCD_STM32_OTG_FS_DCFG_DSPD_FULL_SPEED);

	/* Set the turnaround time. */
	_ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_GUSBCFG,
			UX_DCD_STM32_OTG_FS_GUSBCFG_TRDT_MASK);
	_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GUSBCFG,
			UX_DCD_STM32_OTG_FS_GUSBCFG_TRDT_8);

	/* Restart the PHY clock. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_PCGCCTL, 0);

	/* Set the Device default address to 0 and the Periodic Frame interval to 80%. */
	_ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_DCFG,
			(UX_DCD_STM32_OTG_FS_DCFG_PFVIL_MASK | UX_DCD_STM32_OTG_FS_DCFG_DAD_MASK));

	/* Set the RX FIFO. Size. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GRXFSIZ, UX_DCD_STM32_RX_FIFO_SIZE);

	/* Set the fifo address. */
	ULONG fifo_address = UX_DCD_STM32_RX_FIFO_SIZE;

	/* Set the NP TX FIFO. Size. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GNPTXFSIZ, (fifo_address |
			(UX_DCD_STM32_NP_TX_FIFO_SIZE << UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

	/* Adjust the fifo address. */
	fifo_address += UX_DCD_STM32_NP_TX_FIFO_SIZE;

	/* We need to setup the IN FIFOs. Check the controller. Full-Speed or High-Speed initialization. */
	if (dcd_stm32->ux_dcd_stm32_base == UX_DCD_STM32_OTG_FS_HIGH_SPEED)
	{
		/* For OTG_HS, the maximum amount of RAM we have for FIFOs is 4kb. */

		/* Set the values for the IN Fifos (5 generic IN Fifos). */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS <<
						UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

		/* Adjust the fifo address. */
		fifo_address += UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS;
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF + 4,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

		/* Adjust the fifo address. */
		fifo_address += UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS;
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF + 8,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

		/* Adjust the fifo address. */
		fifo_address += UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS;
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF + 12,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

		/* Adjust the fifo address. */
		fifo_address += UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS;
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF + 16,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_HS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));
	}
	else
	{
		/* For OTG_FS, the maximum amount of RAM we have for FIFOs is 1.25kb. */

		/* Set the values for the IN Fifos (3 generic IN Fifos). */
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_FS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

		/* Adjust the fifo address. */
		fifo_address += UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_FS;
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF + 4,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_FS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));

		/* Adjust the fifo address. */
		fifo_address += UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_FS;
		_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPTXF + 8,
				(fifo_address | (UX_DCD_STM32_ENDPOINT_TX_FIFO_SIZE_FS
								<< UX_DCD_STM32_OTG_FS_GNPTXFSIZ_NPTXFSD_SHIFT)));
	}

	/*--------------------------------------------------------------------------------------------*/

	/* Clear DIEPMSK and DOEPMSK. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DIEPMSK, 0);
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DOEPMSK, 0);

	/* Clear all pending interrupts on endpoint. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINT, 0xFFFFFFFF);
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK, 0);

	/* Disable all interrupts. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTMSK, 0);

	/* Clear all pending interrupts. */
	_ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTSTS, 0xFFFFFFFF);

	/* Enable interrupts for the device mode only. */
	_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GINTMSK,
			UX_DCD_STM32_OTG_FS_GINTMSK_WKUINTM |
			UX_DCD_STM32_OTG_FS_GINTMSK_RFXLVLM |
			UX_DCD_STM32_OTG_FS_GINTMSK_DISCINTM |
			UX_DCD_STM32_OTG_FS_GINTMSK_USBSUSPM |
			UX_DCD_STM32_OTG_FS_GINTMSK_USBRSTM |
			UX_DCD_STM32_OTG_FS_GINTMSK_ENUMDNEM |
			UX_DCD_STM32_OTG_FS_GINTMSK_IEPINTM |
			UX_DCD_STM32_OTG_FS_GINTMSK_OEPINTM);

	/* Set the state of the controller to OPERATIONAL now. */
	dcd->ux_slave_dcd_status = UX_DCD_STATUS_OPERATIONAL;

	/* Set the GINT Global Interrupt Mask register. */
	_ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_GAHBCFG,
			UX_DCD_STM32_OTG_FS_GAHBCFG_GINT);

	/* Clear soft disconnect bit. */
	_ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_DCTL,
			UX_DCD_STM32_OTG_FS_DCTL_SDIS);

	/* Return successful completion. */
	return (UX_SUCCESS);
}
