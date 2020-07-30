/**************************************************************************/
/**                                                                       */
/** Generic USBX Device CDC-ACM Example.                                  */
/**                                                                       */
/** This example illustrates USBX working on a generic processor - there  */
/** is no processor-specific code in this example.                        */
/**                                                                       */
/** This demo shows example usage of USBX's device CDC-ACM class. The     */
/** demo simply replies to any messages received from the host. If it is  */
/** a valid AT command, the demo sends a reply back to the host with the  */
/** the requested information. If it is not an AT command, the message    */
/** is echoed back to the host.                                           */
/**                                                                       */
/**************************************************************************/

/* Include necessary system files.  */
#include "fx_api.h"
#include "ux_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_dcd_stm32.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_stack.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

/* Include controller-specific header file.  */
//#include "ux_dcd_stm32.h"
/* Define constants.  */
#define UX_DEMO_STACK_SIZE          2048
#define UX_DEMO_BUFFER_SIZE         64
#define USBX_MEMORY_SIZE            (32 * 1024)

/* Define local/extern function prototypes.  */
void demo_thread_entry(ULONG);
void tx_demo_thread_slave_simulation_entry(ULONG);
VOID demo_cdc_instance_activate(VOID* cdc_instance);
VOID demo_cdc_instance_deactivate(VOID* cdc_instance);
UINT tx_demo_thread_slave_simulation_response(UCHAR* string, ULONG length);
UINT tx_demo_thread_slave_write_callback(UX_SLAVE_CLASS_CDC_ACM* cdc_acm_slave, UINT status,
		ULONG length);
UINT tx_demo_thread_slave_read_callback(UX_SLAVE_CLASS_CDC_ACM* cdc_acm_slave, UINT status,
		UCHAR* data_pointer, ULONG length);

void USB_OTG_BSP_HS_Init(void);

/* Define global data structures.  */
TX_THREAD demo_thread;
ULONG callback_actual_length;
ULONG callback_transmission_status;
TX_SEMAPHORE slave_reception_semaphore;
TX_SEMAPHORE slave_transmission_semaphore;
UX_SLAVE_CLASS_CDC_ACM* cdc_acm_slave;
UX_SLAVE_CLASS_CDC_ACM_PARAMETER parameter;
UCHAR buffer[UX_DEMO_BUFFER_SIZE];
ULONG echo_mode;
ULONG error_counter;

