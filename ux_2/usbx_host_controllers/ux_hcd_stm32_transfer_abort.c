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
/*    _ux_hcd_stm32_transfer_abort                        PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function will abort transactions attached to a transfer        */ 
/*    request.                                                            */ 
/*                                                                        */ 
/*    Note since ThreadX delay is used, the function must not be used in  */
/*    interrupts.                                                         */
/*                                                                        */
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    hcd_stm32                             Pointer to stm32 controller   */ 
/*    transfer_request                      Pointer to transfer request   */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_utility_delay_ms                   Delay                        */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    stm32 Controller Driver                                             */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_hcd_stm32_transfer_abort(UX_HCD_STM32 *hcd_stm32, UX_TRANSFER *transfer_request)
{
                    
UX_ENDPOINT         *endpoint;
UX_HCD_STM32_ED     *ed;
ULONG               endpoint_type;
ULONG               stm32_channel_register;

    /* Get the pointer to the endpoint associated with the transfer request.  */
    endpoint =  (UX_ENDPOINT *) transfer_request -> ux_transfer_request_endpoint;
    
    /* From the endpoint container, get the address of the physical endpoint.  */
    ed =  (UX_HCD_STM32_ED *) endpoint -> ux_endpoint_ed;
    
    /* Check if this physical endpoint has been initialized properly!  */
    if (ed == UX_NULL)
    {
    
        /* Error trap. */
        _ux_system_error_handler(UX_SYSTEM_LEVEL_THREAD, UX_SYSTEM_CONTEXT_HCD, UX_ENDPOINT_HANDLE_UNKNOWN);

        /* If trace is enabled, insert this event into the trace buffer.  */
        UX_TRACE_IN_LINE_INSERT(UX_TRACE_ERROR, UX_ENDPOINT_HANDLE_UNKNOWN, endpoint, 0, 0, UX_TRACE_ERRORS, 0, 0)

        return(UX_ENDPOINT_HANDLE_UNKNOWN);
    }

    /* The endpoint may be active. If so, set the skip bit.  */
    ed -> ux_stm32_ed_status |=  UX_HCD_STM32_ED_SKIP;

    /* Wait for the controller to finish the current frame processing.  */
    _ux_utility_delay_ms(1);

    /* Only allow the Channel Halt bit interrupt.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCINTMSK + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), UX_HCD_STM32_OTG_FS_HCINT_CHHM);                    

    /* Read the channel characteristic register.  */
    stm32_channel_register = _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE));

    /* We only Halt the channel on an endpoint which has a pending transfer.  */
    if (stm32_channel_register & UX_HCD_STM32_OTG_FS_HCCHAR_CHENA)
    {

        /* The channel is enabled. Disable the channel and rewrite the channel register.  */
        _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCCHAR + 
                                    (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), (stm32_channel_register | UX_HCD_STM32_OTG_FS_HCCHAR_CHDIS));                    

    }

    /* Wait for the controller to finish halting the channel. */
    _ux_utility_delay_ms(1);

    /* Flush FIFOs.  */
    if ((endpoint -> ux_endpoint_descriptor.bEndpointAddress & 0x80) == 0)
    {

        /* Flush the TX FIFO.  */
        endpoint_type = endpoint -> ux_endpoint_descriptor.bmAttributes & 0x3;
        if (endpoint_type == 0 || endpoint_type == 2)

            /* None-periodic Tx FIFO flush for control/bulk endpoints.  */
            _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GRSTCTL, (0|UX_HCD_STM32_OTG_FS_GRSTCTL_TXFFLSH));
        else

            /* Periodic Tx FIFO flush for interrupt/iso endpoints.  */
            _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GRSTCTL, (1|UX_HCD_STM32_OTG_FS_GRSTCTL_TXFFLSH));

        /* Wait for flush to happen.  */
        while (_ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_GRSTCTL) & UX_HCD_STM32_OTG_FS_GRSTCTL_TXFFLSH);
    }

    /* Re-enable the Host channel interrupt mask register.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCINTMSK + 
                                (ed -> ux_stm32_ed_channel * UX_HCD_STM32_ENDPOINT_CHANNEL_SIZE), UX_HCD_STM32_OTG_FS_HCINT_DEFAULT);

    /* Reset TDs (until there is dummy one created on endpoint creation).  */
    while (ed -> ux_stm32_ed_head_td != ed -> ux_stm32_ed_tail_td)
    {

        /* Double confirm, last TD's next is NULL.  */
        if (ed -> ux_stm32_ed_head_td -> ux_stm32_td_next_td == UX_NULL)
            break;

        /* Discard the TD in header.  */
        ed -> ux_stm32_ed_head_td -> ux_stm32_td_status = UX_UNUSED;
        ed -> ux_stm32_ed_head_td = ed -> ux_stm32_ed_head_td -> ux_stm32_td_next_td;
    }

    /* Remove the reset bit in the ED.  */
    ed -> ux_stm32_ed_status =  ~UX_HCD_STM32_ED_SKIP;

    /* Return successful completion.  */
    return(UX_SUCCESS);         
}

