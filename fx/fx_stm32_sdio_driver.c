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
/** FileX Component                                                       */ 
/**                                                                       */
/**   STM32 SDIO Driver                                                   */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

 

/* Include necessary system files.  */

#include "stm32f7xx.h"
#include "stm32746g_discovery_sd.h"
#include "tx_api.h"
#include "fx_api.h"


/* Define semaphore for media transfer.  */
static TX_SEMAPHORE semaphore_transfer;

VOID  _fx_stm32_sdio_driver(FX_MEDIA *media_ptr);
static void wait_DMA_read_complete();
static void wait_DMA_write_complete();
static void wait_transfer_ok();

UINT  _fx_partition_offset_calculate(void  *partition_sector, UINT partition,
                                     ULONG *partition_start, ULONG *partition_size);
extern SD_HandleTypeDef uSdHandle;
/**
  * @brief  This function handles DMA2 Stream 3 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Stream3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(uSdHandle.hdmarx);
}

/**
  * @brief  This function handles DMA2 Stream 6 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Stream6_IRQHandler(void)
{
   HAL_DMA_IRQHandler(uSdHandle.hdmatx); 
}

/**
  * @brief  This function handles SDIO interrupt request.
  * @param  None
  * @retval None
  */
void SDIO_IRQHandler(void)
{
   HAL_SD_IRQHandler(&uSdHandle);
}

void BSP_SD_WriteCpltCallback(void)
{
    
    /* Put semaphore for transfer completion.  */
    tx_semaphore_put(&semaphore_transfer);
}

/**
  * @brief BSP Rx Transfer completed callbacks
  * @param None
  * @retval None
  */
void BSP_SD_ReadCpltCallback(void)
{

    /* Put semaphore for transfer completion.  */
    tx_semaphore_put(&semaphore_transfer);
}


static void wait_DMA_read_complete()
{

    /* Wait for Rx Transfer completion */
    tx_semaphore_get(&semaphore_transfer,TX_WAIT_FOREVER);
}

static void wait_DMA_write_complete()
{

    /* Wait for Tx Transfer completion */
    tx_semaphore_get(&semaphore_transfer,TX_WAIT_FOREVER);
}
static void wait_transfer_ok()
{

    /* Wait until SD card is ready to use for new operation */
    while (BSP_SD_GetCardState() != SD_TRANSFER_OK)
    {
      ;
    }
}