/* Define device framework.  */
unsigned char device_framework_full_speed[] = {
	/* Device Descriptor */
	0x12, /* bLength */
	0x01, /* bDescriptorType */
	0x00, 0x02, /* bcdUSB */
	0xef, /* bDeviceClass - Depends on bDeviceSubClass */
	0x02, /* bDeviceSubClass - Depends on bDeviceProtocol */
	0x01, /* bDeviceProtocol - There's an IAD */
	0x40, /* bMaxPacketSize0 */
	0x84, 0x84, /* idVendor */
	0x00, 0x00, /* idProduct */
	0x00, 0x01, /* bcdDevice */
	0x01, /* iManufacturer */
	0x02, /* iProduct */
	0x03, /* iSerialNumber */
	0x01, /* bNumConfigurations */

	/* Device Qualifier Descriptor */
	0x0a, /* bLength */
	0x06, /* bDescriptorType */
	0x00, 0x02, /* bcdUSB */
	0x02, /* bDeviceClass */
	0x00, /* bDeviceSubClass */
	0x00, /* bDeviceProtocol */
	0x40, /* bMaxPacketSize0 */
	0x01, /* bNumConfigurations */
	0x00, /* Reserved */

	/* Configuration Descriptor */
	0x09, /* bLength */
	0x02, /* bDescriptorType */
	0x4b, 0x00, /* wTotalLength */
	0x02, /* bNumInterfaces */
	0x01, /* bConfigurationValue */
	0x00, /* iConfiguration */
	0x40, /* bmAttributes - Self-powered */
	0x00, /* bMaxPower */

	/* Interface Association Descriptor */
	0x08, /* bLength */
	0x0b, /* bDescriptorType */
	0x00, /* bFirstInterface */
	0x02, /* bInterfaceCount */
	0x02, /* bFunctionClass - CDC - Communication */
	0x02, /* bFunctionSubClass - ACM */
	0x00, /* bFunctionProtocol - No class specific protocol required */
	0x00, /* iFunction */

	/* Interface Descriptor */
	0x09, /* bLength */
	0x04, /* bDescriptorType */
	0x00, /* bInterfaceNumber */
	0x00, /* bAlternateSetting */
	0x01, /* bNumEndpoints */
	0x02, /* bInterfaceClass - CDC - Communication */
	0x02, /* bInterfaceSubClass - ACM */
	0x01, /* bInterfaceProtocol - Common AT commands */
	0x00, /* iInterface */

	/* CDC Header Functional Descriptor */
	0x05, /* bLength */
	0x24, /* bDescriptorType */
	0x00, /* bDescriptorSubType */
	0x10, 0x01, /* bcdCDC */

	/* CDC ACM Functional Descriptor */
	0x04, /* bLength */
	0x24, /* bDescriptorType */
	0x02, /* bDescriptorSubType */
	0x0f, /* bmCapabilities */

	/* CDC Union Functional Descriptor */
	0x05, /* bLength */
	0x24, /* bDescriptorType */
	0x06, /* bDescriptorSubType */
	0x00, /* bmMasterInterface */
	0x01, /* bmSlaveInterface0 */

	/* CDC Call Management Functional Descriptor */
	0x05, /* bLength */
	0x24, /* bDescriptorType */
	0x01, /* bDescriptorSubType */
	0x00, /* bmCapabilities */
	0x01, /* bDataInterface */

	/* Endpoint Descriptor */
	0x07, /* bLength */
	0x05, /* bDescriptorType */
	0x83, /* bEndpointAddress */
	0x03, /* bmAttributes - Interrupt */
	0x08, 0x00, /* wMaxPacketSize */
	0xff, /* bInterval */

	/* Interface Descriptor */
	0x09, /* bLength */
	0x04, /* bDescriptorType */
	0x01, /* bInterfaceNumber */
	0x00, /* bAlternateSetting */
	0x02, /* bNumEndpoints */
	0x0a, /* bInterfaceClass - CDC - Data */
	0x00, /* bInterfaceSubClass - Should be 0x00 */
	0x00, /* bInterfaceProtocol - No class specific protocol required */
	0x00, /* iInterface */

	/* Endpoint Descriptor */
	0x07, /* bLength */
	0x05, /* bDescriptorType */
	0x02, /* bEndpointAddress */
	0x02, /* bmAttributes - Bulk */
	0x40, 0x00, /* wMaxPacketSize */
	0x00, /* bInterval */

	/* Endpoint Descriptor */
	0x07, /* bLength */
	0x05, /* bDescriptorType */
	0x81, /* bEndpointAddress */
	0x02, /* bmAttributes - Bulk */
	0x40, 0x00, /* wMaxPacketSize */
	0x00, /* bInterval */
};

