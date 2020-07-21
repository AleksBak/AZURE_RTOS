/**************************************************************************/
/**                                                                       */
/** USBX Device Mass Storage Example for STM32F746-DISCO Board            */
/**                                                                       */
/** This example illustrates USBX working on a STM32F7xx processor        */
/**                                                                       */
/** This demo will show the device side of USBX. It will make the device  */
/** appear as a small mass storage device to a host.                      */
/**                                                                       */
/**************************************************************************/

/* Include necessary system files.  */
#include "fx_api.h"
#include "ux_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_dcd_stm32.h"
#include "ux_device_class_storage.h"
#include "ux_device_class_dfu.h"
#include "ux_device_stack.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

/* Define constants.  */
#define DEMO_STACK_SIZE			4096
#define USBX_MEMORY_SIZE		(32 * 1024)
#define RAM_DISK_SIZE			(8 * 1024 * 1024 - 512)
#define RAM_DISK_LAST_LBA		((RAM_DISK_SIZE / 512) -1)

#define HOST_POWERSW_PORT		GPIOH
#define HOST_POWERSW_VBUS		GPIO_Pin_5

/* Define local function prototypes.  */
UINT demo_device_state_change(ULONG event);
VOID demo_thread_dfu_activate(VOID* dfu);
VOID demo_thread_dfu_deactivate(VOID* dfu);
UINT demo_thread_dfu_read(VOID* dfu, ULONG block_number, UCHAR* data_pointer, ULONG length,
		ULONG* media_status);
UINT demo_thread_dfu_write(VOID* dfu, ULONG block_number, UCHAR* data_pointer, ULONG length,
		ULONG* media_status);
UINT demo_thread_dfu_get_status(VOID* dfu, ULONG* media_status);
UINT demo_thread_dfu_notify(VOID* dfu, ULONG notification);

/*------------------------------------------------------------------------------------------------*/

VOID demo_thread_entry(ULONG arg);
UINT demo_thread_media_read(VOID* storage, ULONG lun, UCHAR* data_pointer, ULONG number_blocks,
		ULONG lba, ULONG* media_status);
UINT demo_thread_media_write(VOID* storage, ULONG lun, UCHAR* data_pointer, ULONG number_blocks,
		ULONG lba, ULONG* media_status);
UINT demo_thread_media_status(VOID* storage, ULONG lun, ULONG media_id, ULONG* media_status);

VOID _fx_ram_driver(FX_MEDIA* media_ptr);

void USB_OTG_BSP_HS_Init(void);
uint8_t BSP_SDRAM_Init(void);

/*------------------------------------------------------------------------------------------------*/

/* Define global data structures.   */
TX_THREAD demo_thread;
FX_MEDIA ram_disk;
CHAR* ram_disk_memory;
UX_SLAVE_CLASS_STORAGE_PARAMETER storage_parameter;
UX_SLAVE_CLASS_DFU_PARAMETER dfu_parameter;

/* Buffer for FileX RAM media initialization.  */
unsigned char buffer[512];

/*------------------------------------------------------------------------------------------------*/

#define USBD_VID			0x0781
#define USBD_PID			0x0000
#define USBD_DEV			0x0001
#define LOBYTE(x)			((UCHAR)(x & 0x00FFU))
#define HIBYTE(x)			((UCHAR)((x & 0xFF00U) >> 8U))

#define INTERF_COM_NUM		0x00
#define INTERF_DAT_NUM		0x01

#define DEVICE_FRAMEWORK_LENGTH_FULL_SPEED		50

