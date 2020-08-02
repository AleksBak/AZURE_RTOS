################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usbx_device_controllers/ux_dcd_stm32_address_set.c \
../usbx_device_controllers/ux_dcd_stm32_delay.c \
../usbx_device_controllers/ux_dcd_stm32_endpoint_create.c \
../usbx_device_controllers/ux_dcd_stm32_endpoint_destroy.c \
../usbx_device_controllers/ux_dcd_stm32_endpoint_register_address_get.c \
../usbx_device_controllers/ux_dcd_stm32_endpoint_reset.c \
../usbx_device_controllers/ux_dcd_stm32_endpoint_stall.c \
../usbx_device_controllers/ux_dcd_stm32_endpoint_status.c \
../usbx_device_controllers/ux_dcd_stm32_fifo_flush.c \
../usbx_device_controllers/ux_dcd_stm32_fifo_read.c \
../usbx_device_controllers/ux_dcd_stm32_fifo_write.c \
../usbx_device_controllers/ux_dcd_stm32_frame_number_get.c \
../usbx_device_controllers/ux_dcd_stm32_function.c \
../usbx_device_controllers/ux_dcd_stm32_initialize.c \
../usbx_device_controllers/ux_dcd_stm32_initialize_complete.c \
../usbx_device_controllers/ux_dcd_stm32_interrupt_handler.c \
../usbx_device_controllers/ux_dcd_stm32_register_clear.c \
../usbx_device_controllers/ux_dcd_stm32_register_read.c \
../usbx_device_controllers/ux_dcd_stm32_register_set.c \
../usbx_device_controllers/ux_dcd_stm32_register_write.c \
../usbx_device_controllers/ux_dcd_stm32_state_change.c \
../usbx_device_controllers/ux_dcd_stm32_transfer_callback.c \
../usbx_device_controllers/ux_dcd_stm32_transfer_request.c 

OBJS += \
./usbx_device_controllers/ux_dcd_stm32_address_set.o \
./usbx_device_controllers/ux_dcd_stm32_delay.o \
./usbx_device_controllers/ux_dcd_stm32_endpoint_create.o \
./usbx_device_controllers/ux_dcd_stm32_endpoint_destroy.o \
./usbx_device_controllers/ux_dcd_stm32_endpoint_register_address_get.o \
./usbx_device_controllers/ux_dcd_stm32_endpoint_reset.o \
./usbx_device_controllers/ux_dcd_stm32_endpoint_stall.o \
./usbx_device_controllers/ux_dcd_stm32_endpoint_status.o \
./usbx_device_controllers/ux_dcd_stm32_fifo_flush.o \
./usbx_device_controllers/ux_dcd_stm32_fifo_read.o \
./usbx_device_controllers/ux_dcd_stm32_fifo_write.o \
./usbx_device_controllers/ux_dcd_stm32_frame_number_get.o \
./usbx_device_controllers/ux_dcd_stm32_function.o \
./usbx_device_controllers/ux_dcd_stm32_initialize.o \
./usbx_device_controllers/ux_dcd_stm32_initialize_complete.o \
./usbx_device_controllers/ux_dcd_stm32_interrupt_handler.o \
./usbx_device_controllers/ux_dcd_stm32_register_clear.o \
./usbx_device_controllers/ux_dcd_stm32_register_read.o \
./usbx_device_controllers/ux_dcd_stm32_register_set.o \
./usbx_device_controllers/ux_dcd_stm32_register_write.o \
./usbx_device_controllers/ux_dcd_stm32_state_change.o \
./usbx_device_controllers/ux_dcd_stm32_transfer_callback.o \
./usbx_device_controllers/ux_dcd_stm32_transfer_request.o 

