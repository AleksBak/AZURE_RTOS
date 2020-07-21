/**************************************************************************/
/**                                                                       */
/** USBX Device CDC/ACM Example for STM32F746-DISCO Board                 */
/**                                                                       */
/** This example illustrates USBX working on a STM32F7xx processor        */
/**                                                                       */
/** This demo will show the device side of USBX. It will make the device  */
/** appear as a serial device based on CDC ACM on a host.                 */
/**                                                                       */
/** This code assumes the interrupt handler for the USB (device)          */
/** is calling the proper handlers in USBX.                               */
/**                                                                       */
/**************************************************************************/

/* Include necessary system files. */
#include "ux_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_dcd_stm32.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_stack.h"

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

VOID hardware_setup(void);
void GreenLed_Toggle(void);

/* Define local constants. */
#define UX_DEMO_DEBUG_SIZE                  (4096*8)
#define UX_DEMO_STACK_SIZE                  4096
#define UX_DEMO_BUFFER_SIZE                 512
#define UX_USBX_MEMORY_SIZE                 (32 * 1024)

/* Define local function prototypes */
void demo_thread_entry(ULONG arg);
VOID demo_cdc_instance_activate(VOID* cdc_instance);
VOID demo_cdc_instance_deactivate(VOID* cdc_instance);
void USB_OTG_BSP_HS_Init(void);

// @formatter:off

#define LOBYTE(x)							((uint8_t)((x) & 0x00FFU))
#define HIBYTE(x)							((uint8_t)(((x) & 0xFF00U) >> 8U))

#define USB_CLASS_COMMUNICATIONS			0x02
#define USB_CLASS_MISCELLANEOUS				0xEF

#define USB_CDC_ACM_SUBCLASS				0x02
#define USB_CDC_AT_COMMAND_PROTOCOL			0x01
#define USB_CLASS_CDC_DATA					0x0A

/* CDC interface descriptor type */
#define USB_DESCTYPE_CS_INTERFACE			0x24

/* Select what kind of descriptors will be used: 'Express Logic' or 'STMicroelectronis' */
#define DESCRIPTORS_EXP						0
#define DESCRIPTORS_STM						0
#define DESCRIPTORS_MDK						1

#if (DESCRIPTORS_EXP == 1)
	#define USBD_LPM_ENABLED				0
	#define USBD_IAD_ENABLED				1
	#define USBD_QUALIFIER_DESC_ENABLED		1

	#define USBD_VID						0x8484
	#define USBD_PID						0x0000
	#define USBD_BCD_DEVICE					0x0001

	/* EP2 for CDC commands */
	#define CDC_CMD_EP						(UX_ENDPOINT_IN | 2)

	/* EP1 for data IN */
	#define CDC_IN_EP						(UX_ENDPOINT_IN | 1)

	/* EP1 for data OUT */
	#define CDC_OUT_EP						(UX_ENDPOINT_OUT | 1)

	/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
	#define CDC_DATA_HS_MAX_PACKET_SIZE		512U		/* HS Endpoint IN & OUT Packet size */
	#define CDC_DATA_FS_MAX_PACKET_SIZE		64U			/* FS Endpoint IN & OUT Packet size */
	#define CDC_CMD_PACKET_SIZE				8U			/* Control Endpoint Packet size */

	#define CDC_HS_BINTERVAL				0x10U		/* 0x10 (16 ms) */
	#define CDC_FS_BINTERVAL				0x10U		/* 0x10 (16 ms) */

/* UCHAR device_framework_full_speed[] */
#if 1
UCHAR device_framework_full_speed[] =
{
	/* Device Descriptor (must be first in this array) */
	0x12,										/* 0 bLength */
	UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
	0x00,										/* 2 bcdUSB */
	0x02,										/* 3 bcdUSB */
	USB_CLASS_COMMUNICATIONS,					/* 4 bDeviceClass (Communications and CDC Control) */
	0x02,										/* 5 bDeviceSubClass - Specified by interface (Common Class: 0x02) */
	0x00,										/* 6 bDeviceProtocol - Specified by interface (No class specific protocol required: 0x00) */
	0x40,										/* 7 bMaxPacketSize0 */
	LOBYTE(USBD_VID),							/* 8 idVendor */
	HIBYTE(USBD_VID),							/* 9 idVendor */
	LOBYTE(USBD_PID),							/* 10 idProduct */
	HIBYTE(USBD_PID),							/* 11 idProduct */
	LOBYTE(USBD_BCD_DEVICE),							/* 12 bcdDevice */
	HIBYTE(USBD_BCD_DEVICE),							/* 13 bcdDevice */
	0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
	0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
	0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
	0x01,										/* 17 bNumConfigurations (1 Configuration) */

	/* Configuration Descriptor */
	0x09,										/* 0 bLength */
	UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType (Configuration Descriptor) */
	0x43,										/* 2 wTotalLength : */
	0x00,										/* 3 wTotalLength : */
	0x02,										/* 4 bNumInterfaces (2 Interfaces) */
	0x01,										/* 5 bConfigurationValue (Configuration 1) */
	0x04,										/* 6 iConfiguration (String Descriptor 4) */
	0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
	0x32,										/* 8 bMaxPower (0x32 = 100 mA) */

	/* Interface Descriptor */
	0x09,										/* 0 bLength */
	UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType (Interface Descriptor) */
	0x00,										/* 2 bInterfaceNumber - Interface 0 */
	0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
	0x01,										/* 4 bNumEndpoints      : 1 Endpoint for Interface#1 */
	USB_CLASS_COMMUNICATIONS,					/* 5 bInterfaceClass    : Communications and CDC Control (0x02) */
	USB_CDC_ACM_SUBCLASS,						/* 6 bInterfaceSubClass : Abstract Control Model (0x02) */
	USB_CDC_AT_COMMAND_PROTOCOL,				/* 7 bInterfaceProtocol : AT Commands defined by ITU-T V.250 etc (0x01) */
	0x00,										/* 8 iInterface (No String Descriptor) */

	/* Header Functional Descriptor */
	0x05,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x00,										/* 2 bDescriptorSubtype: Header Functional Descriptor (0x00) */
	0x10,										/* 3 bcdCDC (CDC Version 1.10) */
	0x01,										/* 4 bcdCDC */

	/* Call Management Functional Descriptor */
	0x05,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x01,										/* 2 bDescriptorSubtype: CALL MANAGEMENT (0x01) */
	0x00,										/* 3 bmCapabilities */
	0x01,										/* 4 bDataInterface */

	/* Abstract Control Management (ACM) Functional Descriptor */
	0x04,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x02,										/* 2 bDescriptorSubtype: ABSTRACT CONTROL MANAGEMENT (0x02) */
	0x02,										/* 3 bmCapabilities: Supports subset of ACM commands */

	/* Union Functional Descriptor */
	0x05,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x06,										/* 2 bDescriptorSubtype: UNION (0x06) */
	0x00,										/* 3 bControlInterface - Interface 0 */
	0x01,										/* 4 bSubordinateInterface0 - Interface 1 */

	/*----------------------------------------------------------------------------------------*/

	/* CDC-ACM Endpoint Descriptor (Interrupt) for Interface#0 */
	0x07,										/* 0 bLength */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	CDC_CMD_EP,									/* 2 bEndpointAddress: (CDC_CMD_EP) */
	UX_INTERRUPT_ENDPOINT,						/* 3 bmAttributes: Interrupt */
	LOBYTE(CDC_CMD_PACKET_SIZE),				/* 4 wMaxPacketSize: */
	HIBYTE(CDC_CMD_PACKET_SIZE),				/* 5 wMaxPacketSize */
	CDC_FS_BINTERVAL,							/* 6 bInterval: */

	/* CDC-ACM Data Class Interface Descriptor */
	0x09,										/* 0 bLength */
	UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	0x01,										/* 2 bInterfaceNumber */
	0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
	0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface#0 */
	USB_CLASS_CDC_DATA,							/* 5 bInterfaceClass    : Data Interface Class (0x0A) */
	0x00,										/* 6 bInterfaceSubClass : Abstract Control Model */
	0x00,										/* 7 bInterfaceProtocol : No class specific protocol required */
	0x00,										/* 8 iInterface Index   : No string descriptor */

	/* Endpoint OUT Descriptor (Data OUT) */
	0x07,										/* 0 bLength: Endpoint Descriptor size */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	CDC_OUT_EP,									/* 2 bEndpointAddress: (CDC_OUT_EP) */
	UX_BULK_ENDPOINT,							/* 3 bmAttributes */
	LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
	HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
	0x00,										/* 6 bInterval: ignore for Bulk transfer */

	/* Endpoint IN Descriptor (Data IN) */
	0x07,										/* 0 bLength: Endpoint Descriptor size */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	CDC_IN_EP,									/* 2 bEndpointAddress: (CDC_IN_EP) */
	UX_BULK_ENDPOINT,							/* 3 bmAttributes */
	LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
	HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
	0x00,										/* 6 bInterval: ignore for Bulk transfer */
};
#endif

