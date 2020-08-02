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
/*    _ux_dcd_stm32_endpoint_destroy                        PORTABLE C    */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function will destroy a physical endpoint.                     */
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
/*    _ux_dcd_stm32_register_read           Read register                 */ 
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
UINT  _ux_dcd_stm32_endpoint_destroy(UX_DCD_STM32 *dcd_stm32, UX_SLAVE_ENDPOINT *endpoint)
{

UX_DCD_STM32_ED     *ed;
ULONG               stm32_endpoint_address;

    /* Keep the physical endpoint address in the endpoint container.  */
    ed =  (UX_DCD_STM32_ED *) endpoint -> ux_slave_endpoint_ed;

    /* Set the endpoint direction.  */
    if ((endpoint -> ux_slave_endpoint_descriptor.bEndpointAddress & UX_ENDPOINT_DIRECTION) == UX_ENDPOINT_IN)
    {

        /* Clear the DAINTMSK field for endpoint IN.  */
        _ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK, 1 << ed -> ux_dcd_stm32_ed_index);
        
    }            
    else
    {
    
        /* Clear the DAINTMSK field for endpoint OUT.  */
        _ux_dcd_stm32_register_clear(dcd_stm32, UX_DCD_STM32_OTG_FS_DAINTMSK, 0x1000 << ed -> ux_dcd_stm32_ed_index);
    }

    /* Get the endpoint address.  */
    stm32_endpoint_address = _ux_dcd_stm32_endpoint_register_address_get(ed);

    /* Clear the endpoint register at the EP address.  */
    _ux_dcd_stm32_register_write(dcd_stm32, stm32_endpoint_address, 0);

    /* We can free this endpoint.  */
    ed -> ux_dcd_stm32_ed_status =  UX_DCD_STM32_ED_STATUS_UNUSED;

    /* This function never fails.  */
    return(UX_SUCCESS);         
}

