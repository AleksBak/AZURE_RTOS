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


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_hcd_stm32.h"
#include "ux_host_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_port_reset                            PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function will reset a specific port attached to the root       */ 
/*    HUB.                                                                */ 
/*                                                                        */
/*    Note since ThreadX delay is used, the function must not be used in  */
/*    interrupts.                                                         */
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                             Pointer to STM32 controller   */ 
/*    port_index                            Port index                    */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_hcor_register_read      Read STM32 register           */ 
/*    _ux_hcd_stm32_hcor_register_write     Write STM32 register          */ 
/*    _ux_utility_delay_ms                  Delay                         */ 
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
UINT  _ux_hcd_stm32_port_reset(UX_HCD_STM32 *hcd_stm32, ULONG port_index)
{
ULONG    stm32_register;
ULONG    port_enable_timeout;
ULONG   port_reset_loop;

    /* Check to see if this port is valid on this controller.  On STM32, there is only one. */
    if (port_index != 0)
    {

        /* Error trap. */
        _ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD, UX_SYSTEM_CONTEXT_HCD, UX_PORT_INDEX_UNKNOWN);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_PORT_INDEX_UNKNOWN, port_index, 0, 0, UX_TRACE_ERRORS, 0, 0)

        return(UX_PORT_INDEX_UNKNOWN);
    }
    
    /* Ensure that the downstream port has a device attached. It is unnatural
       to perform a port reset if there is no device.  */
    if ((hcd_stm32 -> ux_hcd_stm32_controller_flag & UX_HCD_STM32_CONTROLLER_FLAG_DEVICE_ATTACHED) == 0)
    {
    
        /* Error trap. */
        _ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD, UX_SYSTEM_CONTEXT_HCD, UX_NO_DEVICE_CONNECTED);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_NO_DEVICE_CONNECTED, port_index, 0, 0, UX_TRACE_ERRORS, 0, 0)

        return(UX_NO_DEVICE_CONNECTED);
    }
    
    /* Reset the Port Reset loop.  */
    port_reset_loop =  0;

    /* Perform the reset 3 times.  */
    while (port_reset_loop++ < 3)
    {
    
        /* Arm the Reset signal.  */
        _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT, UX_HCD_STM32_OTG_FS_HPRT_PRST);    
    
        /* Perform the necessary delay for resetting the port.  More than 10ms.  */
        _ux_utility_delay_ms(50);
    
        /* Complete the Reset signal.  */
        _ux_hcd_stm32_register_clear(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT, UX_HCD_STM32_OTG_FS_HPRT_PRST);    

        /* Reset the Port Enabled timeout.  */
        port_enable_timeout =  0;

        /* Wait for the port to be enabled.  */
        while (port_enable_timeout < UX_HCD_STM32_PORT_ENABLE_TIMEOUT)
        {
    
            /* Read the port status.  */
            stm32_register = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT);
            
            /* Is it enabled ? */
            if (stm32_register & UX_HCD_STM32_OTG_FS_HPRT_PENA)
            {


                /* Read the port register.  Isolating speed. */
                stm32_register = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HPRT) & UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_MASK;
                
                /* Check the speed.  */
                switch (stm32_register)
                {
                
                    case UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_LS :
                
                        /* Device is low speed.  */
                        hcd_stm32 -> ux_hcd_stm32_controller_flag |= UX_HCD_STM32_CONTROLLER_LOW_SPEED_DEVICE;
            
                        break;

                    case UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_FS :
                
                        /* Device is full speed.  */
                        hcd_stm32 -> ux_hcd_stm32_controller_flag |= UX_HCD_STM32_CONTROLLER_FULL_SPEED_DEVICE;
            
                        break;

                    case UX_HCD_STM32_OTG_FS_HPRT_PSPD_SPEED_HS :
                
                        /* Device is high speed.  */
                        hcd_stm32 -> ux_hcd_stm32_controller_flag |= UX_HCD_STM32_CONTROLLER_HIGH_SPEED_DEVICE;
            
                        break;

                }

                /* Perform the necessary delay before sending the first control command. Between 10ms and 20ms.  */
                _ux_utility_delay_ms(UX_HCD_STM32_PORT_RESET_DELAY);
            
                /* This function should never fail.  */
                return(UX_SUCCESS);

            }            
    
            /* We need to wait a bit.  */
            _ux_utility_delay_ms(1);
            
            /* Increment the timeout count.  */
            port_enable_timeout++;
    
        }                        
    }

       /* Port reset failed.  */
    return(UX_PORT_RESET_FAILED);
    
    
}