/* UCHAR device_framework_high_speed[] */
#if 1
UCHAR device_framework_high_speed[] =
{
	/* Device Descriptor (must be first in this array) */
	0x12,										/* 0 bLength */
	UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
#if (USBD_LPM_ENABLED == 1)
	/* changed to USB version 2.01 in order to support LPM L1 suspend resume test of USBCV3.0 */
	0x01,										/* 2 bcdUSB */
	0x02,										/* 3 bcdUSB */
#else
	0x00,										/* 2 bcdUSB */
	0x02,										/* 3 bcdUSB */
#endif
	USB_CLASS_COMMUNICATIONS,					/* 4 bDeviceClass (Communications and CDC Control) */
	0x02,										/* 5 bDeviceSubClass - Specified by interface (Common Class: 0x02) */
	0x00,										/* 6 bDeviceProtocol - Specified by interface (No class specific protocol required: 0x00) */
	0x40,										/* 7 bMaxPacketSize0 */
	LOBYTE(USBD_VID),							/* 8 idVendor */
	HIBYTE(USBD_VID),							/* 9 idVendor */
	LOBYTE(USBD_PID),							/* 10 idProduct */
	HIBYTE(USBD_PID),							/* 11 idProduct */
	LOBYTE(USBD_BCD_DEVICE),							/* 12 bcdDevice */
	HIBYTE(USBD_BCD_DEVICE),							/* 13 bcdDevice */
	0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
	0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
	0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
	0x01,										/* 17 bNumConfigurations (1 Configuration) */

#if (USBD_QUALIFIER_DESC_ENABLED == 1)
	/* Device Qualifier Descriptor */
	0x0A,										/* 0 bLength */
	UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM,		/* 1 bDescriptorType */
	0x00,										/* 2 bcdUSB BCD(2.0) */
	0x02,										/* 3 bcdUSB */
	0x00,								/*0xEF*//* 4 bDeviceClass    : Device Class */
	0x00,								/*0x02*//* 5 bDeviceSubClass : Common Class(0x02) */
	0x00,										/* 6 bDeviceProtocol : none */
	0x40,										/* 7 bMaxPacketSize0 */
	0x01,										/* 8 bNumConfigs : 1 */
	0x00,										/* 9 Reserve, fixed to 0 */
#endif

#if (USBD_LPM_ENABLED == 1)
	/* Binary Object Store (BOS) Descriptor */
	0x05,										/* 0 bLength - Size of this descriptor (in bytes) */
	UX_BOS_DESCRIPTOR_ITEM,						/* 1 bDescriptorType */
	0x0C,										/* 2 wTotalLength - Length of this descriptor and all of its sub descriptors */
	0x00,										/* 3 wTotalLength - Length of this descriptor and all of its sub descriptors */
	0x01,										/* 4 bNumDeviceCaps - The number of separate device capability descriptors in the BOS */

	/* Device Capability Descriptor (USB 2.0 Extension Descriptor) */
	0x07,										/* 0 bLength */
	UX_BOS_DEVICE_CAPABILITY_DESCRIPTOR_ITEM,	/* 1 bDescriptorType (Device Capability Descriptor) */
	0x02,										/* 2 bDevCapabilityType (USB 2.0 Extension) */
	0x02,										/* 3 dev_capability_data - size varies - LPM capability bit set */
	0x00,										/* 4 dev_capability_data - size varies */
	0x00,										/* 5 dev_capability_data - size varies */
	0x00,										/* 6 dev_capability_data - size varies */
#endif

	/* Configuration Descriptor */
	0x09,										/* 0 bLength */
	UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType (Configuration Descriptor) */
#if (USBD_IAD_ENABLED == 1)
	0x4B,										/* 2 wTotalLength : This will be calculated at run-time. */
	0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
#else
	0x43,										/* 2 wTotalLength : This will be calculated at run-time. */
	0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
#endif
	0x02,										/* 4 bNumInterfaces (2 Interfaces) */
	0x01,										/* 5 bConfigurationValue (Configuration 1) */
	0x00,										/* 6 iConfiguration (No String Descriptor) */
	0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
	0x32,										/* 8 bMaxPower (0x32 = 100 mA) */

#if (USBD_IAD_ENABLED == 1)
	/* Interface Association Descriptor (IAD) */
	0x08,										/* 0 bLength */
	UX_INTERFACE_ASSOCIATION_DESCRIPTOR_ITEM,	/* 1 bDescriptorType */
	0x00,										/* 2 bFirstInterface */
	0x02,										/* 3 bInterfaceCount */
	0x02,										/* 4 bFunctionClass : Communications and CDC Control */
	0x02,										/* 5 bFunctionSubClass : Abstract Control Model */
	0x00,										/* 6 bFunctionProtocol : Standard or enhanced AT Command set protocol */
	0x00,										/* 7 iFunction : No String Descriptor */
#endif

	/* Interface Descriptor */
	0x09,										/* 0 bLength */
	UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType (Interface Descriptor) */
	0x00,										/* 2 bInterfaceNumber - Interface 0 */
	0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
	0x01,										/* 4 bNumEndpoints      : 1 Endpoint for Interface#1 */
	USB_CLASS_COMMUNICATIONS,					/* 5 bInterfaceClass    : Communications and CDC Control (0x02) */
	USB_CDC_ACM_SUBCLASS,						/* 6 bInterfaceSubClass : Abstract Control Model (0x02) */
	USB_CDC_AT_COMMAND_PROTOCOL,				/* 7 bInterfaceProtocol : AT Commands defined by ITU-T V.250 etc (0x01) */
	0x00,										/* 8 iInterface (No String Descriptor) */

	/* Header Functional Descriptor */
	0x05,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x00,										/* 2 bDescriptorSubtype: Header Functional Descriptor (0x00) */
	0x10,										/* 3 bcdCDC (CDC Version 1.10) */
	0x01,										/* 4 bcdCDC */

	/* Call Management Functional Descriptor */
	0x05,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x01,										/* 2 bDescriptorSubtype: CALL MANAGEMENT (0x01) */
	0x00,								/*0x03*//* 3 bmCapabilities */
	0x01,										/* 4 bDataInterface */

	/* Abstract Control Management (ACM) Functional Descriptor */
	0x04,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x02,										/* 2 bDescriptorSubtype: ABSTRACT CONTROL MANAGEMENT (0x02) */
	0x02,										/* 3 bmCapabilities: Supports subset of ACM commands:
					D7..4	: 0x00 (Reserved)
					D3		: 0x00 (not supports the notification Network_Connection)
					D2		: 0x00 (not supports the request Send_Break)
					D1		: 0x01 (supports the request combination of Set_Line_Coding,
							Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State)
					D0		: 0x00 (not supports the request combination of Set_Comm_Feature,
							Clear_Comm_Feature, and Get_Comm_Feature) */

	/* Union Functional Descriptor */
	0x05,										/* 0 bFunctionLength */
	USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
	0x06,										/* 2 bDescriptorSubtype: UNION (0x06) */
	0x00,										/* 3 bControlInterface - Interface 0 */
	0x01,										/* 4 bSubordinateInterface0 - Interface 1 */

	/*--------------------------------------------------------------------------------------------*/

	/* CDC-ACM Endpoint Descriptor (Interrupt) for Interface#0 */
	0x07,										/* 0 bLength */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	CDC_CMD_EP,									/* 2 bEndpointAddress: (CDC_CMD_EP) */
	UX_INTERRUPT_ENDPOINT,						/* 3 bmAttributes: Interrupt */
	LOBYTE(CDC_CMD_PACKET_SIZE),				/* 4 wMaxPacketSize: */
	HIBYTE(CDC_CMD_PACKET_SIZE),				/* 5 wMaxPacketSize */
	CDC_HS_BINTERVAL,					/*0xFF*//* 6 bInterval: */

	/* CDC-ACM Data Class Interface Descriptor */
	0x09,										/* 0 bLength */
	UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	0x01,										/* 2 bInterfaceNumber */
	0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
	0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface#0 */
	USB_CLASS_CDC_DATA,							/* 5 bInterfaceClass    : Data Interface Class (0x0A) */
	0x00,										/* 6 bInterfaceSubClass : Abstract Control Model */
	0x00,										/* 7 bInterfaceProtocol : No class specific protocol required */
	0x00,										/* 8 iInterface Index   : No string descriptor */

	/* Endpoint OUT Descriptor (Data OUT) */
	0x07,										/* 0 bLength: Endpoint Descriptor size */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	CDC_OUT_EP,									/* 2 bEndpointAddress: (CDC_OUT_EP) */
	UX_BULK_ENDPOINT,							/* 3 bmAttributes */
	LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
	HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
	0x00,										/* 6 bInterval: (never NAKs) */

	/* Endpoint IN Descriptor (Data IN) */
	0x07,										/* 0 bLength: Endpoint Descriptor size */
	UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
	CDC_IN_EP,									/* 2 bEndpointAddress: (CDC_IN_EP) */
	UX_BULK_ENDPOINT,							/* 3 bmAttributes */
	LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
	HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
	0x00,										/* 6 bInterval: (never NAKs) */
};
#endif

/* UCHAR language_id_framework[] + UCHAR string_framework[] */
#if 1
/* Multiple languages are supported on the device, to add a language besides english,
 * the unicode language code must be appended to the language_id_framework array and
 * the length adjusted accordingly. */
UCHAR language_id_framework[] =
{
	/* String Descriptor 0 (Language) */
	0x09, 0x04						/* English - United States */
};

