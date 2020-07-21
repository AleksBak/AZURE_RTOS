@/**************************************************************************/
@/*                                                                        */
@/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
@/*                                                                        */
@/**************************************************************************/
@
@
@/**************************************************************************/
@/**************************************************************************/
@/**                                                                       */ 
@/** ThreadX Component                                                     */ 
@/**                                                                       */
@/**   Initialize                                                          */
@/**                                                                       */
@/**************************************************************************/
@/**************************************************************************/
@
@#define TX_SOURCE_CODE
@
@
        .global  _tx_thread_context_save
        .global  _tx_thread_context_restore
        .global  _ux_hcd_stm32_interrupt_handler

    .text 32
    .align 4
    .syntax unified
@/**************************************************************************/ 
@/*                                                                        */ 
@/*  FUNCTION                                               RELEASE        */ 
@/*                                                                        */ 
@/*    OTG_HS_IRQHandler                                 STM32F7xx/GNU     */
@/*                                                           6.0(Beta)    */
@/*  AUTHOR                                                                */ 
@/*                                                                        */ 
@/*    William E. Lamie, Microsoft Corporation                             */
@/*                                                                        */ 
@/*  DESCRIPTION                                                           */ 
@/*                                                                        */ 
@/*    This function is responsible for fielding the USB interrupts        */ 
@/*    of the STM32F7xx.                                                   */ 
@/*                                                                        */ 
@/*  INPUT                                                                 */ 
@/*                                                                        */ 
@/*    None                                                                */ 
@/*                                                                        */ 
@/*  OUTPUT                                                                */ 
@/*                                                                        */ 
@/*    None                                                                */ 
@/*                                                                        */ 
@/*  CALLS                                                                 */ 
@/*                                                                        */ 
@/*    _ux_hcd_stm32_interrupt_handler       USBX HCD ISR processing       */ 
@/*                                                                        */ 
@/*  CALLED BY                                                             */ 
@/*                                                                        */ 
@/*    Interrupt                                                           */ 
@/*                                                                        */ 
@/*  RELEASE HISTORY                                                       */ 
@/*                                                                        */ 
@/*    DATE              NAME                      DESCRIPTION             */ 
@/*                                                                        */ 
@/*  04-02-2020     William E. Lamie         Initial Version 6.0(Beta)     */
@/*                                                                        */ 
@/**************************************************************************/
        .global  OTG_HS_IRQHandler
.thumb_func
OTG_HS_IRQHandler:
@ VOID UsbInterruptHandler (VOID)
@ {
@
        PUSH    {lr}
        BL      _ux_hcd_stm32_interrupt_handler
        POP     {lr}
        BX      LR
@ }
@
@/**************************************************************************/ 
@/*                                                                        */ 
@/*  FUNCTION                                               RELEASE        */ 
@/*                                                                        */ 
@/*    OTG_FS_IRQHandler                                 STM32F7xx/GNU     */
@/*                                                           6.0(Beta)    */
@/*  AUTHOR                                                                */ 
@/*                                                                        */ 
@/*    William E. Lamie, Microsoft Corporation                             */
@/*                                                                        */ 
@/*  DESCRIPTION                                                           */ 
@/*                                                                        */ 
@/*    This function is responsible for fielding the USB interrupts        */ 
@/*    of the STM32F7xx.                                                   */ 
@/*                                                                        */ 
@/*  INPUT                                                                 */ 
@/*                                                                        */ 
@/*    None                                                                */ 
@/*                                                                        */ 
@/*  OUTPUT                                                                */ 
@/*                                                                        */ 
@/*    None                                                                */ 
@/*                                                                        */ 
@/*  CALLS                                                                 */ 
@/*                                                                        */ 
@/*    _ux_hcd_stm32_interrupt_handler       USBX HCD ISR processing       */ 
@/*                                                                        */ 
@/*  CALLED BY                                                             */ 
@/*                                                                        */ 
@/*    Interrupt                                                           */ 
@/*                                                                        */ 
@/*  RELEASE HISTORY                                                       */ 
@/*                                                                        */ 
@/*    DATE              NAME                      DESCRIPTION             */ 
@/*                                                                        */ 
@/*  04-02-2020     William E. Lamie         Initial Version 6.0(Beta)     */
@/*                                                                        */ 
@/**************************************************************************/
        .global  OTG_FS_IRQHandler
.thumb_func
OTG_FS_IRQHandler:
@ VOID UsbInterruptHandler (VOID)
@ {
@
        PUSH    {lr}
        BL      _tx_thread_context_save
        POP     {lr}
        BX      LR
@ }
