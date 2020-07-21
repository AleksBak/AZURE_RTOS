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
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _ux_dcd_stm32_endpoint_register_address_get         PORTABLE C      */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function returns the address of the endpoint register          */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    ed                                    Endpoint descriptor           */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Register address of endpoint.                                       */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    None                                                                */ 
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
ULONG  _ux_dcd_stm32_endpoint_register_address_get(UX_DCD_STM32_ED *ed)
{

    /* Check for endpoint 0.  */
    if (ed -> ux_dcd_stm32_ed_index == 0)
    
        /* Return the address of endpoint 0. */
        return(UX_DCD_STM32_OTG_FS_DOEPCTL);
    
    else
    {
                    
        /* Check the endpoint direction for the base.  */
        if (ed -> ux_dcd_stm32_ed_direction  == UX_ENDPOINT_IN)

            /* Endpoint is IN.  */
            return(UX_DCD_STM32_OTG_FS_DIEPCTL + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));

        else
        
            /* Endpoint is OUT.  */
            return(UX_DCD_STM32_OTG_FS_DOEPCTL + (ed -> ux_dcd_stm32_ed_index * UX_DCD_STM32_ENDPOINT_SPACE_SIZE));
    }
}

