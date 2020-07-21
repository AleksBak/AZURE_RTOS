################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s 

C_SRCS += \
C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c \
../guix_medical_resources.c \
../guix_medical_specifications.c \
../medications.c \
../patients.c \
../sample_guix_medical.c \
../vitals.c 

OBJS += \
./common_hardware_code.o \
./guix_medical_resources.o \
./guix_medical_specifications.o \
./medications.o \
./patients.o \
./sample_guix_medical.o \
./startup_stm32f746nghx.o \
./vitals.o 

C_DEPS += \
./common_hardware_code.d \
./guix_medical_resources.d \
./guix_medical_specifications.d \
./medications.d \
./patients.d \
./sample_guix_medical.d \
./vitals.d 


# Each subdirectory must supply rules for building sources it contributes
common_hardware_code.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/common_hardware_code.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"common_hardware_code.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
guix_medical_resources.o: ../guix_medical_resources.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"guix_medical_resources.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
guix_medical_specifications.o: ../guix_medical_specifications.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"guix_medical_specifications.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
medications.o: ../medications.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"medications.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
patients.o: ../patients.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"patients.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
sample_guix_medical.o: ../sample_guix_medical.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sample_guix_medical.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
startup_stm32f746nghx.o: C:/Users/YTTIH-5/Documents/workspace_1.0.0/AZURE_RTOS/common/startup_stm32f746nghx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
vitals.o: ../vitals.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32F746xx -c -I"../../common" -I"../../tx" -I"../../fx" -I"../../gx" -I"../../stm32f7xx_library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"vitals.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

