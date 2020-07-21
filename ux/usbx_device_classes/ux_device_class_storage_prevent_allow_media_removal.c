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
/**   Device Storage Class                                                */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define UX_SOURCE_CODE


/* Include necessary system files.  */

#include "ux_api.h"
#include "ux_device_class_storage.h"
#include "ux_device_stack.h"


/**************************************************************************/ 
/*                                                                        */ 
/*  FUNCTION                                               RELEASE        */ 
/*                                                                        */ 
/*    _ux_device_class_storage_prevent_allow_media_removal PORTABLE C     */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function allows or prevents the removal of the media. We don't */ 
/*    do anything here, just the CSW is returned with a SUCCESS code.     */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    storage                               Pointer to storage class      */ 
/*    endpoint_in                           Pointer to IN endpoint        */
/*    endpoint_out                          Pointer to OUT endpoint       */
/*    cbwcb                                 Pointer to CBWCB              */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_device_class_storage_csw_send     Send CSW                      */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Device Storage Class                                                */
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_device_class_storage_prevent_allow_media_removal(UX_SLAVE_CLASS_STORAGE *storage, ULONG lun, 
                                            UX_SLAVE_ENDPOINT *endpoint_in,
                                            UX_SLAVE_ENDPOINT *endpoint_out, UCHAR * cbwcb)
{

    UX_PARAMETER_NOT_USED(cbwcb);
    UX_PARAMETER_NOT_USED(endpoint_out);

    /* If trace is enabled, insert this event into the trace buffer.  */
    UX_TRACE_IN_LINE_INSERT(UX_TRACE_DEVICE_CLASS_STORAGE_PREVENT_ALLOW_MEDIA_REMOVAL, storage, lun, 0, 0, UX_TRACE_DEVICE_CLASS_EVENTS, 0, 0)

    /* We return a CSW with success.  */
    _ux_device_class_storage_csw_send(storage, lun, endpoint_in, UX_SLAVE_CLASS_STORAGE_CSW_PASSED);

    /* And update the REQUEST_SENSE codes.  */
    storage -> ux_slave_class_storage_lun[lun].ux_slave_class_storage_request_sense_key         =  0x00;
    storage -> ux_slave_class_storage_lun[lun].ux_slave_class_storage_request_code              =  0x00;
    storage -> ux_slave_class_storage_lun[lun].ux_slave_class_storage_request_code_qualifier    =  0x00;

    /* Return successful completion.  */
    return(UX_SUCCESS);
}
    