UCHAR string_framework[] =
{
	/* String Descriptor 1 (Manufacturer - see 'Device Descriptor') */
	0x09, 0x04,						/* English - United States */
	0x01,							/* Index of the descriptor */
//	0x12,							/* Length of string below (ASCII) */
//	'S', 'T', 'M', 'i', 'c', 'r', 'o', 'e', 'l', 'e', 'c', 't', 'r', 'o', 'n', 'i', 'c', 's',
	0x0C,							/* Length of string below (ASCII) */
	'E', 'x', 'p', 'r', 'e', 's', ' ', 'L', 'o', 'g', 'i', 'c',

	/* String Descriptor 2 (Product - see 'Device Descriptor') */
	0x09, 0x04,						/* English - United States */
	0x02,							/* Index of the descriptor */
//	0x15,							/* Length of string below (ASCII) */
//	'S', 'T', 'M', '3', '2', ' ', 'V', 'i', 'r', 't', 'u', 'a', 'l', ' ', 'C', 'o', 'm', 'P', 'o', 'r', 't',
	0x13,							/* Length of string below (ASCII) */
	'E', 'L', ' ', 'C', 'o', 'm', 'p', 'o', 's', 'i', 't', 'e', ' ', 'd', 'e', 'v', 'i', 'c', 'e',

	/* String Descriptor 3 (Serial Number - see 'Device Descriptor') */
	0x09, 0x04,						/* English - United States */
	0x03,							/* Index of the descriptor */
//	0x0C,							/* Length of string below (ASCII) */
//	'3', '9', '7', '4', '3', '9', '6', 'C', '3', '0', '3', '5',
	0x04,							/* Length of string below (ASCII) */
	'0', '0', '0', '1',

	/* String Descriptor 4 (Config) */
	0x09, 0x04,						/* English - United States */
	0x04,							/* Index of the descriptor */
	0x0A,							/* Length of string below (ASCII) */
	'C', 'D', 'C', ' ', 'C', 'o', 'n', 'f', 'i', 'g',
};

#endif

