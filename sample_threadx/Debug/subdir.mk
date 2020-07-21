################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s 

C_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c \
../sample_threadx.c 

OBJS += \
./common_hardware_code.o \
./sample_threadx.o \
./startup_stm32f746nghx.o 

C_DEPS += \
./common_hardware_code.d \
./sample_threadx.d 


# Each subdirectory must supply rules for building sources it contributes
common_hardware_code.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F746xx -DSTM32F746NGHx -DSTM32F746G_DISCO -DSTM32F7 -DDEBUG -c -I"../../stm32f7xx_library" -I"../../common" -I"../../tx" -I"../../gx" -O0 -ffunction-sections -fdata-sections -Wall -mthumb-interwork -fstack-usage -MMD -MP -MF"common_hardware_code.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
sample_threadx.o: ../sample_threadx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F746xx -DSTM32F746NGHx -DSTM32F746G_DISCO -DSTM32F7 -DDEBUG -c -I"../../stm32f7xx_library" -I"../../common" -I"../../tx" -I"../../gx" -O0 -ffunction-sections -fdata-sections -Wall -mthumb-interwork -fstack-usage -MMD -MP -MF"sample_threadx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
startup_stm32f746nghx.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -mthumb-interwork -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

