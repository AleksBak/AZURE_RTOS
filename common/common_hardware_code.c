#include "common_hardware_code.h"

#define REG32(x)							(*(volatile unsigned int*)(x))

/* Define RCC register.  */
#define STM32F7_RCC							0x40023800
#define STM32F7_RCC_AHB2ENR					REG32(STM32F7_RCC + 0x34)
#define STM32F7_RCC_AHB2ENR_RNGEN			0x00000040

/* Define RNG registers.  */
#define STM32_RNG							0x50060800
#define STM32_RNG_CR						REG32(STM32_RNG + 0x00)
#define STM32_RNG_SR						REG32(STM32_RNG + 0x04)
#define STM32_RNG_DR						REG32(STM32_RNG + 0x08)
#define STM32_RNG_CR_RNGEN					0x00000004
#define STM32_RNG_CR_IE						0x00000008
#define STM32_RNG_CR_CED					0x00000020
#define STM32_RNG_SR_DRDY					0x00000001
#define STM32_RNG_SR_CECS					0x00000002
#define STM32_RNG_SR_SECS					0x00000004
#define STM32_RNG_SR_CEIS					0x00000020
#define STM32_RNG_SR_SEIS					0x00000040

/* Define symbols for initializing UART. */
#define VCP_RX_Pin							GPIO_PIN_7
#define VCP_TX_Pin							GPIO_PIN_9
#define VCP_TX_GPIO_Port					GPIOA
#define VCP_RX_GPIO_Port					GPIOB
#define ARDUINO_TX_D1_Pin					GPIO_PIN_6
#define ARDUINO_RX_D0_Pin					GPIO_PIN_7

UART_HandleTypeDef huart1;

/*-------------------------------------------- printf --------------------------------------------*/

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF);
	return ch;
}

int _write(int file, char* ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}

	return len;
}

/*-------------------------------------------- common --------------------------------------------*/

int hardware_rand(void)
{
	/* Wait for data ready.  */
	while ((STM32_RNG_SR & STM32_RNG_SR_DRDY) == 0);

	/* Return the random number.  */
	return STM32_RNG_DR;
}

/**
 * @brief UART MSP Initialization
 * This function configures the hardware resources used in this example
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	if (huart->Instance == USART1)
	{
		/* Peripheral clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/* USART1 GPIO Configuration
		 * PB7 ------> USART1_RX
		 * PA9 ------> USART1_TX
		 */
		GPIO_InitStruct.Pin = VCP_RX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(VCP_RX_GPIO_Port, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = VCP_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(VCP_TX_GPIO_Port, &GPIO_InitStruct);
	}
	else if (huart->Instance == USART6)
	{
		/* Peripheral clock enable */
		__HAL_RCC_USART6_CLK_ENABLE();

		__HAL_RCC_GPIOC_CLK_ENABLE();

		/* USART6 GPIO Configuration
		 * PC7 ------> USART6_RX
		 * PC6 ------> USART6_TX
		 */
		GPIO_InitStruct.Pin = ARDUINO_RX_D0_Pin | ARDUINO_TX_D1_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	}
}

/*--------------------------------------- private for Init ---------------------------------------*/

void BSP_SDRAM_Init();
void USB_OTG_BSP_HS_Init(void);

void hardware_rand_initialize(void)
{
	/* Enable clock for the RNG.  */
	STM32F7_RCC_AHB2ENR |= STM32F7_RCC_AHB2ENR_RNGEN;

	/* Enable the random number generator.  */
	STM32_RNG_CR = STM32_RNG_CR_RNGEN;
}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		while (1);
	}
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000
 *            HCLK(Hz)                       = 216000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432
 *            PLL_P                          = 2
 *            PLL_Q                          = 9
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	HAL_StatusTypeDef ret = HAL_OK;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;

	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	if (ret != HAL_OK)
	{
		while (1);
	}

	/* Activate the OverDrive to reach the 216 MHz Frequency */
	ret = HAL_PWREx_EnableOverDrive();
	if (ret != HAL_OK)
	{
		while (1);
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1
			| RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
	if (ret != HAL_OK)
	{
		while (1);
	}
}

/**
 * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
 * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
 *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
 * @param  None
 * @retval None
 */
static void MPU_Config(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable the MPU */
	HAL_MPU_Disable();

	/* Configure the MPU attributes as cacheable for SRAM */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x20010000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0xC0000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_8MB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER1;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/* Enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void)
{
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
}

static void GreenLed_Init(void)
{
	/* enable clock and clear 'MODER1' field for port PI */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
	GPIOI->MODER &= ~GPIO_MODER_MODER1;

	/* setup pin PI1 as 'push-pull' output and reset it in '0' */
	GPIOI->MODER |= GPIO_MODER_MODER1_0;
	GPIOI->BSRR |= GPIO_BSRR_BR_1;
}

static void BlueButton_Init(void)
{
	/* Activate PULLUP for GPIOI11 */
	uint32_t temp = GPIOI->PUPDR;
	temp &= ~(GPIO_PUPDR_PUPDR0 << (11 * 2));
	temp |= (1 << (11 * 2));
	GPIOI->PUPDR = temp;

	/* Configure IO Direction mode (Input) for GPIOI11 */
	temp = GPIOI->MODER;
	temp &= ~(GPIO_MODER_MODER0 << (11 * 2));
	temp |= ((0 & 0x00000003U) << (11 * 2));
	GPIOI->MODER = temp;
}

void GreenLed_On(void)
{
	GPIOI->BSRR |= GPIO_BSRR_BS_1;
}

