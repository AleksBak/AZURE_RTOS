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
#include "ux_utility.h"
#include "ux_device_stack.h"

/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                RELEASE       */
/*                                                                        */
/*    _ux_dcd_stm32_fifo_write                             PORTABLE C     */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will write to the FIFO of a particular endpoint.      */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_stm32                             Pointer to device controller  */
/*    endpoint_index                        Endpoint index                */
/*    fifo_buffer                           Pointer to transfer buffer    */
/*    fifo_length                           Length to write               */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_short_get                 Get short word                */ 
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
UINT  _ux_dcd_stm32_fifo_write(UX_DCD_STM32 *dcd_stm32, ULONG endpoint_index,
                                     UCHAR * data_pointer, ULONG fifo_length, ULONG last_packet_flag)
{

TX_INTERRUPT_SAVE_AREA
ULONG    fifo_address;
ULONG    fifo_value;

    /* Calculate the address of the FIFO.  */
    fifo_address = UX_DCD_STM32_DATA_FIFO_OFFSET + (endpoint_index * UX_DCD_STM32_DATA_FIFO_SIZE);

    /* Number of bytes to read is based on DWORDS.  */
    fifo_length = (fifo_length + 3) / sizeof(ULONG);
    
    /* Lockout interrupts.  */
    TX_DISABLE

    /* Write one DWORD at a time.  */
    while (fifo_length--)
    {

        /* load the value from the FIFO. This is little/endian agnostic.  */
        fifo_value = _ux_utility_long_get(data_pointer);

        /* Write from FIFO.  */
        _ux_dcd_stm32_register_write(dcd_stm32, fifo_address, fifo_value);

        /* Increment the data pointer buffer address.  */
        data_pointer += sizeof(ULONG);

    }

    /* Restore interrupts.  */
    TX_RESTORE

    /* Return successful completion.  */
    return(UX_SUCCESS);        
}