#elif (DESCRIPTORS_STM == 1)
	#define USBD_LPM_ENABLED				0
	#define USBD_IAD_ENABLED				0
	#define USBD_QUALIFIER_DESC_ENABLED		1

	#define USBD_VID						0x0483		/* 1155U */
	#define USBD_PID						0x5740		/* 22336U */
	#define USBD_BCD_DEVICE					0x0200

	/* EP2 for CDC commands */
	#define CDC_CMD_EP						(UX_ENDPOINT_IN | 2)

	/* EP1 for data IN */
	#define CDC_IN_EP						(UX_ENDPOINT_IN | 1)

	/* EP1 for data OUT */
	#define CDC_OUT_EP						(UX_ENDPOINT_OUT | 1)

	/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
	#define CDC_DATA_HS_MAX_PACKET_SIZE		512U		/* HS Endpoint IN & OUT Packet size */
	#define CDC_DATA_FS_MAX_PACKET_SIZE		64U			/* FS Endpoint IN & OUT Packet size */
	#define CDC_CMD_PACKET_SIZE				8U			/* Control Endpoint Packet size */

	#define CDC_HS_BINTERVAL				0x10U		/* 0x10 (16 ms) */
	#define CDC_FS_BINTERVAL				0x10U		/* 0x10 (16 ms) */

	/* UCHAR device_framework_full_speed[] */
	#if 1
	UCHAR device_framework_full_speed[] =
	{
		/* Device Descriptor (must be first in this array) */
		0x12,										/* 0 bLength */
		UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
		0x00,										/* 2 bcdUSB */
		0x02,										/* 3 bcdUSB */
		USB_CLASS_COMMUNICATIONS,					/* 4 bDeviceClass (Communications and CDC Control) */
		0x02,										/* 5 bDeviceSubClass - Specified by interface (Common Class: 0x02) */
		0x00,										/* 6 bDeviceProtocol - Specified by interface (No class specific protocol required: 0x00) */
		0x40,										/* 7 bMaxPacketSize0 */
		LOBYTE(USBD_VID),							/* 8 idVendor */
		HIBYTE(USBD_VID),							/* 9 idVendor */
		LOBYTE(USBD_PID),							/* 10 idProduct */
		HIBYTE(USBD_PID),							/* 11 idProduct */
		LOBYTE(USBD_BCD_DEVICE),							/* 12 bcdDevice */
		HIBYTE(USBD_BCD_DEVICE),							/* 13 bcdDevice */
		0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
		0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
		0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
		0x01,										/* 17 bNumConfigurations (1 Configuration) */

		/* Configuration Descriptor */
		0x09,										/* 0 bLength */
		UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType (Configuration Descriptor) */
		0x43,										/* 2 wTotalLength : */
		0x00,										/* 3 wTotalLength : */
		0x02,										/* 4 bNumInterfaces (2 Interfaces) */
		0x01,										/* 5 bConfigurationValue (Configuration 1) */
		0x04,										/* 6 iConfiguration (String Descriptor 4) */
		0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
		0x32,										/* 8 bMaxPower (0x32 = 100 mA) */

		/* Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType (Interface Descriptor) */
		0x00,										/* 2 bInterfaceNumber - Interface 0 */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x01,										/* 4 bNumEndpoints      : 1 Endpoint for Interface#1 */
		USB_CLASS_COMMUNICATIONS,					/* 5 bInterfaceClass    : Communications and CDC Control (0x02) */
		USB_CDC_ACM_SUBCLASS,						/* 6 bInterfaceSubClass : Abstract Control Model (0x02) */
		USB_CDC_AT_COMMAND_PROTOCOL,				/* 7 bInterfaceProtocol : AT Commands defined by ITU-T V.250 etc (0x01) */
		0x00,										/* 8 iInterface (No String Descriptor) */

		/* Header Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x00,										/* 2 bDescriptorSubtype: Header Functional Descriptor (0x00) */
		0x10,										/* 3 bcdCDC (CDC Version 1.10) */
		0x01,										/* 4 bcdCDC */

		/* Call Management Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x01,										/* 2 bDescriptorSubtype: CALL MANAGEMENT (0x01) */
		0x00,										/* 3 bmCapabilities */
		0x01,										/* 4 bDataInterface */

		/* Abstract Control Management (ACM) Functional Descriptor */
		0x04,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x02,										/* 2 bDescriptorSubtype: ABSTRACT CONTROL MANAGEMENT (0x02) */
		0x02,										/* 3 bmCapabilities: Supports subset of ACM commands */

		/* Union Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x06,										/* 2 bDescriptorSubtype: UNION (0x06) */
		0x00,										/* 3 bControlInterface - Interface 0 */
		0x01,										/* 4 bSubordinateInterface0 - Interface 1 */

		/*----------------------------------------------------------------------------------------*/

		/* CDC-ACM Endpoint Descriptor (Interrupt) for Interface#0 */
		0x07,										/* 0 bLength */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_CMD_EP,									/* 2 bEndpointAddress: (CDC_CMD_EP) */
		UX_INTERRUPT_ENDPOINT,						/* 3 bmAttributes: Interrupt */
		LOBYTE(CDC_CMD_PACKET_SIZE),				/* 4 wMaxPacketSize: */
		HIBYTE(CDC_CMD_PACKET_SIZE),				/* 5 wMaxPacketSize */
		CDC_FS_BINTERVAL,							/* 6 bInterval: */

		/* CDC-ACM Data Class Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		0x01,										/* 2 bInterfaceNumber */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface#0 */
		USB_CLASS_CDC_DATA,							/* 5 bInterfaceClass    : Data Interface Class (0x0A) */
		0x00,										/* 6 bInterfaceSubClass : Abstract Control Model */
		0x00,										/* 7 bInterfaceProtocol : No class specific protocol required */
		0x00,										/* 8 iInterface Index   : No string descriptor */

		/* Endpoint OUT Descriptor (Data OUT) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_OUT_EP,									/* 2 bEndpointAddress: (CDC_OUT_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: ignore for Bulk transfer */

		/* Endpoint IN Descriptor (Data IN) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_IN_EP,									/* 2 bEndpointAddress: (CDC_IN_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: ignore for Bulk transfer */
	};
	#endif

	/* UCHAR device_framework_high_speed[] */
	#if 1
	UCHAR device_framework_high_speed[] =
	{
		/* Device Descriptor (must be first in this array) */
		0x12,										/* 0 bLength */
		UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
	#if (USBD_LPM_ENABLED == 1)
		/* changed to USB version 2.01 in order to support LPM L1 suspend resume test of USBCV3.0 */
		0x01,										/* 2 bcdUSB */
		0x02,										/* 3 bcdUSB */
	#else
		0x00,										/* 2 bcdUSB */
		0x02,										/* 3 bcdUSB */
	#endif
		USB_CLASS_COMMUNICATIONS,					/* 4 bDeviceClass (Communications and CDC Control) */
		0x02,										/* 5 bDeviceSubClass - Specified by interface (Common Class: 0x02) */
		0x00,										/* 6 bDeviceProtocol - Specified by interface (No class specific protocol required: 0x00) */
		0x40,										/* 7 bMaxPacketSize0 */
		LOBYTE(USBD_VID),							/* 8 idVendor */
		HIBYTE(USBD_VID),							/* 9 idVendor */
		LOBYTE(USBD_PID),							/* 10 idProduct */
		HIBYTE(USBD_PID),							/* 11 idProduct */
		LOBYTE(USBD_BCD_DEVICE),							/* 12 bcdDevice */
		HIBYTE(USBD_BCD_DEVICE),							/* 13 bcdDevice */
		0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
		0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
		0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
		0x01,										/* 17 bNumConfigurations (1 Configuration) */

	#if (USBD_QUALIFIER_DESC_ENABLED == 1)
		/* Device Qualifier Descriptor */
		0x0A,										/* 0 bLength */
		UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM,		/* 1 bDescriptorType */
		0x00,										/* 2 bcdUSB BCD(2.0) */
		0x02,										/* 3 bcdUSB */
		0x00,								/*0xEF*//* 4 bDeviceClass    : Device Class */
		0x00,								/*0x02*//* 5 bDeviceSubClass : Common Class(0x02) */
		0x00,										/* 6 bDeviceProtocol : none */
		0x40,										/* 7 bMaxPacketSize0 */
		0x01,										/* 8 bNumConfigs : 1 */
		0x00,										/* 9 Reserve, fixed to 0 */
	#endif

	#if (USBD_LPM_ENABLED == 1)
		/* Binary Object Store (BOS) Descriptor */
		0x05,										/* 0 bLength - Size of this descriptor (in bytes) */
		UX_BOS_DESCRIPTOR_ITEM,						/* 1 bDescriptorType */
		0x0C,										/* 2 wTotalLength - Length of this descriptor and all of its sub descriptors */
		0x00,										/* 3 wTotalLength - Length of this descriptor and all of its sub descriptors */
		0x01,										/* 4 bNumDeviceCaps - The number of separate device capability descriptors in the BOS */
	
		/* Device Capability Descriptor (USB 2.0 Extension Descriptor) */
		0x07,										/* 0 bLength */
		UX_BOS_DEVICE_CAPABILITY_DESCRIPTOR_ITEM,	/* 1 bDescriptorType (Device Capability Descriptor) */
		0x02,										/* 2 bDevCapabilityType (USB 2.0 Extension) */
		0x02,										/* 3 dev_capability_data - size varies - LPM capability bit set */
		0x00,										/* 4 dev_capability_data - size varies */
		0x00,										/* 5 dev_capability_data - size varies */
		0x00,										/* 6 dev_capability_data - size varies */
	#endif

		/* Configuration Descriptor */
		0x09,										/* 0 bLength */
		UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType (Configuration Descriptor) */
	#if (USBD_IAD_ENABLED == 1)
		0x4B,										/* 2 wTotalLength : This will be calculated at run-time. */
		0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	#else
		0x43,										/* 2 wTotalLength : This will be calculated at run-time. */
		0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	#endif
		0x02,										/* 4 bNumInterfaces (2 Interfaces) */
		0x01,										/* 5 bConfigurationValue (Configuration 1) */
		0x00,										/* 6 iConfiguration (No String Descriptor) */
		0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
		0x32,										/* 8 bMaxPower (0x32 = 100 mA) */

	#if (USBD_IAD_ENABLED == 1)
		/* Interface Association Descriptor (IAD) */
		0x08,										/* 0 bLength */
		UX_INTERFACE_ASSOCIATION_DESCRIPTOR_ITEM,	/* 1 bDescriptorType */
		0x00,										/* 2 bFirstInterface */
		0x02,										/* 3 bInterfaceCount */
		0x02,										/* 4 bFunctionClass : Communications and CDC Control */
		0x02,										/* 5 bFunctionSubClass : Abstract Control Model */
		0x00,										/* 6 bFunctionProtocol : Standard or enhanced AT Command set protocol */
		0x00,										/* 7 iFunction : No String Descriptor */
	#endif

		/* Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType (Interface Descriptor) */
		0x00,										/* 2 bInterfaceNumber - Interface 0 */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x01,										/* 4 bNumEndpoints      : 1 Endpoint for Interface#1 */
		USB_CLASS_COMMUNICATIONS,					/* 5 bInterfaceClass    : Communications and CDC Control (0x02) */
		USB_CDC_ACM_SUBCLASS,						/* 6 bInterfaceSubClass : Abstract Control Model (0x02) */
		USB_CDC_AT_COMMAND_PROTOCOL,				/* 7 bInterfaceProtocol : AT Commands defined by ITU-T V.250 etc (0x01) */
		0x00,										/* 8 iInterface (No String Descriptor) */

		/* Header Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x00,										/* 2 bDescriptorSubtype: Header Functional Descriptor (0x00) */
		0x10,										/* 3 bcdCDC (CDC Version 1.10) */
		0x01,										/* 4 bcdCDC */

		/* Call Management Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x01,										/* 2 bDescriptorSubtype: CALL MANAGEMENT (0x01) */
		0x00,								/*0x03*//* 3 bmCapabilities */
		0x01,										/* 4 bDataInterface */

		/* Abstract Control Management (ACM) Functional Descriptor */
		0x04,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x02,										/* 2 bDescriptorSubtype: ABSTRACT CONTROL MANAGEMENT (0x02) */
		0x02,										/* 3 bmCapabilities: Supports subset of ACM commands:
						D7..4	: 0x00 (Reserved)
						D3		: 0x00 (not supports the notification Network_Connection)
						D2		: 0x00 (not supports the request Send_Break)
						D1		: 0x01 (supports the request combination of Set_Line_Coding,
								Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State)
						D0		: 0x00 (not supports the request combination of Set_Comm_Feature,
								Clear_Comm_Feature, and Get_Comm_Feature) */

		/* Union Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x06,										/* 2 bDescriptorSubtype: UNION (0x06) */
		0x00,										/* 3 bControlInterface - Interface 0 */
		0x01,										/* 4 bSubordinateInterface0 - Interface 1 */

		/*--------------------------------------------------------------------------------------------*/

		/* CDC-ACM Endpoint Descriptor (Interrupt) for Interface#0 */
		0x07,										/* 0 bLength */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_CMD_EP,									/* 2 bEndpointAddress: (CDC_CMD_EP) */
		UX_INTERRUPT_ENDPOINT,						/* 3 bmAttributes: Interrupt */
		LOBYTE(CDC_CMD_PACKET_SIZE),				/* 4 wMaxPacketSize: */
		HIBYTE(CDC_CMD_PACKET_SIZE),				/* 5 wMaxPacketSize */
		CDC_HS_BINTERVAL,					/*0xFF*//* 6 bInterval: */

		/* CDC-ACM Data Class Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		0x01,										/* 2 bInterfaceNumber */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface#0 */
		USB_CLASS_CDC_DATA,							/* 5 bInterfaceClass    : Data Interface Class (0x0A) */
		0x00,										/* 6 bInterfaceSubClass : Abstract Control Model */
		0x00,										/* 7 bInterfaceProtocol : No class specific protocol required */
		0x00,										/* 8 iInterface Index   : No string descriptor */

		/* Endpoint OUT Descriptor (Data OUT) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_OUT_EP,									/* 2 bEndpointAddress: (CDC_OUT_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: (never NAKs) */
	
		/* Endpoint IN Descriptor (Data IN) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_IN_EP,									/* 2 bEndpointAddress: (CDC_IN_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: (never NAKs) */
	};
	#endif

	/* UCHAR language_id_framework[] + UCHAR string_framework[] */
	#if 1
	/* Multiple languages are supported on the device, to add a language besides english,
	 * the unicode language code must be appended to the language_id_framework array and
	 * the length adjusted accordingly. */
	UCHAR language_id_framework[] =
	{
		/* String Descriptor 0 (Language) */
		0x09, 0x04						/* English - United States */
	};

	UCHAR string_framework[] =
	{
		/* String Descriptor 1 (Manufacturer - see 'Device Descriptor') */
		0x09, 0x04,						/* English - United States */
		0x01,							/* Index of the descriptor */
	//	0x12,							/* Length of string below (ASCII) */
	//	'S', 'T', 'M', 'i', 'c', 'r', 'o', 'e', 'l', 'e', 'c', 't', 'r', 'o', 'n', 'i', 'c', 's',
		0x0C,							/* Length of string below (ASCII) */
		'E', 'x', 'p', 'r', 'e', 's', ' ', 'L', 'o', 'g', 'i', 'c',

		/* String Descriptor 2 (Product - see 'Device Descriptor') */
		0x09, 0x04,						/* English - United States */
		0x02,							/* Index of the descriptor */
	//	0x15,							/* Length of string below (ASCII) */
	//	'S', 'T', 'M', '3', '2', ' ', 'V', 'i', 'r', 't', 'u', 'a', 'l', ' ', 'C', 'o', 'm', 'P', 'o', 'r', 't',
		0x13,							/* Length of string below (ASCII) */
		'E', 'L', ' ', 'C', 'o', 'm', 'p', 'o', 's', 'i', 't', 'e', ' ', 'd', 'e', 'v', 'i', 'c', 'e',

		/* String Descriptor 3 (Serial Number - see 'Device Descriptor') */
		0x09, 0x04,						/* English - United States */
		0x03,							/* Index of the descriptor */
	//	0x0C,							/* Length of string below (ASCII) */
	//	'3', '9', '7', '4', '3', '9', '6', 'C', '3', '0', '3', '5',
		0x04,							/* Length of string below (ASCII) */
		'0', '0', '0', '1',

		/* String Descriptor 4 (Config) */
		0x09, 0x04,						/* English - United States */
		0x04,							/* Index of the descriptor */
		0x0A,							/* Length of string below (ASCII) */
		'C', 'D', 'C', ' ', 'C', 'o', 'n', 'f', 'i', 'g',
	};

	#endif

