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
/*  FUNCTION                                              RELEASE         */
/*                                                                        */
/*    _ux_dcd_stm32_address_set                          PORTABLE C       */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will set the address of the device after we have      */
/*    received a SET_ADDRESS command from the host.                       */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    dcd_stm32                             Pointer to device controller  */
/*    address                               Address to set                */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
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
UINT _ux_dcd_stm32_address_set(UX_DCD_STM32* dcd_stm32, ULONG address)
{
    /* Clear the previous address. */
    _ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_DCFG,
            UX_DCD_STM32_OTG_FS_DCFG_DAD_MASK);

    /* Store the new address of the device. */
    _ux_dcd_stm32_register_set(dcd_stm32, UX_DCD_STM32_OTG_FS_DCFG,
            address << UX_DCD_STM32_OTG_FS_DCFG_DAD_SHIFT);

    /* This function always succeeds. */
    return (UX_SUCCESS);
}