#if 1
// @formatter:off
UCHAR device_framework_full_speed[] =
{
	/* Device Descriptor (must be first in this array) */
	0x12,										/* 0 bLength */
	UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
	0x10,										/* 2 bcdUSB */
	0x01,										/* 3 bcdUSB */
	0x00,										/* 4 bDeviceClass */
	0x00,										/* 5 bDeviceSubClass */
	0x00,										/* 6 bDeviceProtocol */
	0x08,										/* 7 bMaxPacketSize0 */
	LOBYTE(USBD_VID),							/* 8 idVendor */
	HIBYTE(USBD_VID),							/* 9 idVendor */
	LOBYTE(USBD_PID),							/* 10 idProduct */
	HIBYTE(USBD_PID),							/* 11 idProduct */
	LOBYTE(USBD_DEV),							/* 12 bcdDevice */
	HIBYTE(USBD_DEV),							/* 13 bcdDevice */
	0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
	0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
	0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
	0x01,										/* 17 bNumConfigurations (1 Configuration) */

//	/* Device Descriptor */
//	0x12, 0x01, 0x10, 0x01, 0x00, 0x00, 0x00, 0x08,
//	0x81, 0x07, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02,
//	0x03, 0x01,

	/* Configuration descriptor */
	0x09, 0x02, 0x20, 0x00, 0x01, 0x01, 0x00, 0xc0,
	0x32,

	/* Interface descriptor */
	0x09, 0x04, 0x00, 0x00, 0x02, 0x08, 0x06, 0x50,
	0x00,

	/* Endpoint descriptor (Bulk In) */
	0x07, 0x05, 0x81, 0x02, 0x40, 0x00, 0x00,

	/* Endpoint descriptor (Bulk Out) */
	0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00
};
// @formatter:on
#endif

#define DEVICE_FRAMEWORK_LENGTH_HIGH_SPEED		60

#if 1
// @formatter:off
UCHAR device_framework_high_speed[] =
{
	/* Device Descriptor (must be first in this array) */
	0x12,										/* 0 bLength */
	UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
	0x00,										/* 2 bcdUSB */
	0x02,										/* 3 bcdUSB */
	0x00,										/* 4 bDeviceClass */
	0x00,										/* 5 bDeviceSubClass */
	0x00,										/* 6 bDeviceProtocol */
	0x40,										/* 7 bMaxPacketSize0 */
	LOBYTE(USBD_VID),							/* 8 idVendor */
	HIBYTE(USBD_VID),							/* 9 idVendor */
	LOBYTE(USBD_PID),							/* 10 idProduct */
	HIBYTE(USBD_PID),							/* 11 idProduct */
	LOBYTE(USBD_DEV),							/* 12 bcdDevice */
	HIBYTE(USBD_DEV),							/* 13 bcdDevice */
	0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
	0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
	0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
	0x01,										/* 17 bNumConfigurations (1 Configuration) */

	/* Device Qualifier Descriptor */
	0x0A,										/* 0 bLength */
	UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM,		/* 1 bDescriptorType */
	0x00,										/* 2 bcdUSB BCD(2.0) */
	0x02,										/* 3 bcdUSB */
	0x00,										/* 4 bDeviceClass */
	0x00,										/* 5 bDeviceSubClass */
	0x00,										/* 6 bDeviceProtocol */
	0x40,										/* 7 bMaxPacketSize0 */
	0x01,										/* 8 bNumConfigs : 1 */
	0x00,										/* 9 Reserve, fixed to 0 */

	/* Configuration Descriptor */
	0x09,										/* 0 bLength */
	UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType */
	0x20,										/* 2 wTotalLength : This will be calculated at run-time. */
	0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	0x01,										/* 4 bNumInterfaces (1 Interface) */
	0x01,										/* 5 bConfigurationValue : Fixed to 1 since only one configuration is supported. */
	0x00,										/* 6 iConfiguration (No String Descriptor) */
	0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
	32,											/* 8 bMaxPower (0x32 = 100 mA) */

	/* Interface Descriptor */
	0x09,										/* 0 bLength */
	UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	INTERF_COM_NUM,								/* 2 bInterfaceNumber */
	0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
	0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface */
	0x08,										/* 5 bInterfaceClass    : */
	0x06,										/* 6 bInterfaceSubClass : */
	0x50,										/* 7 bInterfaceProtocol : */
	0x00,										/* 8 iInterface Index */

	/* Endpoint Descriptor (Bulk-In) for Interface#1 */
	0x07,										/* 0 bLength */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	(UX_ENDPOINT_IN | 1),						/* 2 bEndpointAddress */
	UX_BULK_ENDPOINT,							/* 3 bmAttributes */
	0x00,										/* 4 wMaxPacketSize */
	0x01,										/* 5 wMaxPacketSize */
	0x00,										/* 6 bInterval */

	/* Endpoint Descriptor (Bulk-Out) for Interface#1 */
	0x07,										/* 0 bLength */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	(UX_ENDPOINT_OUT | 2),						/* 2 bEndpointAddress */
	UX_BULK_ENDPOINT,							/* 3 bmAttributes */
	0x00,										/* 4 wMaxPacketSize */
	0x01,										/* 5 wMaxPacketSize */
	0x00,										/* 6 bInterval */
};
// @formatter:on
#endif