#elif (DESCRIPTORS_MDK == 1)
	#define USBD_LPM_ENABLED				0
	#define USBD_IAD_ENABLED				1
	#define USBD_QUALIFIER_DESC_ENABLED		1

	#define USBD_VID						0x0483
	#define USBD_PID						0x5741
	#define USBD_BCD_DEVICE					0x0200

//	#define USBD_VID						0x8484
//	#define USBD_PID						0x0000
//	#define USBD_BCD_DEVICE					0x0001

//	#define USBD_VID						0x0283
//	#define USBD_PID						0x01FF
//	#define USBD_BCD_DEVICE					0x0200

	/* EP2 for CDC commands */
	#define CDC_CMD_EP						(UX_ENDPOINT_IN | 3)	// 3 // 2

	/* EP1 for data IN */
	#define CDC_IN_EP						(UX_ENDPOINT_IN | 1)

	/* EP1 for data OUT */
	#define CDC_OUT_EP						(UX_ENDPOINT_OUT | 2)	// 2 // 1

	/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
	#define CDC_DATA_HS_MAX_PACKET_SIZE		512U		/* HS Endpoint IN & OUT Packet size */
	#define CDC_DATA_FS_MAX_PACKET_SIZE		64U			/* FS Endpoint IN & OUT Packet size */
	#define CDC_CMD_PACKET_SIZE				8U			/* Control Endpoint Packet size */

	#define CDC_HS_BINTERVAL				0x10U		/* 0x10 (16 ms) */
	#define CDC_FS_BINTERVAL				0x10U		/* 0x10 (16 ms) */

	#define INTERF_COM_NUM						0x00		/*0x01*/
	#define INTERF_DAT_NUM						0x01

	/* UCHAR device_framework_full_speed[] */
	#if 1
	UCHAR device_framework_full_speed[] =
	{
		/* Device Descriptor (must be first in this array) */
		0x12,										/* 0 bLength */
		UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
		0x00,										/* 2 bcdUSB */
		0x02,										/* 3 bcdUSB */
		USB_CLASS_MISCELLANEOUS,					/* 4 bDeviceClass */
		0x02,										/* 5 bDeviceSubClass (Common Class: 0x02) */
		0x01,										/* 6 bDeviceProtocol (IAD: 0x01) */
		0x08,										/* 7 bMaxPacketSize0 */
		LOBYTE(USBD_VID),							/* 8 idVendor */
		HIBYTE(USBD_VID),							/* 9 idVendor */
		LOBYTE(USBD_PID),							/* 10 idProduct */
		HIBYTE(USBD_PID),							/* 11 idProduct */
		LOBYTE(USBD_BCD_DEVICE),							/* 12 bcdDevice */
		HIBYTE(USBD_BCD_DEVICE),							/* 13 bcdDevice */
		0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
		0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
		0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
		0x01,										/* 17 bNumConfigurations (1 Configuration) */

		/* Configuration Descriptor */
	#if 1
		0x09,										/* 0 bLength */
		UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType (Configuration Descriptor) */
	#if (USBD_IAD_ENABLED == 1)
		0x4B,										/* 2 wTotalLength : This will be calculated at run-time. */
		0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	#else
		0x43,										/* 2 wTotalLength : This will be calculated at run-time. */
		0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	#endif
		0x02,										/* 4 bNumInterfaces (2 Interfaces) */
		0x01,										/* 5 bConfigurationValue (Configuration 1) */
		0x00,										/* 6 iConfiguration (No String Descriptor) */
		0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
		0x32,										/* 8 bMaxPower (0x32 = 100 mA) */
	#endif

		/* Interface Association Descriptor (IAD) */
	#if (USBD_IAD_ENABLED == 1)
		0x08,										/* 0 bLength */
		UX_INTERFACE_ASSOCIATION_DESCRIPTOR_ITEM,	/* 1 bDescriptorType */
		INTERF_COM_NUM,									/* 2 bFirstInterface */
		0x02,										/* 3 bInterfaceCount */
		0x02,										/* 4 bFunctionClass : Communications and CDC Control */
		0x02,										/* 5 bFunctionSubClass : Abstract Control Model */
		0x01,										/* 6 bFunctionProtocol : Standard or enhanced AT Command set protocol */
		0x00,										/* 7 iFunction : No String Descriptor */
	#endif

		/* Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType (Interface Descriptor) */
		INTERF_COM_NUM,									/* 2 bInterfaceNumber */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x01,										/* 4 bNumEndpoints      : 1 Endpoint for Interface */
//		UX_SLAVE_CLASS_CDC_ACM_CLASS,
		USB_CLASS_COMMUNICATIONS,					/* 5 bInterfaceClass    : Communications and CDC Control (0x02) */
		USB_CDC_ACM_SUBCLASS,						/* 6 bInterfaceSubClass : Abstract Control Model (0x02) */
		USB_CDC_AT_COMMAND_PROTOCOL,				/* 7 bInterfaceProtocol : AT Commands defined by ITU-T V.250 etc (0x01) */
		0x00,										/* 8 iInterface (No String Descriptor) */

#if 1
		/* Header Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x00,										/* 2 bDescriptorSubtype: HEADER (0x00) */
		0x10,										/* 3 bcdCDC (CDC Version 1.10) */
		0x01,										/* 4 bcdCDC */

		/* Call Management Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x01,										/* 2 bDescriptorSubtype: CALL MANAGEMENT (0x01) */
		0x03,										/* 3 bmCapabilities */
		INTERF_DAT_NUM,									/* 4 bDataInterface */

		/* Abstract Control Management (ACM) Functional Descriptor */
		0x04,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x02,										/* 2 bDescriptorSubtype: ABSTRACT CONTROL MANAGEMENT (0x02) */
		0x02,										/* 3 bmCapabilities: Supports subset of ACM commands:
						D7..4	: 0x00 (Reserved)
						D3		: 0x00 (not supports the notification Network_Connection)
						D2		: 0x00 (not supports the request Send_Break)
						D1		: 0x01 (supports the request combination of Set_Line_Coding,
								Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State)
						D0		: 0x00 (not supports the request combination of Set_Comm_Feature,
								Clear_Comm_Feature, and Get_Comm_Feature) */

		/* Union Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x06,										/* 2 bDescriptorSubtype: UNION (0x06) */
		INTERF_COM_NUM,									/* 3 bControlInterface - Interface 0 */
		INTERF_DAT_NUM,									/* 4 bSubordinateInterface0 - Interface 1 */
#endif

		/* CDC-ACM Endpoint Descriptor (Interrupt) for Interface#0 */
		0x07,										/* 0 bLength */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_CMD_EP,									/* 2 bEndpointAddress: (CDC_CMD_EP) */
		UX_INTERRUPT_ENDPOINT,						/* 3 bmAttributes: Interrupt */
		LOBYTE(CDC_CMD_PACKET_SIZE),				/* 4 wMaxPacketSize: */
		HIBYTE(CDC_CMD_PACKET_SIZE),				/* 5 wMaxPacketSize */
		CDC_FS_BINTERVAL,							/* 6 bInterval: */

		/* CDC-ACM Data Class Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		INTERF_DAT_NUM,									/* 2 bInterfaceNumber */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface */
		USB_CLASS_CDC_DATA,							/* 5 bInterfaceClass    : Data Interface Class (0x0A) */
		0x00,										/* 6 bInterfaceSubClass : Abstract Control Model */
		0x00,										/* 7 bInterfaceProtocol : No class specific protocol required */
		0x00,										/* 8 iInterface Index   : No string descriptor */

		/* Endpoint OUT Descriptor (Data OUT) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_OUT_EP,									/* 2 bEndpointAddress: (CDC_OUT_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: (never NAKs) */

		/* Endpoint IN Descriptor (Data IN) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_IN_EP,									/* 2 bEndpointAddress: (CDC_IN_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_FS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: (never NAKs) */
	};

	#endif

	/* UCHAR device_framework_high_speed[] */
	#if 1
	UCHAR device_framework_high_speed[] =
	{
		/* The following descriptors are required in an USB CDC ACM Device:
		 * 
		 * + Standard Device Descriptor
		 * + Standard Configuration Descriptor
		 * + Interface Association Descriptor
		 * CDC Header Functional Descriptor
		 * CDC Union Functional Descriptor
		 * Call Management Functional Descriptor
		 * Abstract Control Management Functional Descriptor
		 * Standard Interface Descriptor for the CDC Class communication interface
		 * Standard Endpoint Descriptor for Interrupt IN endpoint
		 * Standard Interface Descriptor for the CDC Class data interface
		 * Standard Endpoint Descriptors for Bulk IN and Bulk OUT endpoints
		 */

		/* Device Descriptor (must be first in this array) */
	#if 1
		0x12,										/* 0 bLength */
		UX_DEVICE_DESCRIPTOR_ITEM,					/* 1 bDescriptorType (Device Descriptor) */
		0x00,										/* 2 bcdUSB */
		0x02,										/* 3 bcdUSB */
		USB_CLASS_MISCELLANEOUS,					/* 4 bDeviceClass */
		0x02,										/* 5 bDeviceSubClass (Common Class: 0x02) */
		0x01,										/* 6 bDeviceProtocol (IAD: 0x01) */
		0x40,										/* 7 bMaxPacketSize0 */
		LOBYTE(USBD_VID),							/* 8 idVendor */
		HIBYTE(USBD_VID),							/* 9 idVendor */
		LOBYTE(USBD_PID),							/* 10 idProduct */
		HIBYTE(USBD_PID),							/* 11 idProduct */
		LOBYTE(USBD_BCD_DEVICE),					/* 12 bcdDevice */
		HIBYTE(USBD_BCD_DEVICE),					/* 13 bcdDevice */
		0x01,										/* 14 iManufacturer - Index of Manufacturer string (String Descriptor 1) */
		0x02,										/* 15 iProduct - Index of Product string (String Descriptor 2) */
		0x03,										/* 16 iSerialNumber - Index of Serial Number string (String Descriptor 3) */
		0x01,										/* 17 bNumConfigurations (1 Configuration) */
	#endif

	#if (USBD_QUALIFIER_DESC_ENABLED == 1)
		/* Device Qualifier Descriptor */
		0x0A,										/* 0 bLength */
		UX_DEVICE_QUALIFIER_DESCRIPTOR_ITEM,		/* 1 bDescriptorType */
		0x00,										/* 2 bcdUSB BCD(2.0) */
		0x02,										/* 3 bcdUSB */
		USB_CLASS_COMMUNICATIONS,					/* 4 bDeviceClass    : Device Class */
		0x00,										/* 5 bDeviceSubClass : Common Class(0x02) */
		0x00,										/* 6 bDeviceProtocol : none */
		0x40,										/* 7 bMaxPacketSize0 */
		0x01,										/* 8 bNumConfigs : 1 */
		0x00,										/* 9 Reserve, fixed to 0 */
	#endif

		/* Configuration Descriptor */
	#if 1
		0x09,										/* 0 bLength */
		UX_CONFIGURATION_DESCRIPTOR_ITEM,			/* 1 bDescriptorType (Configuration Descriptor) */
	#if (USBD_IAD_ENABLED == 1)
		0x4B,										/* 2 wTotalLength : This will be calculated at run-time. */
		0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	#else
		0x43,										/* 2 wTotalLength : This will be calculated at run-time. */
		0x00,										/* 3 wTotalLength : This will be calculated at run-time. */
	#endif
		0x02,										/* 4 bNumInterfaces (2 Interfaces) */
		0x01,										/* 5 bConfigurationValue (Configuration 1) */
		0x00,										/* 6 iConfiguration (No String Descriptor) */
		0x80 | (1 << 6) | (0 << 5),					/* 7 bmAttributes (D7: Reserved, set 1; D6: Self Powered; D5: Remote Wakeup; D4..0: Reserved, set 0) */
		0x32,										/* 8 bMaxPower (0x32 = 100 mA) */
	#endif

		/* Interface Association Descriptor (IAD) */
	#if (USBD_IAD_ENABLED == 1)
		0x08,										/* 0 bLength */
		UX_INTERFACE_ASSOCIATION_DESCRIPTOR_ITEM,	/* 1 bDescriptorType */
		INTERF_COM_NUM,									/* 2 bFirstInterface */
		0x02,										/* 3 bInterfaceCount */
		0x02,										/* 4 bFunctionClass : Communications and CDC Control */
		0x02,										/* 5 bFunctionSubClass : Abstract Control Model */
		0x01,										/* 6 bFunctionProtocol : Standard or enhanced AT Command set protocol */
		0x00,										/* 7 iFunction : No String Descriptor */
	#endif

		/* Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType (Interface Descriptor) */
		INTERF_COM_NUM,									/* 2 bInterfaceNumber */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x01,										/* 4 bNumEndpoints      : 1 Endpoint for Interface */
//		UX_SLAVE_CLASS_CDC_ACM_CLASS,
		USB_CLASS_COMMUNICATIONS,					/* 5 bInterfaceClass    : Communications and CDC Control (0x02) */
		USB_CDC_ACM_SUBCLASS,						/* 6 bInterfaceSubClass : Abstract Control Model (0x02) */
		USB_CDC_AT_COMMAND_PROTOCOL,				/* 7 bInterfaceProtocol : AT Commands defined by ITU-T V.250 etc (0x01) */
		0x00,										/* 8 iInterface (No String Descriptor) */

#if 1
		/* Header Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x00,										/* 2 bDescriptorSubtype: HEADER (0x00) */
		0x10,										/* 3 bcdCDC (CDC Version 1.10) */
		0x01,										/* 4 bcdCDC */

		/* Call Management Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x01,										/* 2 bDescriptorSubtype: CALL MANAGEMENT (0x01) */
		0x03,										/* 3 bmCapabilities */
		INTERF_DAT_NUM,									/* 4 bDataInterface */

		/* Abstract Control Management (ACM) Functional Descriptor */
		0x04,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x02,										/* 2 bDescriptorSubtype: ABSTRACT CONTROL MANAGEMENT (0x02) */
		0x02,										/* 3 bmCapabilities: Supports subset of ACM commands:
						D7..4	: 0x00 (Reserved)
						D3		: 0x00 (not supports the notification Network_Connection)
						D2		: 0x00 (not supports the request Send_Break)
						D1		: 0x01 (supports the request combination of Set_Line_Coding,
								Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State)
						D0		: 0x00 (not supports the request combination of Set_Comm_Feature,
								Clear_Comm_Feature, and Get_Comm_Feature) */

		/* Union Functional Descriptor */
		0x05,										/* 0 bFunctionLength */
		USB_DESCTYPE_CS_INTERFACE,					/* 1 bDescriptorType: CS_INTERFACE */
		0x06,										/* 2 bDescriptorSubtype: UNION (0x06) */
		INTERF_COM_NUM,									/* 3 bControlInterface - Interface 0 */
		INTERF_DAT_NUM,									/* 4 bSubordinateInterface0 - Interface 1 */
#endif

		/* CDC-ACM Endpoint Descriptor (Interrupt) for Interface#0 */
		0x07,										/* 0 bLength */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_CMD_EP,									/* 2 bEndpointAddress: (CDC_CMD_EP) */
		UX_INTERRUPT_ENDPOINT,						/* 3 bmAttributes: Interrupt */
		LOBYTE(CDC_CMD_PACKET_SIZE),				/* 4 wMaxPacketSize: */
		HIBYTE(CDC_CMD_PACKET_SIZE),				/* 5 wMaxPacketSize */
		CDC_HS_BINTERVAL,							/* 6 bInterval: */

		/* CDC-ACM Data Class Interface Descriptor */
		0x09,										/* 0 bLength */
		UX_INTERFACE_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		INTERF_DAT_NUM,									/* 2 bInterfaceNumber */
		0x00,										/* 3 bAlternateSetting  : Alternate for SetInterface Request */
		0x02,										/* 4 bNumEndpoints      : 2 Endpoints for Interface */
		USB_CLASS_CDC_DATA,							/* 5 bInterfaceClass    : Data Interface Class (0x0A) */
		0x00,										/* 6 bInterfaceSubClass : Abstract Control Model */
		0x00,										/* 7 bInterfaceProtocol : No class specific protocol required */
		0x00,										/* 8 iInterface Index   : No string descriptor */

		/* Endpoint OUT Descriptor (Data OUT) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_OUT_EP,									/* 2 bEndpointAddress: (CDC_OUT_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: (never NAKs) */

		/* Endpoint IN Descriptor (Data IN) */
		0x07,										/* 0 bLength: Endpoint Descriptor size */
		UX_ENDPOINT_DESCRIPTOR_ITEM,				/* 1 bDescriptorType */
		CDC_IN_EP,									/* 2 bEndpointAddress: (CDC_IN_EP) */
		UX_BULK_ENDPOINT,							/* 3 bmAttributes */
		LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 4 wMaxPacketSize: */
		HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),		/* 5 wMaxPacketSize: */
		0x00,										/* 6 bInterval: (never NAKs) */
	};

	#endif

	/* UCHAR language_id_framework[] + UCHAR string_framework[] */
	#if 1
	/* Multiple languages are supported on the device, to add a language besides english,
	 * the unicode language code must be appended to the language_id_framework array and
	 * the length adjusted accordingly. */
	UCHAR language_id_framework[] =
	{
		/* String Descriptor 0 (Language) */
		0x09, 0x04						/* English - United States */
	};

	UCHAR string_framework[] =
	{
		/* String Descriptor 1 (Manufacturer - see 'Device Descriptor') */
		0x09, 0x04,						/* English - United States */
		0x01,							/* Index of the descriptor */
	//	0x12,							/* Length of string below (ASCII) */
	//	'S', 'T', 'M', 'i', 'c', 'r', 'o', 'e', 'l', 'e', 'c', 't', 'r', 'o', 'n', 'i', 'c', 's',
		0x0C,							/* Length of string below (ASCII) */
		'E', 'x', 'p', 'r', 'e', 's', ' ', 'L', 'o', 'g', 'i', 'c',

		/* String Descriptor 2 (Product - see 'Device Descriptor') */
		0x09, 0x04,						/* English - United States */
		0x02,							/* Index of the descriptor */
	//	0x15,							/* Length of string below (ASCII) */
	//	'S', 'T', 'M', '3', '2', ' ', 'V', 'i', 'r', 't', 'u', 'a', 'l', ' ', 'C', 'o', 'm', 'P', 'o', 'r', 't',
		0x13,							/* Length of string below (ASCII) */
		'E', 'L', ' ', 'C', 'o', 'm', 'p', 'o', 's', 'i', 't', 'e', ' ', 'd', 'e', 'v', 'i', 'c', 'e',

		/* String Descriptor 3 (Serial Number - see 'Device Descriptor') */
		0x09, 0x04,						/* English - United States */
		0x03,							/* Index of the descriptor */
	//	0x0C,							/* Length of string below (ASCII) */
	//	'3', '9', '7', '4', '3', '9', '6', 'C', '3', '0', '3', '5',
		0x04,							/* Length of string below (ASCII) */
		'0', '0', '0', '1',

		/* String Descriptor 4 (Config) */
		0x09, 0x04,						/* English - United States */
		0x04,							/* Index of the descriptor */
		0x0A,							/* Length of string below (ASCII) */
		'C', 'D', 'C', ' ', 'C', 'o', 'n', 'f', 'i', 'g',
	};

	#endif