unsigned char device_framework_high_speed[] = {
	/* Device Descriptor */
	0x12, /* bLength */
	0x01, /* bDescriptorType */
	0x00, 0x02, /* bcdUSB */
	0xef, /* bDeviceClass - Depends on bDeviceSubClass */
	0x02, /* bDeviceSubClass - Depends on bDeviceProtocol */
	0x01, /* bDeviceProtocol - There's an IAD */
	0x40, /* bMaxPacketSize0 */
	0x84, 0x84, /* idVendor */
	0x00, 0x00, /* idProduct */
	0x00, 0x01, /* bcdDevice */
	0x01, /* iManufacturer */
	0x02, /* iProduct */
	0x03, /* iSerialNumber */
	0x01, /* bNumConfigurations */

	/* Device Qualifier Descriptor */
	0x0a, /* bLength */
	0x06, /* bDescriptorType */
	0x00, 0x02, /* bcdUSB */
	0x02, /* bDeviceClass */
	0x00, /* bDeviceSubClass */
	0x00, /* bDeviceProtocol */
	0x40, /* bMaxPacketSize0 */
	0x01, /* bNumConfigurations */
	0x00, /* Reserved */

	/* Configuration Descriptor */
	0x09, /* bLength */
	0x02, /* bDescriptorType */
	0x4b, 0x00, /* wTotalLength */
	0x02, /* bNumInterfaces */
	0x01, /* bConfigurationValue */
	0x00, /* iConfiguration */
	0x40, /* bmAttributes - Self-powered */
	0x00, /* bMaxPower */

	/* Interface Association Descriptor */
	0x08, /* bLength */
	0x0b, /* bDescriptorType */
	0x00, /* bFirstInterface */
	0x02, /* bInterfaceCount */
	0x02, /* bFunctionClass - CDC - Communication */
	0x02, /* bFunctionSubClass - ACM */
	0x00, /* bFunctionProtocol - No class specific protocol required */
	0x00, /* iFunction */

	/* Interface Descriptor */
	0x09, /* bLength */
	0x04, /* bDescriptorType */
	0x00, /* bInterfaceNumber */
	0x00, /* bAlternateSetting */
	0x01, /* bNumEndpoints */
	0x02, /* bInterfaceClass - CDC - Communication */
	0x02, /* bInterfaceSubClass - ACM */
	0x01, /* bInterfaceProtocol - Common AT commands */
	0x00, /* iInterface */

	/* CDC Header Functional Descriptor */
	0x05, /* bLength */
	0x24, /* bDescriptorType */
	0x00, /* bDescriptorSubType */
	0x10, 0x01, /* bcdCDC */

	/* CDC ACM Functional Descriptor */
	0x04, /* bLength */
	0x24, /* bDescriptorType */
	0x02, /* bDescriptorSubType */
	0x0f, /* bmCapabilities */

	/* CDC Union Functional Descriptor */
	0x05, /* bLength */
	0x24, /* bDescriptorType */
	0x06, /* bDescriptorSubType */
	0x00, /* bmMasterInterface */
	0x01, /* bmSlaveInterface0 */

	/* CDC Call Management Functional Descriptor */
	0x05, /* bLength */
	0x24, /* bDescriptorType */
	0x01, /* bDescriptorSubType */
	0x00, /* bmCapabilities */
	0x01, /* bDataInterface */

	/* Endpoint Descriptor */
	0x07, /* bLength */
	0x05, /* bDescriptorType */
	0x83, /* bEndpointAddress */
	0x03, /* bmAttributes - Interrupt */
	0x08, 0x00, /* wMaxPacketSize */
	0xff, /* bInterval */

	/* Interface Descriptor */
	0x09, /* bLength */
	0x04, /* bDescriptorType */
	0x01, /* bInterfaceNumber */
	0x00, /* bAlternateSetting */
	0x02, /* bNumEndpoints */
	0x0a, /* bInterfaceClass - CDC - Data */
	0x00, /* bInterfaceSubClass - Should be 0x00 */
	0x00, /* bInterfaceProtocol - No class specific protocol required */
	0x00, /* iInterface */

	/* Endpoint Descriptor */
	0x07, /* bLength */
	0x05, /* bDescriptorType */
	0x02, /* bEndpointAddress */
	0x02, /* bmAttributes - Bulk */
	0x40, 0x00, /* wMaxPacketSize */
	0x00, /* bInterval */

	/* Endpoint Descriptor */
	0x07, /* bLength */
	0x05, /* bDescriptorType */
	0x81, /* bEndpointAddress */
	0x02, /* bmAttributes - Bulk */
	0x40, 0x00, /* wMaxPacketSize */
	0x00, /* bInterval */
};

unsigned char string_framework[] = {
	/* Manufacturer string descriptor : Index 1 - "Express Logic" */
	0x09, 0x04, 0x01, 0x0c,
	0x45, 0x78, 0x70, 0x72, 0x65, 0x73, 0x20, 0x4c,
	0x6f, 0x67, 0x69, 0x63,

	/* Product string descriptor : Index 2 - "EL Composite device" */
	0x09, 0x04, 0x02, 0x13,
	0x45, 0x4c, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x6f,
	0x73, 0x69, 0x74, 0x65, 0x20, 0x64, 0x65, 0x76,
	0x69, 0x63, 0x65,

	/* Serial Number string descriptor : Index 3 - "0001" */
	0x09, 0x04, 0x03, 0x04,
	0x30, 0x30, 0x30, 0x31
};

