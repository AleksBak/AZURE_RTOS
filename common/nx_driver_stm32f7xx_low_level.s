@/**************************************************************************/
@/*                                                                        */
@/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
@/*                                                                        */
@/*       This software is licensed under the Microsoft Software License   */
@/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
@/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
@/*       and in the root directory of this software.                      */
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
        .global  nx_driver_stm32f7xx_ethernet_isr

    .text 32
    .align 4
    .syntax unified
@/**************************************************************************/ 
@/*                                                                        */ 
@/*  FUNCTION                                               RELEASE        */ 
@/*                                                                        */ 
@/*    __nx_driver_stm32f7xx_ethernet_isr                STM32F7xx/GNU     */ 
@/*                                                           6.0          */
@/*  AUTHOR                                                                */ 
@/*                                                                        */ 
@/*    Yuxin Zhou, Microsoft Corporation                                   */
@/*                                                                        */ 
@/*  DESCRIPTION                                                           */ 
@/*                                                                        */ 
@/*    This function is responsible for fielding the etherent interrupts   */ 
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
@/*    nx_driver_stm32f7xx_ethernet_isr      NetX driver ethernet ISR      */ 
@/*                                                                        */ 
@/*  CALLED BY                                                             */ 
@/*                                                                        */ 
@/*    _tx_initialize_kernel_enter           ThreadX entry function        */ 
@/*                                                                        */ 
@/*  RELEASE HISTORY                                                       */ 
@/*                                                                        */ 
@/*    DATE              NAME                      DESCRIPTION             */ 
@/*                                                                        */ 
@/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
@/*                                                                        */ 
@/**************************************************************************/
        .global  ETH_IRQHandler
        .global  __nx_driver_stm32f7xx_ethernet_isr 
.thumb_func
ETH_IRQHandler:
.thumb_func
__nx_driver_stm32f7xx_ethernet_isr:
        PUSH    {lr}
        BL      nx_driver_stm32f7xx_ethernet_isr
        POP     {lr}
        BX      LR