#endif

// @formatter:on

VOID _hardware_setup(void);

int main(int argc, char** argv)
{
	/* Setup the hardware: MPU, CACHE, HAL_Init, Clock, SDRAM, USART1, RNG */
	hardware_setup();
	USB_OTG_BSP_HS_Init();
	uint32_t i = 0;
	while (i++ < 0xffffff);

	/* Enter the ThreadX kernel. */
	tx_kernel_enter();
}

/* Define local variables and definitions. */
UX_SLAVE_CLASS_CDC_ACM* cdc;
TX_THREAD demo_thread;
UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_parameter;
UCHAR buffer[UX_DEMO_BUFFER_SIZE];

void tx_application_define(void* first_unused_memory)
{
	/* Initialize the free memory pointer. */
	CHAR* stack_pointer = (CHAR*)first_unused_memory;

	/* Initialize the RAM disk memory. */
	CHAR* memory_pointer = stack_pointer + UX_DEMO_STACK_SIZE;

	/* Initialize USBX Memory */
	UINT status = _ux_system_initialize(memory_pointer, UX_USBX_MEMORY_SIZE, UX_NULL, 0);
	if (status != UX_SUCCESS)
		return;

	ULONG device_framework_length_full_speed = sizeof(device_framework_full_speed);		// 93
	ULONG device_framework_length_high_speed = sizeof(device_framework_high_speed);		// 103
	ULONG string_framework_length = sizeof(string_framework);							// 47
	ULONG language_id_framework_length = sizeof(language_id_framework);					// 2

	/* The code below is required for installing the device portion of USBX.
	 * No call back for device status change in this example. */
	status = _ux_device_stack_initialize(device_framework_high_speed,
			device_framework_length_high_speed, device_framework_full_speed,
			device_framework_length_full_speed, string_framework, string_framework_length,
			language_id_framework, language_id_framework_length, UX_NULL);
	if (status != UX_SUCCESS)
		return;

	/* Set the parameters for callback when insertion/extraction of a CDC device. */
	cdc_parameter.ux_slave_class_cdc_acm_instance_activate = demo_cdc_instance_activate;
	cdc_parameter.ux_slave_class_cdc_acm_instance_deactivate = demo_cdc_instance_deactivate;

	/* Initialize the device cdc class. This class owns both interfaces starting with 0. */
	status = _ux_device_stack_class_register(_ux_system_slave_class_cdc_acm_name,
			_ux_device_class_cdc_acm_entry, 1, 0, (VOID*)&cdc_parameter);
	if (status != UX_SUCCESS)
		return;

	/* Create the main demo thread. */
	status = _tx_thread_create(&demo_thread, "tx demo", demo_thread_entry, 0, stack_pointer,
	UX_DEMO_STACK_SIZE, 20, 20, 1, TX_AUTO_START);
	if (status != TX_SUCCESS)
		return;

	return;
}

