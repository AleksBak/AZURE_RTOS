#ifndef COMMON_HARDWARE_CODE_HEADER
#define COMMON_HARDWARE_CODE_HEADER

#include "stm32f7xx_hal.h"

/* Define prototypes. */
void hardware_setup();

void GreenLed_On(void);
void GreenLed_Off(void);
void GreenLed_Toggle(void);

void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

#endif
