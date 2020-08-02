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
/*    _ux_hcd_stm32_initialize                            PORTABLE C      */ 
/*                                                           6.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Chaoqiong Xiao, Microsoft Corporation                               */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */ 
/*    This function initializes the STM32 F1 USB host controller. This    */ 
/*    is not for the OTG mode. It forces the chip in Host mode only.      */ 
/*    For OTG support, the filex in the usbx_otg subdirectory must be     */ 
/*    used.                                                               */ 
/*                                                                        */ 
/*  INPUT                                                                 */ 
/*                                                                        */ 
/*    HCD                                   Pointer to HCD                */ 
/*                                                                        */ 
/*  OUTPUT                                                                */ 
/*                                                                        */ 
/*    Completion Status                                                   */ 
/*                                                                        */ 
/*  CALLS                                                                 */ 
/*                                                                        */ 
/*    _ux_hcd_stm32_register_read             Read STM32 register read    */ 
/*    _ux_hcd_stm32_register_write            Write STM32 register write  */ 
/*    _ux_hcd_stm32_periodic_tree_create      Create periodic tree        */ 
/*    _ux_hcd_stm32_power_root_hubs           Power root HUBs             */ 
/*    _ux_utility_memory_allocate             Allocate memory block       */ 
/*    _ux_utility_set_interrupt_handler       Setup interrupt handler     */ 
/*    _ux_utility_delay_ms                    Delay ms                    */ 
/*                                                                        */ 
/*  CALLED BY                                                             */ 
/*                                                                        */ 
/*    Host Stack                                                          */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  05-19-2020     Chaoqiong Xiao           Initial Version 6.0           */
/*                                                                        */
/**************************************************************************/
UINT  _ux_hcd_stm32_initialize_fscore(UX_HCD *hcd)
{

UX_HCD_STM32          *hcd_stm32;
ULONG                stm32_register;
UINT                status;

    /* The controller initialized here is of STM32 type Full Speed only.  */
    hcd -> ux_hcd_controller_type =  UX_HCD_STM32_CONTROLLER_FS;
    
    /* Initialize the max bandwidth for periodic endpoints. On STM32, the spec says 
       no more than 90% to be allocated for periodic.  */
    hcd -> ux_hcd_available_bandwidth =  UX_HCD_STM32_AVAILABLE_BANDWIDTH;

    /* Allocate memory for this STM32 HCD instance.  */
    hcd_stm32 =  _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, sizeof(UX_HCD_STM32));
    if (hcd_stm32 == UX_NULL)
        return(UX_MEMORY_INSUFFICIENT);

    /* Set the pointer to the STM32 HCD.  */
    hcd -> ux_hcd_controller_hardware =  (VOID *) hcd_stm32;

    /* Set the generic HCD owner for the STM32 HCD.  */
    hcd_stm32 -> ux_hcd_stm32_hcd_owner =  hcd;
    
    /* Save the base address.  */
    hcd_stm32 -> ux_hcd_stm32_base =  hcd -> ux_hcd_io;

    /* Initialize the function collector for this HCD.  */
    hcd -> ux_hcd_entry_function =  _ux_hcd_stm32_entry;

    /* Set the state of the controller to HALTED first.  */
    hcd -> ux_hcd_status =  UX_HCD_STATUS_HALTED;

    /* Initialize the number of channels for FS core.  */
    hcd_stm32 -> ux_hcd_stm32_nb_channels =  UX_HCD_STM32_FS_NB_CHANNELS;

    /* Allocate the list of eds.   */
    hcd_stm32 -> ux_hcd_stm32_ed_list =  _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, sizeof(UX_HCD_STM32_ED) *_ux_system_host -> ux_system_host_max_ed);
    if (hcd_stm32 -> ux_hcd_stm32_ed_list == UX_NULL)
        return(UX_MEMORY_INSUFFICIENT);

    /* Allocate the list of tds.  */
    hcd_stm32 -> ux_hcd_stm32_td_list =  _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, sizeof(UX_HCD_STM32_TD) *_ux_system_host -> ux_system_host_max_td);
    if (hcd_stm32 -> ux_hcd_stm32_td_list == UX_NULL)
        return(UX_MEMORY_INSUFFICIENT);

    /* Allocate the list of isochronous tds. */
    if (_ux_system_host -> ux_system_host_max_iso_td != 0)
    {

        /* We need Iso TDs.  */
        hcd_stm32 -> ux_hcd_stm32_iso_td_list =  _ux_utility_memory_allocate(UX_NO_ALIGN, UX_REGULAR_MEMORY, sizeof(UX_HCD_STM32_ISO_TD) *_ux_system_host -> ux_system_host_max_iso_td);
        if (hcd_stm32 -> ux_hcd_stm32_iso_td_list == UX_NULL)
            return(UX_MEMORY_INSUFFICIENT);
    }
            
    /* Initialize the periodic tree.  */
    status =  _ux_hcd_stm32_periodic_tree_create(hcd_stm32);
    if (status != UX_SUCCESS)
        return(status);

    /* Since we know this is a full-speed controller, we can hardwire the version.  */
    hcd -> ux_hcd_version =  0x100;

    /* Reset the GINT Global Interrupt Mask register.  */
    _ux_hcd_stm32_register_clear(hcd_stm32, UX_HCD_STM32_OTG_FS_GAHBCFG, UX_HCD_STM32_OTG_FS_GAHBCFG_GINT);
    
    /* PHY Selection.  */
    _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_GUSBCFG, UX_HCD_STM32_OTG_FS_GUSBCFG_PHYSEL); 

    /* Initialize the PHY Power options.  */
    _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_GCCFG , UX_HCD_STM32_OTG_FS_GCCFG_PWRDWN);

    /* Spec says wait for 10000 cycles ???.  */
    _ux_hcd_stm32_delay(1000);    

    /* Wait for AHB master Idle State.  */
    do
    {

        /* Spec says wait for 3 cycles.  */
        _ux_hcd_stm32_delay(3);    

        /* Read the RST Control register.  */
        stm32_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_GRSTCTL); 

    } while ((stm32_register & UX_HCD_STM32_OTG_FS_GRSTCTL_AHBIDL) == 0);   

    /* Perform the core soft reset.  */
    _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_GRSTCTL, UX_HCD_STM32_OTG_FS_GRSTCTL_CSRST); 
    
    /* Wait for Soft Reset to be completed.  */
    do
    {

        /* Read the RST Control register.  */
        stm32_register =  _ux_hcd_stm32_register_read(hcd_stm32, UX_HCD_STM32_OTG_FS_GRSTCTL); 

    } while (stm32_register & UX_HCD_STM32_OTG_FS_GRSTCTL_CSRST);   

    /* Spec says wait for 10 cycles.  */
    _ux_hcd_stm32_delay(10);    

    /* Force the chip to be in host mode.  This is not for OTG support. */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GUSBCFG, UX_HCD_STM32_OTG_FS_GUSBCFG_FHMOD);

    /* Spec says wait for 5000 cycles ???.  */
    _ux_hcd_stm32_delay(5000);    

    /* Restart the PHY clock. */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_PCGCCTL, 0); 

    /* Select Clock. */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HCFG, UX_HCD_STM32_OTG_FS_HCFG_FSLSPCS_FSLS); 

    /* Wait for clock to settle.  */
    _ux_utility_delay_ms(10); 
    

    /* Set the RX Fifo size. Set to 256 bytes in DWORDS.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GRXFSIZ, UX_HCD_STM32_FS_RX_FIFO_SIZE); 

    /* Set the Non periodic TX Fifo size. Set to 256 bytes in DWORDS.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GNPTXFSIZ, (UX_HCD_STM32_FS_NPTX_FIFO_SIZE << 16) | UX_HCD_STM32_FS_RX_FIFO_SIZE); 
    
    /* Set the Periodic TX Fifo size. Set to 256 bytes in DWORDS.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_HPTXFSIZ, (UX_HCD_STM32_FS_PTX_FIFO_SIZE << 16) | 
                                (UX_HCD_STM32_FS_RX_FIFO_SIZE + UX_HCD_STM32_FS_NPTX_FIFO_SIZE)); 

    /* Seems we need to wait here as well.  */
    _ux_hcd_stm32_delay(5000);    

    /* Disable all interrupts.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTMSK, 0);

    /* Clear all pending interrupts.  */
    _ux_hcd_stm32_register_write(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTSTS, 0xFFFFFFFF);

    /* Enable interrupts for the host mode only.  */
    _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_GINTMSK,     UX_HCD_STM32_OTG_FS_GINTMSK_WKUINTM   |
                                                                        UX_HCD_STM32_OTG_FS_GINTMSK_RFXLVLM      |
                                                                        UX_HCD_STM32_OTG_FS_GINTMSK_SOFM      |
                                                                        UX_HCD_STM32_OTG_FS_GINTMSK_HCIM      |
                                                                        UX_HCD_STM32_OTG_FS_GINTMSK_PRTIM     |
                                                                        UX_HCD_STM32_OTG_FS_GINTMSK_DISCINTM);

    /* The number of ports on the controller is fixed to 1. The number of ports needs to be reflected both 
       for the generic HCD container and the local stm32 container.  */
    hcd -> ux_hcd_nb_root_hubs             =  UX_HCD_STM32_NB_ROOT_PORTS;
    hcd_stm32 -> ux_hcd_stm32_nb_root_hubs =  UX_HCD_STM32_NB_ROOT_PORTS;

    /* The root port must now be powered to pick up device insertion.  */
    _ux_hcd_stm32_power_on_port(hcd_stm32, 0);

    /* The asynchronous queues are empty for now.  */
    hcd_stm32 -> ux_hcd_stm32_queue_empty =  UX_TRUE;

    /* The periodic scheduler is not active.  */
    hcd_stm32 -> ux_hcd_stm32_periodic_scheduler_active =  0;

    /* Set the host controller into the operational state.  */
    hcd -> ux_hcd_status =  UX_HCD_STATUS_OPERATIONAL;

    /* Enable the global interrupt.  */
    _ux_hcd_stm32_register_set(hcd_stm32, UX_HCD_STM32_OTG_FS_GAHBCFG, UX_HCD_STM32_OTG_FS_GAHBCFG_GINT); 

    /* Return successful completion.  */
    return(UX_SUCCESS);
}