void demo_thread_entry(ULONG arg)
{
//	/* Initialize the bsp layer of the USB OTG HS Controller. */
//	USB_OTG_BSP_HS_Init();
//	//	_hardware_setup();
//
//	_tx_thread_sleep(20);

	/* Register the STM32  USB device controllers available in this system */
	ULONG status = _ux_dcd_stm32_initialize(UX_DCD_STM32_OTG_FS_HIGH_SPEED, 0);
//	ULONG status = _ux_dcd_stm32_initialize(UX_DCD_STM32_OTG_FS_FULL_SPEED, 0);
	if (status != UX_SUCCESS)
		return;

	_tx_thread_sleep(30);

	ULONG actual_length;
	ULONG requested_length;

	for (;;)
	{
		// GPIOI->BSRR |= ((GPIOI->ODR & 0x02) != 0x00u) ? GPIO_BSRR_BR_1 : GPIO_BSRR_BS_1;
//		GreenLed_Toggle();

		/* Ensure the CDC class is mounted. */
		if (cdc != UX_NULL)
		{
//			/* Read from the CDC class. */
//			status = _ux_device_class_cdc_acm_read(cdc, buffer, UX_DEMO_BUFFER_SIZE,
//					&actual_length);
//
//			/* The actual length becomes the requested length. */
//			requested_length = actual_length;
//
//			/* Check the status.  If OK, we will write to the CDC instance. */
//			status = _ux_device_class_cdc_acm_write(cdc, buffer, requested_length, &actual_length);
//
//			/* Check for CR/LF. */
//			if (buffer[requested_length - 1] == '\r')
//			{
//				/* Copy LF value into user buffer. */
//				_ux_utility_memory_copy(buffer, "\n", 1);
//
//				/* And send it again. */
//				status = _ux_device_class_cdc_acm_write(cdc, buffer, 1, &actual_length);
//			}

			/* Fill buffer. */
			buffer[0] = 'a';
			buffer[1] = 'b';
			buffer[2] = 'c';
			buffer[3] = 'd';
			buffer[4] = 'e';
			buffer[5] = 'f';
			buffer[6] = '\r';
			buffer[7] = '\n';

			/* And send 8 bytes. */
			status = _ux_device_class_cdc_acm_write(cdc, buffer, 8, &actual_length);

			/* And send 0 byte packet. Forced ZLP. */
			status = _ux_device_class_cdc_acm_write(cdc, buffer, 0, &actual_length);
		}

		_tx_thread_sleep(50);
	}
}

/*static void Mb_usbfs_rcv_task(ULONG ptr)
 {
 UINT              res;
 ULONG             actual_length;
 ULONG             actual_flags;
 T_usbfs_drv_cbl * p = (T_usbfs_drv_cbl *)ptr;
 uint32_t          n;

 do
 {
 if (p->active)
 {
 n = p->head_n;
 res = ux_device_class_cdc_acm_read(p->cdc, p->rd_pack[n].buff,USBDRV_BUFFER_MAX_LENGTH,  &actual_length); // Чтение пакета из USB
 p->rd_pack[n].len = actual_length;
 if (res == UX_SUCCESS)
 {
 // Перемещаем указатель головы очереди
 n++; 
 if (n >= IN_BUF_QUANTITY) n = 0;
 p->head_n = n;

 // Выставляем флаг выполненного чтения
 if (tx_event_flags_set(&(p->evt), MB_USBFS_READ_DONE, TX_OR) != TX_SUCCESS)
 {
 tx_thread_sleep(2); // Задержка после ошибки 
 }

 // Если все буферы на прием заполнены, то значит системе не требуются данные
 if (p->tail_n == n)
 {
 // Перестаем принимать данные из USB и ждем когда система обработает уже принятые данные и подаст сигнал к началу приема по USB
 p->no_space = 1;
 if (tx_event_flags_get(&(p->evt), MB_USBFS_READ_REQUEST, TX_AND_CLEAR,&actual_flags, TX_WAIT_FOREVER) != TX_SUCCESS)
 {
 tx_thread_sleep(2); // Задержка после ошибки 
 }
 }
 }
 else
 {
 tx_thread_sleep(2); // Задержка после ошибки
 }
 }
 else
 {
 tx_thread_sleep(2); // Задержки после ошибки нужны для того чтобы задача не захватила все ресурсы в случает постоянного появления ошибки
 }

 } while (1);
 }*/

void demo_cdc_instance_activate(void* cdc_instance)
{
	/* этот callback вызывается внутри функции:
	 * 		UINT _ux_device_class_cdc_acm_activate(UX_SLAVE_CLASS_COMMAND* command);	(1)
	 * а эта функция вызывается внутри такой задачи-функции:
	 * 		UINT _ux_device_class_cdc_acm_entry(UX_SLAVE_CLASS_COMMAND* command);		(2)
	 * внутри обработки случая:
	 * 		case UX_SLAVE_CLASS_COMMAND_ACTIVATE:										(3)
	 * когда хост отправляет команду 'SET_CONFIGURATION' и интерфейс смонтирован (см. там)
	 */
	/* Save the CDC instance. */
	cdc = (UX_SLAVE_CLASS_CDC_ACM*)cdc_instance;
}

void demo_cdc_instance_deactivate(void* cdc_instance)
{
	/* Reset the CDC instance. */
//	cdc = UX_NULL;
}

