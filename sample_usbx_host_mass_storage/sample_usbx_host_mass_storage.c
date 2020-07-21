/**************************************************************************/
/**                                                                       */
/** USBX Host Mass Storage Example for STM32F746-DISCO Board              */
/**                                                                       */
/** This example illustrates USBX working on a STM32F7xx processor        */
/**                                                                       */
/** This demo will show the host side of USBX. A USB flash drive can be   */
/** mounted and this demo will cycle through the directory entries,       */
/** reading the contents of any file in the root directory.               */
/**                                                                       */
/**************************************************************************/

/* Include necessary system files.  */

#include "fx_api.h"
#include "ux_api.h"
#include "ux_system.h"
#include "ux_utility.h"
#include "ux_hcd_stm32.h"
#include "ux_host_class_hub.h"
#include "ux_host_class_storage.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

/* Define constants.  */

#define USBX_MEMORY_SIZE            (64 * 1024)
#define DEMO_STACK_SIZE             (2 * 1024)
#define DEMO_BUFFER_SIZE            1024

#define HOST_POWERSW_PORT           GPIOH
#define HOST_POWERSW_VBUS           GPIO_Pin_5

/*------------------------------- Define local function prototypes -------------------------------*/

void demo_thread_entry(ULONG arg);
UINT demo_class_storage_get(void);

void USB_OTG_BSP_HS_Init(void);
void demo_read_file();
VOID hardware_setup(void);

/*-------------------------------- Define global data structures. --------------------------------*/

TX_THREAD tx_demo_thread;
UX_HOST_CLASS* class_driver;
ULONG class_driver_index;
UX_HOST_CLASS_STORAGE* storage;
UX_HOST_CLASS_STORAGE_MEDIA* storage_media;
FX_MEDIA* media;
UINT status;

UINT transfer_completed;
ULONG requested_length;
FX_FILE my_file;
TX_SEMAPHORE tx_demo_semaphore;

CHAR file_name[64];
UCHAR local_buffer[1024];
UCHAR storage_buffer[DEMO_BUFFER_SIZE];

/*--------------------------------------------- main ---------------------------------------------*/

int main(int argc, char** argv)
{
	/* Setup the hardware. */
	hardware_setup();

	/* Enter the ThreadX kernel.
	 * 1. _tx_initialize_low_level();
	 * 2. tx_application_define(_tx_initialize_unused_memory); (see below)
	 * 3. _tx_thread_schedule(); */
	tx_kernel_enter();
}

/*-------------------------- Define what the initial system looks like. --------------------------*/

void tx_application_define(void* first_unused_memory)
{
	/* Initialize the bsp layer of the USB OTG HS Controller.  */
	USB_OTG_BSP_HS_Init();

	/* Initialize the free memory pointer */
	CHAR* stack_pointer = (CHAR*)first_unused_memory;
	CHAR* memory_pointer = stack_pointer + DEMO_STACK_SIZE;

	/* Initialize FileX.  */
	fx_system_initialize();

	/* Initialize USBX memory. */
	ux_system_initialize(memory_pointer, USBX_MEMORY_SIZE, UX_NULL, 0);

	/* Create the main demo thread: thread_ptr, name_ptr, entry_function, entry_input, stack_start,
	 * stack_size, priority, preempt_threshold, time_slice, auto_start */
	tx_thread_create(&tx_demo_thread, "tx demo", demo_thread_entry, 0, stack_pointer,
			DEMO_STACK_SIZE, 30, 30, 1, TX_AUTO_START);
}

void demo_thread_entry(ULONG arg)
{
	/* The code below is required for installing the host portion of USBX.  */
	status = ux_host_stack_initialize(UX_NULL);
	if (status != UX_SUCCESS)
		return;

	/* Register the HUB class.  */
	status = ux_host_stack_class_register(_ux_system_host_class_hub_name, _ux_host_class_hub_entry);
	if (status != UX_SUCCESS)
		return;

	/* Register storage class.  */
	status = ux_host_stack_class_register(_ux_system_host_class_storage_name,
			_ux_host_class_storage_entry);
	if (status != UX_SUCCESS)
		return;

	/* Register all the USB host controllers available in this system.  */
	status = ux_host_stack_hcd_register(_ux_system_host_hcd_stm32_name,
			_ux_hcd_stm32_initialize_hscore, 0x40040000, 0x0);
	if (status != UX_SUCCESS)
		return;

	for (;;)
	{
		/* Find the storage class. */
		status = demo_class_storage_get();

		if (status != UX_SUCCESS)
			continue;

		/* Find first file on media.  */
		status = fx_directory_first_entry_find(media, file_name);

		if (status != UX_SUCCESS)
			continue;

		demo_read_file();

		tx_thread_sleep(10);
	}
}

void demo_read_file()
{
	ULONG files_count = 0;
	FX_FILE my_file;
	ULONG requested_length;
	UINT file_attribute;
	ULONG error_count = 0;

	/* We come here if there is at least a file in the directory.   */
	do
	{
		/* Increment file count.  */
		files_count++;

		/* Reset file attributes.  */
		file_attribute = 0;

		/* Try to read the file attributes.  */
		status = fx_file_attributes_read(media, file_name, &file_attribute);

		/* If this is a directory, pass.  */
		if (!(file_attribute & 0x18) && (status == UX_SUCCESS))
		{
			/* Try to open the file.  */
			status = fx_file_open(media, &my_file, file_name, FX_OPEN_FOR_READ);
			if (status != UX_SUCCESS)
				break;

			/* Read the entire file.  */
			while (status == UX_SUCCESS)
			{
				/* Read the file in blocks */
				status = fx_file_read(&my_file, local_buffer, 1024, &requested_length);

				/* Check if status OK.  */
				if (status != UX_SUCCESS)
				{
					error_count++;
					break;
				}

				/* Check if end of file.  */
				if (requested_length != 1024)
					break;
			}

			/* Finished reading file either at the end or because of error. */
			fx_file_close(&my_file);
		}

		/* Ask FileX to find another file.  */
		status = fx_directory_next_entry_find(media, file_name);

	} while (status == UX_SUCCESS);

	/* We get here we have exhausted all the files in the root directory. */
	return;
}

UINT demo_class_storage_get(void)
{
	UX_HOST_CLASS* class;

	/* Find the main storage container */
	status = ux_host_stack_class_get(_ux_system_host_class_storage_name, &class);
	if (status != UX_SUCCESS)
		return (status);

	/* We still need to wait for the storage status to be live */
	do
	{
		/* We get the first instance of the storage device */
		do
		{
			status = ux_host_stack_class_instance_get(class, 0, (void**)&storage);
			tx_thread_sleep(10);
		} while (status != UX_SUCCESS);

		tx_thread_sleep(10);

	} while (storage->ux_host_class_storage_state != UX_HOST_CLASS_INSTANCE_LIVE);

	/* We try to get the first media attached to the class container.  */
	while (class->ux_host_class_media == UX_NULL)
	{
		tx_thread_sleep(10);
	}

	/* Setup media pointer.  */
	storage_media = (UX_HOST_CLASS_STORAGE_MEDIA*)class->ux_host_class_media;
	media = &storage_media->ux_host_class_storage_media;

	return (UX_SUCCESS);
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
	HAL_NVIC_SetPriority(OTG_HS_IRQn, 3, 0);

	/* Enable USBHS Interrupt */
	HAL_NVIC_EnableIRQ(OTG_HS_IRQn);
}