/* String Device Framework :
 * Byte 0 and 1 : Word containing the language ID : 0x0904 for US
 * Byte 2       : Byte containing the index of the descriptor
 * Byte 3       : Byte containing the length of the descriptor string
 */

#define STRING_FRAMEWORK_LENGTH					38

#if 1
UCHAR string_framework[] =
{
	/* Manufacturer string descriptor : Index 1 */
	0x09, 0x04, 0x01, 0x0c,
	0x45, 0x78, 0x70, 0x72, 0x65, 0x73, 0x20, 0x4c,
	0x6f, 0x67, 0x69, 0x63,

	/* Product string descriptor : Index 2 */
	0x09, 0x04, 0x02, 0x0a,
	0x46, 0x6c, 0x61, 0x73, 0x68, 0x20, 0x44, 0x69, 0x73, 0x6b,

	/* Serial Number string descriptor : Index 3 */
	0x09, 0x04, 0x03, 0x04,
	0x30, 0x30, 0x30, 0x31
};
#endif

/* Multiple languages are supported on the device, to add a language besides english,
 * the Unicode language code must be appended to the language_id_framework array and
 * the length adjusted accordingly. */
#define LANGUAGE_ID_FRAMEWORK_LENGTH			2

UCHAR language_id_framework[] =
{
	/* English. */
	0x09, 0x04
};

/*------------------------------------------------------------------------------------------------*/

VOID hardware_setup(void);

int main(int argc, char** argv)
{
	/* Setup the hardware. */
	hardware_setup();

	/* Enter the ThreadX kernel.  */
	tx_kernel_enter();
}

void tx_application_define(void* first_unused_memory)
{
	CHAR* stack_pointer;
	CHAR* memory_pointer;
	UINT status;

	/* Initialize the free memory pointer.  */
	stack_pointer = (CHAR*)first_unused_memory;

	/* Initialize the RAM disk memory. */
	memory_pointer = stack_pointer + DEMO_STACK_SIZE;

	/* Initialize USBX Memory */
	status = _ux_system_initialize(memory_pointer, USBX_MEMORY_SIZE, UX_NULL, 0);

	/* Initialize memory address for USBX.  */
	ram_disk_memory = (CHAR*)0xC0000000;

	/* Reset it.  */
	_ux_utility_memory_set(ram_disk_memory, 0, RAM_DISK_SIZE);

	/* Initialize FileX.  */
	_fx_system_initialize();

	/* The code below is required for installing the device portion of USBX.
	 * In this demo, DFU is possible and we have a call back for state change.
	 *
	 * device_framework_high_speed           Pointer to high speed FW
	 * device_framework_length_high_speed    Length of high speed FW
	 * device_framework_full_speed           Pointer to full speed FW
	 * device_framework_length_full_speed    Length of full speed FW
	 * string_framework                      Pointer to string FW
	 * string_framework_length               Length of string FW
	 * language_id_framework                 Pointer to language ID FW
	 * language_id_framework_length          Length of language ID FW
	 * (ux_system_slave_change_function)     Pointer to callback function for device changes
	 */
	status = _ux_device_stack_initialize(device_framework_high_speed,
			DEVICE_FRAMEWORK_LENGTH_HIGH_SPEED, device_framework_full_speed,
			DEVICE_FRAMEWORK_LENGTH_FULL_SPEED, string_framework, STRING_FRAMEWORK_LENGTH,
			language_id_framework, LANGUAGE_ID_FRAMEWORK_LENGTH, UX_NULL);
	if (status != UX_SUCCESS)
		return;

	/* Store the number of LUN in this device storage instance.  */
	storage_parameter.ux_slave_class_storage_parameter_number_lun = 1;

	/* Initialize the storage class parameters for reading/writing to the Flash Disk.  */
	storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_last_lba =
			RAM_DISK_LAST_LBA;

	storage_parameter.ux_slave_class_storage_parameter_lun[0]
			.ux_slave_class_storage_media_block_length = 512;

	storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_type = 0;

	storage_parameter.ux_slave_class_storage_parameter_lun[0]
			.ux_slave_class_storage_media_removable_flag = 0x80;

	storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read =
			demo_thread_media_read;
	storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_write =
			demo_thread_media_write;
	storage_parameter.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_status =
			demo_thread_media_status;

	/* Initialize the device storage class.
	 * The class is connected with interface 0 on configuration 1.
	 * class_name                            Name of class
	 * class_function_entry                  Class entry function
	 * configuration_number                  Configuration # for this class
	 * interface_number                      Interface # for this class
	 * parameter                             Parameter specific for class */
	status = _ux_device_stack_class_register(_ux_system_slave_class_storage_name,
			_ux_device_class_storage_entry, 1, 0, (VOID*)&storage_parameter);
	if (status != UX_SUCCESS)
		return;

	/* Create the main demo thread. */
	status = _tx_thread_create(&demo_thread, "tx demo", demo_thread_entry, 0, stack_pointer,
			DEMO_STACK_SIZE, 20, 20, 1, TX_AUTO_START);

	return;
}

