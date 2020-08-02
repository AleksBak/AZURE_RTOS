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
/*    _ux_dcd_stm32_fifo_flush                             PORTABLE C     */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will flush a selective or all TX Fifo or all RX fifos.*/
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_stm32                             Pointer to device controller  */
/*    fifo type                             FIFO type (TX or RX)          */
/*    fifo_index                            Fifo index for TX             */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
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
UINT  _ux_dcd_stm32_fifo_flush(UX_DCD_STM32 *dcd_stm32, ULONG fifo_type, ULONG fifo_index)
{
ULONG    stm32_register;

    /* Check if this is for RX or TX Fifos.  */
    if (fifo_type == UX_DCD_STM32_FLUSH_RX_FIFO)

        /* Set the RXFFLSH bit.  */
        _ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GRSTCTL, 
                                    UX_DCD_STM32_OTG_FS_GRSTCTL_RXFFLSH);
    else

        /* Set the Fifo number and the TXFFLSH bit.  */
        _ux_dcd_stm32_register_write(dcd_stm32, UX_DCD_STM32_OTG_FS_GRSTCTL, 
                                    (UX_DCD_STM32_OTG_FS_GRSTCTL_TXFFLSH | 
                                    (fifo_index << UX_DCD_STM32_OTG_FS_GRSTCTL_TXFNUM_SHIFT)));

    /* Wait for the FIFO to be flushed.  */
    do
    {
        /* Read the GRSTCTL register.  */
        stm32_register = _ux_dcd_stm32_register_read(dcd_stm32, UX_DCD_STM32_OTG_FS_GRSTCTL);

    } while (stm32_register & fifo_type);

    /* Spec says to wait for 3 PHY Clocks.  */
    _ux_dcd_stm32_delay(3);    

    return(UX_SUCCESS);        
}

