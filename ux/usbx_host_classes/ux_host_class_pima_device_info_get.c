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
/**   PIMA Class                                                          */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */

#define UX_SOURCE_CODE

#include "ux_api.h"
#include "ux_host_class_pima.h"
#include "ux_host_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_host_class_pima_device_info_get                 PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function gets the device information block.                    */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    pima                                       Pointer to pima class    */ 
/*    pima_device                                Device structure to fill */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_host_class_pima_command               Pima command function     */
/*    _ux_utility_descriptor_parse              Unpack descriptor         */ 
/*    _ux_utility_memory_allocate               Allocate memory           */ 
/*    _ux_utility_memory_copy                   Copy memory               */
/*    _ux_utility_memory_free                   Free allocated memory     */ 
/*    _ux_utility_short_get                     Get 16-bit value          */
/*    _ux_utility_long_get                      Get 32-bit value          */
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    USB application                                                     */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_host_class_pima_device_info_get(UX_HOST_CLASS_PIMA *pima, 
                                        UX_HOST_CLASS_PIMA_DEVICE *pima_device)
{

UX_HOST_CLASS_PIMA_COMMAND           command;
UCHAR                                *device_buffer;
UCHAR                                *device_pointer;
ULONG                                unicode_string_length;
ULONG                                array_length = 0;
UINT                                 status;

    /* If trace is enabled, insert this event into the trace buffer.  */
    UX_TRACE_IN_LINE_INSERT(UX_TRACE_HOST_CLASS_PIMA_DEVICE_INFO_GET, pima, pima_device, 0, 0, UX_TRACE_HOST_CLASS_EVENTS, 0, 0)

    /* Issue command to get the device info.  no parameter.  */
    command.ux_host_class_pima_command_nb_parameters =  0;
    
    /* Other parameters unused.  */
    command.ux_host_class_pima_command_parameter_1 =  0;
    command.ux_host_class_pima_command_parameter_2 =  0;
    command.ux_host_class_pima_command_parameter_3 =  0;
    command.ux_host_class_pima_command_parameter_4 =  0;
    command.ux_host_class_pima_command_parameter_5 =  0;

    /* Then set the command to GET_DEVICE_INFO.  */
    command.ux_host_class_pima_command_operation_code =  UX_HOST_CLASS_PIMA_OC_GET_DEVICE_INFO;

    /* Allocate some DMA safe memory for receiving the device info block.  */
    device_buffer =  _ux_utility_memory_allocate(UX_SAFE_ALIGN, UX_CACHE_SAFE_MEMORY, UX_HOST_CLASS_PIMA_DEVICE_MAX_LENGTH);
    if (device_buffer == UX_NULL)
        return(UX_MEMORY_INSUFFICIENT);

    /* Issue the command.  */
    status = _ux_host_class_pima_command(pima, &command, UX_HOST_CLASS_PIMA_DATA_PHASE_IN , device_buffer, 
                                        UX_HOST_CLASS_PIMA_DEVICE_MAX_LENGTH, UX_HOST_CLASS_PIMA_DEVICE_MAX_LENGTH);

    /* Check the result. If the result is OK, the device info block was read properly. */
    if (status == UX_SUCCESS)
    {

        /* Read and store the Standard Version field.  */
        pima_device -> ux_host_class_pima_device_standard_version =  _ux_utility_short_get(device_buffer + 
                                                                                            UX_HOST_CLASS_PIMA_DEVICE_STANDARD_VERSION);
        
        /* Read and store the Vendor Extension ID .  */
        pima_device -> ux_host_class_pima_device_vendor_extension_id =  _ux_utility_long_get(device_buffer + 
                                                                                            UX_HOST_CLASS_PIMA_DEVICE_VENDOR_EXTENSION_ID);
        
        /* Read and store the Vendor Extension Version .  */
        pima_device -> ux_host_class_pima_device_vendor_extension_version =  _ux_utility_long_get(device_buffer + 
                                                                                            UX_HOST_CLASS_PIMA_DEVICE_VENDOR_EXTENSION_VERSION);
        

        /* Copy the vendor extension descriptor.   */
        device_pointer =  device_buffer + UX_HOST_CLASS_PIMA_DEVICE_VENDOR_EXTENSION_DESC;
        
        /* Get the unicode string length.  */
        unicode_string_length =  (ULONG) *device_pointer;

        /* Check if the string can fit in our buffer.  */
        if (unicode_string_length > UX_HOST_CLASS_PIMA_UNICODE_MAX_LENGTH)

            /* Return error.  */
            status =  UX_MEMORY_INSUFFICIENT;
        
        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy that string into the object description field.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_vendor_extension_desc, device_pointer, unicode_string_length);

            /* Point to the next field.  */
            device_pointer += unicode_string_length + 1;

            /* Read and store the Functional Mode.  */
            pima_device -> ux_host_class_pima_device_functional_mode =  _ux_utility_short_get(device_pointer);

            /* Point to the next field.  */
            device_pointer += sizeof(USHORT);
            
            /* Get the number of elements in array and compute total length.  */
            array_length = (ULONG)sizeof(ULONG) + (_ux_utility_long_get(device_pointer) * 2);

            /* Ensure the array can fit in our buffer.  */
            if (array_length > UX_HOST_CLASS_PIMA_ARRAY_MAX_LENGTH)

                /* Return error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy the array of supported operations.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_operations_supported, device_pointer, array_length);

            /* Point to the next field.  */
            device_pointer += array_length;

            /* Get the number of elements in array and compute total length.  */
            array_length = (ULONG)sizeof(ULONG) + (_ux_utility_long_get(device_pointer) * 2);

            /* Ensure the array can fit in our buffer.  */
            if (array_length > UX_HOST_CLASS_PIMA_ARRAY_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy the array of events supported.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_events_supported, device_pointer, array_length);

            /* Point to the next field.  */
            device_pointer += array_length;

            /* Get the number of elements in array and compute total length.  */
            array_length = (ULONG)sizeof(ULONG) + (_ux_utility_long_get(device_pointer) * 2);

            /* Ensure the array can fit in our buffer.  */
            if (array_length > UX_HOST_CLASS_PIMA_ARRAY_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy the array of device properties.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_properties_supported, device_pointer, array_length);

            /* Point to the next field.  */
            device_pointer += array_length;

            /* Get the number of elements in array and compute total length.  */
            array_length = (ULONG)sizeof(ULONG) + (_ux_utility_long_get(device_pointer) * 2);

            /* Ensure the array can fit in our buffer.  */
            if (array_length > UX_HOST_CLASS_PIMA_ARRAY_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy the array of capture formats.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_capture_formats, device_pointer, array_length);

            /* Point to the next field.  */
            device_pointer += array_length;

            /* Get the number of elements in array and compute total length.  */
            array_length = (ULONG)sizeof(ULONG) + (_ux_utility_long_get(device_pointer) * 2);

            /* Ensure the array can fit in our buffer.  */
            if (array_length > UX_HOST_CLASS_PIMA_ARRAY_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy the array of supported operations.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_image_formats, device_pointer, array_length);

            /* Point to the next field.  */
            device_pointer += array_length;

            /* Get the unicode string length.  */
            unicode_string_length =  (ULONG) *device_pointer;

            /* Ensure the string can fit in our buffer.  */
            if (unicode_string_length > UX_HOST_CLASS_PIMA_UNICODE_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy that string into the manufacturer field.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_manufacturer, device_pointer, unicode_string_length);

            /* Point to the next field.  */
            device_pointer += unicode_string_length + 1;
            
            /* Get the unicode string length.  */
            unicode_string_length =  (ULONG) *device_pointer ;

            /* Ensure the string can fit in our buffer.  */
            if (unicode_string_length > UX_HOST_CLASS_PIMA_DATE_TIME_STRING_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy that string into the model date field.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_model, device_pointer, unicode_string_length);

            /* Point to the next field.  */
            device_pointer += unicode_string_length + 1;

            /* Get the unicode string length.  */
            unicode_string_length =  (ULONG) *device_pointer ;

            /* Ensure the string can fit in our buffer.  */
            if (unicode_string_length > UX_HOST_CLASS_PIMA_DATE_TIME_STRING_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)
        {

            /* Copy that string into the version field.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_version, device_pointer, unicode_string_length);

            /* Point to the next field.  */
            device_pointer += unicode_string_length + 1;

            /* Get the unicode string length.  */
            unicode_string_length =  (ULONG) *device_pointer ;

            /* Ensure the string can fit in our buffer.  */
            if (unicode_string_length > UX_HOST_CLASS_PIMA_UNICODE_MAX_LENGTH)

                /* Return overflow error.  */
                status =  UX_MEMORY_INSUFFICIENT;
        }

        /* Is there enough space?  */
        if (status == UX_SUCCESS)

            /* Copy that string into the serial number field.  */
            _ux_utility_memory_copy(pima_device -> ux_host_class_pima_device_serial_number, device_pointer, unicode_string_length);

        else
        {

            /* If trace is enabled, insert this event into the trace buffer.  */
            UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_MEMORY_INSUFFICIENT, 0, 0, 0, UX_TRACE_ERRORS, 0, 0)

            /* Report error to application.  */
            _ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD, UX_SYSTEM_CONTEXT_CLASS, UX_MEMORY_INSUFFICIENT);
        }
    }

    /* Free the original object info buffer.  */                       
    _ux_utility_memory_free(device_buffer);
   
    /* Return completion status.  */
    return(status);
}