void demo_thread_entry(ULONG arg)
{
	ULONG status;

	/* Format the ram drive. */
	status = fx_media_format(&ram_disk, _fx_ram_driver, ram_disk_memory, buffer, 512, "RAM DISK",
			2, 512, 0, RAM_DISK_SIZE / 512, 512, 4, 1, 1);

	/* Check the media format status.  */
	if (status != FX_SUCCESS)
	{
		/* Error opening media.  Return to caller.  */
		return;
	}

	/* Open the ram_disk.  */
	status = fx_media_open(&ram_disk, "RAM DISK", _fx_ram_driver, ram_disk_memory, buffer, 512);

	/* Check the media open status.  */
	if (status != FX_SUCCESS)
	{
		/* Error opening media.  Return to caller.  */
		return;
	}

	/* Initialize the bsp layer of the USB OTG HS Controller.  */
	USB_OTG_BSP_HS_Init();

	_tx_thread_sleep(10);

	/* Register the STM32  USB device controllers available in this system */
	status = _ux_dcd_stm32_initialize(UX_DCD_STM32_OTG_FS_HIGH_SPEED, 0);
}

UINT demo_thread_media_status(VOID* storage, ULONG lun, ULONG media_id, ULONG* media_status)
{
	/* The ATA drive never fails. This is just for demo only !!!! */
	return (UX_SUCCESS);
}

UINT demo_thread_media_read(VOID* storage, ULONG lun, UCHAR* data_pointer, ULONG number_blocks,
		ULONG lba, ULONG* media_status)
{
	UINT status = 0;

	while (number_blocks--)
	{
		status = fx_media_read(&ram_disk, lba, data_pointer);
		data_pointer += 512;
		lba++;
	}

	return (status);
}

UINT demo_thread_media_write(VOID* storage, ULONG lun, UCHAR* data_pointer, ULONG number_blocks,
		ULONG lba, ULONG* media_status)
{
	UINT status = 0;

	while (number_blocks--)
	{
		status = fx_media_write(&ram_disk, lba, data_pointer);
		data_pointer += 512;
		lba++;
	}

	return (status);
}

void USB_OTG_BSP_HS_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Configure USB FS GPIOs */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	/* CLK */
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* D0 */
	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* D1 D2 D3 D4 D5 D6 D7 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* STP */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* NXT */
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

	/* DIR */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_HS;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/* Enable USB HS Clocks */
	__HAL_RCC_USB_OTG_HS_CLK_ENABLE();
	__HAL_RCC_USB_OTG_HS_ULPI_CLK_ENABLE();

	/* Set USBHS Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(OTG_HS_IRQn, 4, 0);

	/* Enable USBHS Interrupt */
	HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
}