/** эта ф. повторяет ф. HAL_PCD_MspInit(..) из 'usbd_conf.c' */
void USB_OTG_BSP_HS_Init(void)
{
	/* Configure USB FS GPIOs */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	/* USB_OTG_HS GPIO Configuration:
	 * PA5     ------> USB_OTG_HS_ULPI_CK
	 * PA3     ------> USB_OTG_HS_ULPI_D0
	 * PB0     ------> USB_OTG_HS_ULPI_D1
	 * PB1     ------> USB_OTG_HS_ULPI_D2
	 * PB10    ------> USB_OTG_HS_ULPI_D3
	 * PB11    ------> USB_OTG_HS_ULPI_D4
	 * PB12    ------> USB_OTG_HS_ULPI_D5
	 * PB13    ------> USB_OTG_HS_ULPI_D6
	 * PB5     ------> USB_OTG_HS_ULPI_D7
	 * PC0     ------> USB_OTG_HS_ULPI_STP
	 * PH4     ------> USB_OTG_HS_ULPI_NXT
	 * PC2     ------> USB_OTG_HS_ULPI_DIR
	 */
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

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
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_11 |
	GPIO_PIN_12 | GPIO_PIN_13;
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
	HAL_NVIC_SetPriority(OTG_HS_IRQn, 4, 0);		// (OTG_HS_IRQn, 0, 0)

	/* Enable USB HS Interrupt */
	HAL_NVIC_EnableIRQ(OTG_HS_IRQn);

//	/* Set USBHS Interrupt to the lowest priority */
//	HAL_NVIC_SetPriority(OTG_FS_IRQn, 4, 0);		// (OTG_HS_IRQn, 0, 0)
//
//	/* Enable USB HS Interrupt */
//	HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
}

/*------------------------------------------------------------------------------------------------*/

/* Definition of STM32 registers. */
#define STM32_RCC                           0x40021000
#define STM32_RCC_CR                        (*(volatile unsigned long*)(STM32_RCC + 0x00000000))
#define STM32_RCC_CR_HSEON                  0x00010000
#define STM32_RCC_CR_HSERDY                 0x00020000
#define STM32_RCC_CR_HSEBYP                 0x00040000
#define STM32_RCC_CR_PLL2RDY                0x08000000
#define STM32_RCC_CR_PLLRDY                 0x02000000
#define STM32_RCC_CFGR                      (*(volatile unsigned long*)(STM32_RCC + 0x00000004))
#define STM32_RCC_CFGR_HPRE                 0x000000F0
#define STM32_RCC_CFGR_SYSCLK_DIV1          0x00000000
#define STM32_RCC_CFGR_HCLK_DIV1            0x00000000
#define STM32_RCC_CFGR_HCLK_DIV2            0x00000400
#define STM32_RCC_CFGR_HCLK_MASK            0x00003800
#define STM32_RCC_CFGR_PCLK1_MASK           0x00000700
#define STM32_RCC_CFGR_PLL_MASK             0x003F0000
#define STM32_RCC_CFGR_SW_MASK              0x00000003
#define STM32_RCC_CFGR_SWS_MASK             0x0000000C
#define STM32_RCC_CFGR_SYSCLK_PLLCLK        0x00000002
#define STM32_RCC_CFGR_SYSCLK_PLLCLK_STAT   0x00000008
#define STM32_RCC_CIR                       (*(volatile unsigned long*)(STM32_RCC + 0x00000008))

#define STM32_RCC_AHBENR                    (*(volatile unsigned long*)(STM32_RCC + 0x00000014))
#define STM32_RCC_AHBENR_OTGFSEN            0x00001000

#define STM32_RCC_CFGR2                     (*(volatile unsigned long*)(STM32_RCC + 0x0000002C))
#define STM32_RCC_CFGR2_PREDIV1             0x0000000F
#define STM32_RCC_CFGR2_PREDIV1_DIV5        0x00000004
#define STM32_RCC_CFGR2_PREDIV1_SRC         0x00010000
#define STM32_RCC_CFGR2_PREDIV2             0x000000F0
#define STM32_RCC_CFGR2_PREDIV2_DIV5        0x00000040
#define STM32_RCC_CFGR2_PLL2MUL             0x00000F00
#define STM32_RCC_CFGR2_PLL2MUL_MASK        0xFFC2FFFF
#define STM32_RCC_CFGR2_PLL2MUL_8           0x00000600
#define STM32_RCC_CFGR2_PLLMULL_9           0x001C0000

#define STM32_FLASH                         0x40022000
#define STM32_FLASH_ACR                     (*(volatile unsigned long*)(STM32_FLASH + 0x00000000))
#define STM32_FLASH_ACR_PREFETCH_ENABLE     0x00000010
#define STM32_FLASH_ACR_LATENCY_MASK        0x00000038
#define STM32_FLASH_ACR_LATENCY_2           0x00000002

#define STM32_BB_BASE                       0x42420000
#define STM32_PLL2                          (*(volatile unsigned long*)(STM32_BB_BASE + 0x00000068))
#define STM32_PLL                           (*(volatile unsigned long*)(STM32_BB_BASE + 0x00000060))

#define STM32CFGR_OTGFSPRE_BB               0x424200D8

VOID _hardware_setup(void)
{
	/* Reset the STM32 board. */
	STM32_RCC_CR |= 0x00000001;
	STM32_RCC_CFGR &= 0xf0ff0000;
	STM32_RCC_CR &= 0xfef6ffff;
	STM32_RCC_CR &= 0xffbfffff;
	STM32_RCC_CFGR &= 0xff80ffff;
	STM32_RCC_CR &= 0xebffffff;
	STM32_RCC_CIR = 0x00ff0000;
	STM32_RCC_CFGR2 = 0;

	/* Set the RCC_CR register. Enable HSE. */
	STM32_RCC_CR &= ~STM32_RCC_CR_HSEON;
	STM32_RCC_CR &= ~STM32_RCC_CR_HSEBYP;
	STM32_RCC_CR |= STM32_RCC_CR_HSEON;

	/* Wait for HSE to be ready. */
	while ((STM32_RCC_CR & STM32_RCC_CR_HSERDY) == 0);

	/* Enable prefetch buffer. */
	STM32_FLASH_ACR |= STM32_FLASH_ACR_PREFETCH_ENABLE;

	/* Flash 2 wait state latency. */
	STM32_FLASH_ACR &= STM32_FLASH_ACR_LATENCY_MASK;
	STM32_FLASH_ACR |= STM32_FLASH_ACR_LATENCY_2;

	/* Set the Clock to SYSCLK Divisor 1. */
	STM32_RCC_CFGR &= ~STM32_RCC_CFGR_HPRE;
	STM32_RCC_CFGR |= STM32_RCC_CFGR_SYSCLK_DIV1;

	/* Set the PCLK2 to HCLK Divisor 1. */
	STM32_RCC_CFGR &= ~STM32_RCC_CFGR_HCLK_MASK;
	STM32_RCC_CFGR |= STM32_RCC_CFGR_HCLK_DIV1;

	/* Set the PCLK1 to HCLK Divisor 2. */
	STM32_RCC_CFGR &= ~STM32_RCC_CFGR_PCLK1_MASK;
	STM32_RCC_CFGR |= STM32_RCC_CFGR_HCLK_DIV2;

	/* Set the PREDIV2 register to Div 5. */
	STM32_RCC_CFGR2 &= ~STM32_RCC_CFGR2_PREDIV2;
	STM32_RCC_CFGR2 |= STM32_RCC_CFGR2_PREDIV2_DIV5;

	/* Set the PLLMUL register to 8. */
	STM32_RCC_CFGR2 &= ~STM32_RCC_CFGR2_PLL2MUL;
	STM32_RCC_CFGR2 |= STM32_RCC_CFGR2_PLL2MUL_8;

	/* Enable PLL2. */
	STM32_PLL2 = 1;

	/* Wait for PLL2 to be ready. */
	while ((STM32_RCC_CR & STM32_RCC_CR_PLL2RDY) == 0);

	/* Set the PREDIV1 register to Div 5. */
	STM32_RCC_CFGR2 &= ~(STM32_RCC_CFGR2_PREDIV1 | STM32_RCC_CFGR2_PREDIV1_SRC);
	STM32_RCC_CFGR2 |= STM32_RCC_CFGR2_PREDIV1_DIV5 | STM32_RCC_CFGR2_PREDIV1_SRC;

	/* Set the PLLMUL register to 9. */
	STM32_RCC_CFGR &= STM32_RCC_CFGR2_PLL2MUL_MASK;
	STM32_RCC_CFGR |= STM32_RCC_CFGR2_PLLMULL_9 | STM32_RCC_CFGR2_PREDIV1_SRC;

	/* Enable PLL. */
	STM32_PLL = 1;

	/* Wait for PLL to be ready. */
	while ((STM32_RCC_CR & STM32_RCC_CR_PLLRDY) == 0);

	/* Select PLL as system clock source. */
	STM32_RCC_CFGR &= ~STM32_RCC_CFGR_SW_MASK;
	STM32_RCC_CFGR |= STM32_RCC_CFGR_SYSCLK_PLLCLK;

	/* Wait till PLL is used as system clock source. */
	while ((STM32_RCC_CFGR & STM32_RCC_CFGR_SYSCLK_PLLCLK_STAT) == 0);

	/* Select USBCLK source.*/
	STM32_PLL = 0;

	/* Enable the USB clock. */
	STM32_RCC_AHBENR |= STM32_RCC_AHBENR_OTGFSEN;
}
