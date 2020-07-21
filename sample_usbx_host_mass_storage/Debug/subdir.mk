################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s \
../ux_stm32f7xx_hcd_low_level.s 

C_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c \
../sample_usbx_host_mass_storage.c 

OBJS += \
./common_hardware_code.o \
./sample_usbx_host_mass_storage.o \
./startup_stm32f746nghx.o \
./ux_stm32f7xx_hcd_low_level.o 

C_DEPS += \
./common_hardware_code.d \
./sample_usbx_host_mass_storage.d 


# Each subdirectory must supply rules for building sources it contributes
common_hardware_code.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../ux/usbx_host_classes" -I"../../ux/usbx_host_controllers" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../ux" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"common_hardware_code.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
sample_usbx_host_mass_storage.o: ../sample_usbx_host_mass_storage.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../ux/usbx_host_classes" -I"../../ux/usbx_host_controllers" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../ux" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sample_usbx_host_mass_storage.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
startup_stm32f746nghx.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
%.o: ../%.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

