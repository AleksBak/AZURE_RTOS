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
/**   Device Stack                                                        */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define UX_SOURCE_CODE


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_device_stack.h"


/**************************************************************************/
/*                                                                        */
/*    FUNCTION                                              RELEASE       */
/*                                                                        */
/*      _ux_device_stack_alternate_setting_get             PORTABLE C     */
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function gets the alternate setting for a specific interface.  */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    endpoint                              Pointer to endpoint           */
/*    interface_value                       Interface value               */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    Completion Status                                                   */ 
/*                                                                        */
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_device_stack_transfer_request     Process transfer request      */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Application                                                         */ 
/*    Device Stack                                                        */
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_device_stack_alternate_setting_get(ULONG interface_value)
{

UX_SLAVE_TRANSFER       *transfer_request;
UX_SLAVE_INTERFACE      *interface;
UX_SLAVE_DEVICE         *device;
UX_SLAVE_ENDPOINT       *endpoint;
UINT                    status;
                                
    /* If trace is enabled, insert this event into the trace buffer.  */
    UX_TRACE_IN_LINE_INSERT(UX_TRACE_DEVICE_STACK_ALTERNATE_SETTING_GET, interface_value, 0, 0, 0, UX_TRACE_DEVICE_STACK_EVENTS, 0, 0)

    /* Get the pointer to the device.  */
    device =  &_ux_system_slave -> ux_system_slave_device;

    /* If the device was in the configured state, there may be interfaces
       attached to the configuration.  */
    if (device -> ux_slave_device_state == UX_DEVICE_CONFIGURED)
    {

        /* Obtain the pointer to the first interface attached.  */
        interface =  device -> ux_slave_device_first_interface;

        /* Start parsing each interface.  */
        while (interface != UX_NULL)
        {

            /* Check if this is the interface we have an inquiry for.  */
            if (interface -> ux_slave_interface_descriptor.bInterfaceNumber == interface_value)
            {

                /* Get the control endpoint of the device.  */                
                endpoint =  &device -> ux_slave_device_control_endpoint;

                /* Get the pointer to the transfer request associated with the endpoint.  */
                transfer_request =  &endpoint -> ux_slave_endpoint_transfer_request;

                /* Set the value of the alternate setting in the buffer.  */
                *transfer_request -> ux_slave_transfer_request_data_pointer =
                            (UCHAR) interface -> ux_slave_interface_descriptor.bAlternateSetting;

                /* Setup the length appropriately.  */
                transfer_request -> ux_slave_transfer_request_requested_length =  1;

                /* Set the phase of the transfer to data out.  */
                transfer_request -> ux_slave_transfer_request_phase =  UX_TRANSFER_PHASE_DATA_OUT;

                /* Send the descriptor with the appropriate length to the host.  */
                status =  _ux_device_stack_transfer_request(transfer_request, 1, 1);

                /* Return the function status.  */
                return(status);
            }

            /* Get the next interface.  */
            interface =  interface -> ux_slave_interface_next_interface;
        }
    }

    /* Return error completion. */
    return(UX_ERROR);
}

