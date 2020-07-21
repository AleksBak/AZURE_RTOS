################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/nx_driver_stm32f7xx_low_level.s \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s 

C_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c \
../sample_netx_duo_iperf.c 

OBJS += \
./common_hardware_code.o \
./nx_driver_stm32f7xx_low_level.o \
./sample_netx_duo_iperf.o \
./startup_stm32f746nghx.o 

C_DEPS += \
./common_hardware_code.d \
./sample_netx_duo_iperf.d 


# Each subdirectory must supply rules for building sources it contributes
common_hardware_code.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -DNX_ENABLE_DHCP -c -I"../../common" -I"../../nxd" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"common_hardware_code.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
nx_driver_stm32f7xx_low_level.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/nx_driver_stm32f7xx_low_level.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
sample_netx_duo_iperf.o: ../sample_netx_duo_iperf.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -DNX_ENABLE_DHCP -c -I"../../common" -I"../../nxd" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sample_netx_duo_iperf.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
startup_stm32f746nghx.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