/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _fx_stm32_sdio_driver                               PORTABLE C      */ 
/*                                                           6.0          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Yuxin Zhou, Microsoft Corporation                                   */  
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This function is the entry point to the STM32 SDIO disk driver.     */ 
/*    It relies on the STM32 peripheral library from ST.                  */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    media_ptr                             Media control block pointer   */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _fx_utility_memory_copy               Copy sector memory            */ 
/*    _fx_utility_16_unsigned_read          Read 16-bit unsigned          */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    FileX System Functions                                              */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */ 
/*                                                                        */ 
/**************************************************************************/ 
VOID  _fx_stm32_sdio_driver(FX_MEDIA *media_ptr)
{

UINT        status;
uint8_t     SDIO_Status;
ULONG       partition_start;
ULONG       partition_size;


    /* There are several useful/important pieces of information contained in the media
       structure, some of which are supplied by FileX and others are for the driver to
       setup. The following is a summary of the necessary FX_MEDIA structure members:
       
            FX_MEDIA Member                              Meaning
                                        
        fx_media_driver_request             FileX request type. Valid requests from FileX are 
                                            as follows:

                                                    FX_DRIVER_READ
                                                    FX_DRIVER_WRITE                 
                                                    FX_DRIVER_FLUSH
                                                    FX_DRIVER_ABORT
                                                    FX_DRIVER_INIT
                                                    FX_DRIVER_BOOT_READ
                                                    FX_DRIVER_RELEASE_SECTORS
                                                    FX_DRIVER_BOOT_WRITE
                                                    FX_DRIVER_UNINIT

        fx_media_driver_status              This value is RETURNED by the driver. If the 
                                            operation is successful, this field should be
                                            set to FX_SUCCESS for before returning. Otherwise,
                                            if an error occurred, this field should be set
                                            to FX_IO_ERROR. 

        fx_media_driver_buffer              Pointer to buffer to read or write sector data.
                                            This is supplied by FileX.

        fx_media_driver_logical_sector      Logical sector FileX is requesting.

        fx_media_driver_sectors             Number of sectors FileX is requesting.


       The following is a summary of the optional FX_MEDIA structure members:
       
            FX_MEDIA Member                              Meaning
                                        
        fx_media_driver_info                Pointer to any additional information or memory.
                                            This is optional for the driver use and is setup
                                            from the fx_media_open call. The RAM disk uses
                                            this pointer for the RAM disk memory itself.

        fx_media_driver_write_protect       The DRIVER sets this to FX_TRUE when media is write 
                                            protected. This is typically done in initialization, 
                                            but can be done anytime.

        fx_media_driver_free_sector_update  The DRIVER sets this to FX_TRUE when it needs to 
                                            know when clusters are released. This is important
                                            for FLASH wear-leveling drivers.

        fx_media_driver_system_write        FileX sets this flag to FX_TRUE if the sector being
                                            written is a system sector, e.g., a boot, FAT, or 
                                            directory sector. The driver may choose to use this
                                            to initiate error recovery logic for greater fault
                                            tolerance.

        fx_media_driver_data_sector_read    FileX sets this flag to FX_TRUE if the sector(s) being
                                            read are file data sectors, i.e., NOT system sectors.

        fx_media_driver_sector_type         FileX sets this variable to the specific type of 
                                            sector being read or written. The following sector
                                            types are identified:

                                                    FX_UNKNOWN_SECTOR 
                                                    FX_BOOT_SECTOR
                                                    FX_FAT_SECTOR
                                                    FX_DIRECTORY_SECTOR
                                                    FX_DATA_SECTOR  
    */

    /* Process the driver request specified in the media control block.  */
    switch(media_ptr -> fx_media_driver_request)
    {

        case FX_DRIVER_READ:
        {

            wait_transfer_ok();

            /*Invalidate cache before DMA read */
            SCB_CleanInvalidateDCache_by_Addr((uint32_t*)media_ptr -> fx_media_driver_buffer,media_ptr -> fx_media_driver_sectors*512);
            
            /* Use the STM32 SDIO library to ready one or more sectors.  */
            SDIO_Status = BSP_SD_ReadBlocks_DMA((uint32_t*)media_ptr -> fx_media_driver_buffer,                                       /* Destination buffer  */
                                                (media_ptr -> fx_media_driver_logical_sector + media_ptr -> fx_media_hidden_sectors), /* SD card address     */
                                                media_ptr -> fx_media_driver_sectors);                                                /* Number of sectors   */

            /* Check status of SDIO Read.  */
            if (SDIO_Status == MSD_OK)
            {
                wait_DMA_read_complete();

                /* Successful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            }
            else
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                break;
            }

            break;

        }
        
        case FX_DRIVER_WRITE:
        {

            wait_transfer_ok();
            
            /*Clean cache before DMA write */
            SCB_CleanDCache_by_Addr((uint32_t*)media_ptr -> fx_media_driver_buffer,media_ptr -> fx_media_driver_sectors*512);

            /* Use the STM32 SDIO library to write one or more sectors.  */
            SDIO_Status = BSP_SD_WriteBlocks_DMA((uint32_t*)media_ptr -> fx_media_driver_buffer,                                         /* Source buffer        */
                                                 ((media_ptr -> fx_media_driver_logical_sector + media_ptr -> fx_media_hidden_sectors)), /* SD card address      */ 
                                                 media_ptr -> fx_media_driver_sectors);                                                  /* Number of sectors   */

            /* Check status of SDIO Write.  */
            if (SDIO_Status == MSD_OK)
            {
                wait_DMA_write_complete();

                /* Successful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            }
            else
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                break;
            }

            break;
        }

        case FX_DRIVER_FLUSH:
        {

            /* Return driver success.  */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_ABORT:
        {

            /* Return driver success.  */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

    case FX_DRIVER_INIT:
        {

            /* FLASH drivers are responsible for setting several fields in the 
            media structure, as follows:
            
            media_ptr -> fx_media_driver_free_sector_update
            media_ptr -> fx_media_driver_write_protect
            
            The fx_media_driver_free_sector_update flag is used to instruct
            FileX to inform the driver whenever sectors are not being used.
            This is especially useful for FLASH managers so they don't have 
            maintain mapping for sectors no longer in use.
            
            The fx_media_driver_write_protect flag can be set anytime by the
            driver to indicate the media is not writable.  Write attempts made
            when this flag is set are returned as errors.  */
            
            /* Perform basic initialization here... since the boot record is going
            to be read subsequently and again for volume name requests.  */
            
            if(tx_semaphore_create(&semaphore_transfer, "SD transfer semaphore", 0) != TX_SUCCESS)
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                break;
            }

            /* Enable SDIO clock and reset SDIO.  */
            __HAL_RCC_SDIO_CLK_ENABLE();
            __HAL_RCC_SDIO_FORCE_RESET();
            __HAL_RCC_SDIO_RELEASE_RESET();

            /* SDIO Initialize.  */
            SDIO_Status = BSP_SD_Init();

            /* Set DMA transfer complete interrupt priority.  */
            HAL_NVIC_SetPriority(SD_DMAx_Rx_IRQn, 0x0E, 0);
            HAL_NVIC_SetPriority(SD_DMAx_Tx_IRQn, 0x0E, 0);

            /* Check status of SDIO Initialize.  */
            if (SDIO_Status == MSD_OK)
            {

                /* Successful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            }
            else
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
            }

            break;
        }

        case FX_DRIVER_UNINIT:
        {

            /* There is nothing to do in this case for the RAM driver.  For actual
               devices some shutdown processing may be necessary.  */

            tx_semaphore_delete(&semaphore_transfer);

            /* Successful driver request.  */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_BOOT_READ:
        {

            wait_transfer_ok();

            /*Invalidate cache before DMA read */
            SCB_CleanInvalidateDCache_by_Addr((uint32_t*)media_ptr -> fx_media_driver_buffer,512);

            /* Read the boot record of 512 bytes.  */
            SDIO_Status = BSP_SD_ReadBlocks_DMA((uint32_t*)media_ptr -> fx_media_driver_buffer, 0, 1);

            /* Check status of SDIO Read.  */
            if (SDIO_Status != MSD_OK)
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                return;
            }

            /* Wait for Rx Transfer completion */
            wait_DMA_read_complete();

            /* Determine if we have the parition... */
            partition_start =  0;

            status =  _fx_partition_offset_calculate(media_ptr -> fx_media_driver_buffer, 0,
                                                     &partition_start, &partition_size);

            /* Check partition read error.  */
            if (status)
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                return;
            }

            /* Now determine if there is a partition...   */
            if (partition_start)
            {

                wait_transfer_ok();
                
                /*Invalidate cache before DMA read */
                SCB_CleanInvalidateDCache_by_Addr((uint32_t*)media_ptr -> fx_media_driver_buffer,512);

                /* Yes, now lets read the actual boot record.  */
                SDIO_Status = BSP_SD_ReadBlocks_DMA((uint32_t*)media_ptr -> fx_media_driver_buffer, partition_start, 1);

                /* Check status of SDIO Read.  */
                if (SDIO_Status != MSD_OK)
                {

                    /* Unsuccessful driver request.  */
                    media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                    return;
                }

                /* Wait for Rx Transfer completion */
                wait_DMA_read_complete();
            }

            /* Successful driver request.  */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_BOOT_WRITE:
        {

            wait_transfer_ok();

            /*Clean cache before DMA write */
            SCB_CleanDCache_by_Addr((uint32_t*)media_ptr -> fx_media_driver_buffer,512);
            /* Write the boot record.  */
            SDIO_Status = BSP_SD_WriteBlocks_DMA((uint32_t*)media_ptr -> fx_media_driver_buffer, (media_ptr -> fx_media_hidden_sectors),1);

            /* Check status of SDIO Write.  */
            if (SDIO_Status == MSD_OK)
            {
                wait_DMA_write_complete();

                /* Successful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            }
            else
            {

                /* Unsuccessful driver request.  */
                media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
                break;
            }

            break ;
        }

        default:
        {

            /* Invalid driver request.  */
            media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
            break;
        }
    }
}
