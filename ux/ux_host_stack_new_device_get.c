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
/**   Host Stack                                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_host_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_host_stack_new_device_get                       PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function obtains a free device container for the new device.   */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    None                                                                */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    UX_DEVICE pointer                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_memory_set                Set memory to a value         */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    USBX Components                                                     */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UX_DEVICE  *_ux_host_stack_new_device_get(VOID)
{

ULONG           container_index;
UX_DEVICE       *device;
    

    /* Start with the first device.  */
    device =  _ux_system_host -> ux_system_host_device_array;    

    /* Reset the container index.  */
    container_index =  0;

    /* Search the list until the end.  */
    while (container_index++ < _ux_system_host -> ux_system_host_max_devices)
    {

        /* Until we have found an unused entry.  */
        if (device -> ux_device_handle == UX_UNUSED)
        {

            /* Reset the entire entry.  */
            _ux_utility_memory_set(device, 0, sizeof(UX_DEVICE));

            /* This entry is now used.  */
            device -> ux_device_handle =  UX_USED;

            /* Return the device pointer.  */
            return(device);
        }

        /* Move to the next device entry.  */
        device++;
    }

    /* No unused devices, return NULL.  */
    return(UX_NULL);
}