C_DEPS += \
./usbx_device_controllers/ux_dcd_stm32_address_set.d \
./usbx_device_controllers/ux_dcd_stm32_delay.d \
./usbx_device_controllers/ux_dcd_stm32_endpoint_create.d \
./usbx_device_controllers/ux_dcd_stm32_endpoint_destroy.d \
./usbx_device_controllers/ux_dcd_stm32_endpoint_register_address_get.d \
./usbx_device_controllers/ux_dcd_stm32_endpoint_reset.d \
./usbx_device_controllers/ux_dcd_stm32_endpoint_stall.d \
./usbx_device_controllers/ux_dcd_stm32_endpoint_status.d \
./usbx_device_controllers/ux_dcd_stm32_fifo_flush.d \
./usbx_device_controllers/ux_dcd_stm32_fifo_read.d \
./usbx_device_controllers/ux_dcd_stm32_fifo_write.d \
./usbx_device_controllers/ux_dcd_stm32_frame_number_get.d \
./usbx_device_controllers/ux_dcd_stm32_function.d \
./usbx_device_controllers/ux_dcd_stm32_initialize.d \
./usbx_device_controllers/ux_dcd_stm32_initialize_complete.d \
./usbx_device_controllers/ux_dcd_stm32_interrupt_handler.d \
./usbx_device_controllers/ux_dcd_stm32_register_clear.d \
./usbx_device_controllers/ux_dcd_stm32_register_read.d \
./usbx_device_controllers/ux_dcd_stm32_register_set.d \
./usbx_device_controllers/ux_dcd_stm32_register_write.d \
./usbx_device_controllers/ux_dcd_stm32_state_change.d \
./usbx_device_controllers/ux_dcd_stm32_transfer_callback.d \
./usbx_device_controllers/ux_dcd_stm32_transfer_request.d 


# Each subdirectory must supply rules for building sources it contributes
usbx_device_controllers/ux_dcd_stm32_address_set.o: ../usbx_device_controllers/ux_dcd_stm32_address_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_address_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_delay.o: ../usbx_device_controllers/ux_dcd_stm32_delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_delay.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_endpoint_create.o: ../usbx_device_controllers/ux_dcd_stm32_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_endpoint_destroy.o: ../usbx_device_controllers/ux_dcd_stm32_endpoint_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_endpoint_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_endpoint_register_address_get.o: ../usbx_device_controllers/ux_dcd_stm32_endpoint_register_address_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_endpoint_register_address_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_endpoint_reset.o: ../usbx_device_controllers/ux_dcd_stm32_endpoint_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_endpoint_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_endpoint_stall.o: ../usbx_device_controllers/ux_dcd_stm32_endpoint_stall.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_endpoint_stall.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_endpoint_status.o: ../usbx_device_controllers/ux_dcd_stm32_endpoint_status.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_endpoint_status.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_fifo_flush.o: ../usbx_device_controllers/ux_dcd_stm32_fifo_flush.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_fifo_flush.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_fifo_read.o: ../usbx_device_controllers/ux_dcd_stm32_fifo_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_fifo_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_fifo_write.o: ../usbx_device_controllers/ux_dcd_stm32_fifo_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_fifo_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_frame_number_get.o: ../usbx_device_controllers/ux_dcd_stm32_frame_number_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_frame_number_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_function.o: ../usbx_device_controllers/ux_dcd_stm32_function.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_function.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_initialize.o: ../usbx_device_controllers/ux_dcd_stm32_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_initialize_complete.o: ../usbx_device_controllers/ux_dcd_stm32_initialize_complete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_initialize_complete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_interrupt_handler.o: ../usbx_device_controllers/ux_dcd_stm32_interrupt_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_interrupt_handler.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_register_clear.o: ../usbx_device_controllers/ux_dcd_stm32_register_clear.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_register_clear.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_register_read.o: ../usbx_device_controllers/ux_dcd_stm32_register_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_register_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_register_set.o: ../usbx_device_controllers/ux_dcd_stm32_register_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_register_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_register_write.o: ../usbx_device_controllers/ux_dcd_stm32_register_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_register_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_state_change.o: ../usbx_device_controllers/ux_dcd_stm32_state_change.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_state_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_transfer_callback.o: ../usbx_device_controllers/ux_dcd_stm32_transfer_callback.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_transfer_callback.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_controllers/ux_dcd_stm32_transfer_request.o: ../usbx_device_controllers/ux_dcd_stm32_transfer_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_controllers/ux_dcd_stm32_transfer_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