/* Multiple languages are supported on the device, to add
 a language besides english, the unicode language code must
 be appended to the language_id_framework array and the length
 adjusted accordingly. */
unsigned char language_id_framework[] = {

/* English. */
0x09, 0x04
};

void error_handler()
{
	while (1);
}

VOID error_callback(UINT system_level, UINT system_context, UINT error_code)
{
	error_handler();
}

void hardware_setup();

int main(void)
{
	/* Setup the hardware. */
	hardware_setup();

	/* Enter the ThreadX kernel.  */
	tx_kernel_enter();
}

VOID demo_cdc_instance_activate(VOID* cdc_instance)
{
	/* Save the CDC instance.  */
	cdc_acm_slave = (UX_SLAVE_CLASS_CDC_ACM*)cdc_instance;
}

VOID demo_cdc_instance_deactivate(VOID* cdc_instance)
{
	/* Reset the CDC instance.  */
	cdc_acm_slave = UX_NULL;
}

void tx_application_define(void* first_unused_memory)
{
	CHAR* stack_pointer;
	CHAR* memory_pointer;
	UINT status;

	stack_pointer = (CHAR*)first_unused_memory;
	memory_pointer = stack_pointer + UX_DEMO_STACK_SIZE;

	/* Create the main demo thread.  */
	status = tx_thread_create(&demo_thread, "tx demo", demo_thread_entry, (ULONG )memory_pointer,
			stack_pointer, UX_DEMO_STACK_SIZE,
			20, 20, 1, TX_AUTO_START);
	if (status)
		error_handler();
}

void demo_thread_entry(ULONG memory_pointer_thread_input)
{
	UINT status;
	ULONG message_length;

	/* Initialize USBX. Memory */
	ux_system_initialize((ULONG*)memory_pointer_thread_input, USBX_MEMORY_SIZE, UX_NULL, 0);

	/* Register error callback. */
	_ux_utility_error_callback_register(error_callback);

	/* The code below is required for installing the device portion of USBX. No call back for
	 device status change in this example. */
	status = ux_device_stack_initialize(device_framework_high_speed,
			sizeof(device_framework_high_speed),
			device_framework_full_speed, sizeof(device_framework_full_speed),
			string_framework, sizeof(string_framework),
			language_id_framework, sizeof(language_id_framework),
			UX_NULL);
	if (status != UX_SUCCESS)
		error_handler();

	/* Set the parameters for callback when insertion/extraction of a CDC device.  */
	parameter.ux_slave_class_cdc_acm_instance_activate = demo_cdc_instance_activate;
	parameter.ux_slave_class_cdc_acm_instance_deactivate = demo_cdc_instance_deactivate;

	/* Initialize the device cdc class. This class owns both interfaces starting with 0. */
	status = ux_device_stack_class_register(_ux_system_slave_class_cdc_acm_name,
			ux_device_class_cdc_acm_entry,
			1, 0, &parameter);
	if (status != UX_SUCCESS)
		error_handler();

	/* Initialize the bsp layer of the USB OTG HS Controller.  */
	USB_OTG_BSP_HS_Init();
	status = tx_thread_sleep(10);
	if (status)
		error_handler();

	/* Register the STM32  USB device controllers available in this system */
	status = _ux_dcd_stm32_initialize(0x40040000, 0);
	if (status)
		error_handler();

	while (1)
	{
		/* Ensure the CDC class is mounted.  */
		while (cdc_acm_slave != UX_NULL)
		{
			/* Read from the host.  */
			status = ux_device_class_cdc_acm_read(cdc_acm_slave, buffer, UX_DEMO_BUFFER_SIZE,
					&message_length);

			/* Device disconnect? */
			if (status != UX_SUCCESS)
				break;

			/* Echo it back to the host.  */
			status = ux_device_class_cdc_acm_write(cdc_acm_slave, buffer, message_length,
					&message_length);

			/* Device disconnect? */
			if (status != UX_SUCCESS)
				break;
		}
	}
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

