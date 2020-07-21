################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s 

C_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c \
../sample_guix_speedometer.c \
../speedometer_resources.c \
../speedometer_specifications.c 

OBJS += \
./common_hardware_code.o \
./sample_guix_speedometer.o \
./speedometer_resources.o \
./speedometer_specifications.o \
./startup_stm32f746nghx.o 

C_DEPS += \
./common_hardware_code.d \
./sample_guix_speedometer.d \
./speedometer_resources.d \
./speedometer_specifications.d 


# Each subdirectory must supply rules for building sources it contributes
common_hardware_code.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"common_hardware_code.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
sample_guix_speedometer.o: ../sample_guix_speedometer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sample_guix_speedometer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
speedometer_resources.o: ../speedometer_resources.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"speedometer_resources.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
speedometer_specifications.o: ../speedometer_specifications.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"speedometer_specifications.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
startup_stm32f746nghx.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

