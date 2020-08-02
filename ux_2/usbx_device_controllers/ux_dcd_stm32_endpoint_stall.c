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
#include "ux_device_stack.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                                 RELEASE      */
/*                                                                        */
/*    _ux_dcd_stm32_endpoint_stall                          PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will stall a physical endpoint.                       */
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
/*    _ux_dcd_stm32_register_set            Set register                  */ 
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
UINT  _ux_dcd_stm32_endpoint_stall(UX_DCD_STM32 *dcd_stm32, UX_SLAVE_ENDPOINT *endpoint)
{
                    
UX_DCD_STM32_ED     *ed;
ULONG               stm32_endpoint_register;
ULONG               stm32_endpoint_address;

    /* Get the physical endpoint address in the endpoint container.  */
    ed =  (UX_DCD_STM32_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Check the endpoint direction for the base.  */
    if (ed -> ux_dcd_stm32_ed_direction  == UX_ENDPOINT_IN)

        /* Endpoint is IN.  */
        stm32_endpoint_address = (UX_DCD_STM32_OTG_FS_DIEPCTL + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

    else
    
        /* Endpoint is OUT.  */
        stm32_endpoint_address = (UX_DCD_STM32_OTG_FS_DOEPCTL + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

    /* Read the current EP register.  */
       stm32_endpoint_register =  _ux_dcd_stm32_register_read(dcd_stm32, stm32_endpoint_address);

    /* Check the direction. Is the endpoint IN ? */
    if (ed -> ux_dcd_stm32_ed_direction == UX_ENDPOINT_IN)
    {
        
        /* Check if the endpoint is enabled.  */
        if (stm32_endpoint_register & UX_DCD_STM32_OTG_FS_DIEPCTL_EPENA)
        
            /* Disabled the endpoint.  */
            stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_EPDIS;

    }

    /* Set the stall bit.  */
    stm32_endpoint_register |= UX_DCD_STM32_OTG_FS_DIEPCTL_STALL;

    /* Write the endpoint register.  */
    _ux_dcd_stm32_register_write(dcd_stm32, stm32_endpoint_address, stm32_endpoint_register);
        
    /* Set the endpoint to stall.  */
    ed -> ux_dcd_stm32_ed_status |=  UX_DCD_STM32_ED_STATUS_STALLED;

    /* This function never fails.  */
    return(UX_SUCCESS);         
}