void GreenLed_Off(void)
{
	GPIOI->BSRR |= GPIO_BSRR_BR_1;
}

void GreenLed_Toggle(void)
{
	GPIOI->BSRR |= ((GPIOI->ODR & 0x02) != 0x00u) ? GPIO_BSRR_BR_1 : GPIO_BSRR_BS_1;
}

int BlueButton_Pressed(void)
{
	return (GPIOI->IDR & ((uint16_t)(1 << 11)));
}

/** Initialize: MPU, CACHE, HAL_Init, Clock, SDRAM, USART1, RNG */
void hardware_setup(void)
{
	/* Configure the MPU attributes as Write Through */
	MPU_Config();

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization */
	HAL_Init();

	/* Configure the system clock to 216 MHz */
	SystemClock_Config();

	/* Configure the SDRAM.  */
	BSP_SDRAM_Init();

	/* Initialize UART for printf.  */
	MX_USART1_UART_Init();

	/* Initialize the hardware random number generator.  */
	hardware_rand_initialize();

	GreenLed_Init();
	BlueButton_Init();
}

/*------------------------------------------------------------------------------------------------*/

/**************************************************************************/
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function copies the register values from the stack into        */
/*    the C variables, then sits in a loop. The variables are named       */
/*    to indicate the register value that they hold.                      */
/*    Other registers will not have changed since the fault occurred,     */
/*    and can be viewed directly in the debugger’s CPU register window.   */
/*                                                                        */
/**************************************************************************/
void prvGetRegistersFromStack(uint32_t* pulFaultStackAddress)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"	// "-Wunused-parameter"
	/* These are volatile to try and prevent the compiler/linker optimising them
	 * away as the variables never actually get used.  If the debugger won't show the
	 * values of the variables, make them global my moving their declaration outside
	 * of this function. */
	volatile uint32_t r0;
	volatile uint32_t r1;
	volatile uint32_t r2;
	volatile uint32_t r3;
	volatile uint32_t r12;
	volatile uint32_t lr;	/* Link register. */
	volatile uint32_t pc;	/* Program counter. */
	volatile uint32_t psr;	/* Program status register. */
#pragma GCC diagnostic pop

	r0 = pulFaultStackAddress[0];
	r1 = pulFaultStackAddress[1];
	r2 = pulFaultStackAddress[2];
	r3 = pulFaultStackAddress[3];

	r12 = pulFaultStackAddress[4];
	lr = pulFaultStackAddress[5];
	pc = pulFaultStackAddress[6];	/* contains the program counter value */
	psr = pulFaultStackAddress[7];

	/* When the following line is hit, the variables contain the register values. */
	for (;;);

	/* The first register of interest is the program counter. In the code above, the variable pc
	 * contains the program counter value. When the fault is a precise fault, the pc holds the
	 * address of the instruction that was executing when the hard fault (or other fault) occurred.
	 * When the fault is an imprecise fault, then additional steps are required to find the address
	 * of the instruction that caused the fault.
	 * To find the instruction at the address held in the pc variable, either…
	 * Open an assembly code window in the debugger, and manually enter the address to view the
	 * assembly instructions at that address, or
	 * Open the break point window in the debugger, and manually define an execution or access
	 * break point at that address. With the break point set, restart the application to see which
	 * line of code the instruction relates to.
	 * Knowing the instruction that was being executed when the fault occurred allows you to know
	 * which other register values are also of interest. For example, if the instruction was using
	 * the value of R7 as an address, then the value of R7 needs to be know. Further, examining
	 * the assembly code, and the C code that generated the assembly code, will show what R7
	 * actually holds (it might be the value of a variable, for example). */

	/* ----- Handling Imprecise Faults -----
	 * ARM Cortex-M faults can be precise or imprecise. If the IMPRECISERR bit (bit 2) is set in
	 * the BusFault Status Register (or BFSR, which is byte accessible at address 0xE000ED29)
	 * is set then the fault is imprecise.
	 * It is harder to determine the cause of an imprecise fault because the fault will not
	 * necessarily occur concurrently with the instruction that caused the fault.
	 * For example, if writes to memory are cached then there might be a delay between an assembly
	 * instruction initiating a write to memory and the write to memory actually occurring.
	 * If such a delayed write operation is invalid (for example, a write is being attempted to
	 * an invalid memory location) then an imprecise fault will occur, and the program counter
	 * value obtained using the code above will not be the address of the assembly instruction
	 * that initiated the write operation.
	 * In the above example, turning off write buffering by setting the DISDEFWBUF bit (bit 1) in
	 * the Auxiliary Control Register (or ACTLR) will result in the imprecise fault becoming
	 * a precise fault, which makes the fault easier to debug, albeit at the cost of slower
	 * program execution. */
}

void NMI_Handler(void)
{
	while(1);
}

void HardFault_Handler(void)
{
	while(1)
	{
		/* fault handler implementation calls a function called 'prvGetRegistersFromStack()' */
		__asm volatile
		(
			" TST	lr, #4                                              \n"
			" ITE	eq                                                  \n"
			" MRSEQ	r0, msp                                             \n"
			" MRSNE	r0, psp                                             \n"
			" LDR	r1, [r0, #24]                                       \n"
			" LDR	r2, HANDLER2_ADDRESS_CONST                          \n"
			" BX	r2                                                  \n"
			"                                                           \n"
			" HANDLER2_ADDRESS_CONST: .word prvGetRegistersFromStack    \n"
		);
	}
}

void MemManage_Handler(void)
{
	while(1);
}

void BusFault_Handler(void)
{
	while(1);
}

void UsageFault_Handler(void)
{
	while(1);
}
