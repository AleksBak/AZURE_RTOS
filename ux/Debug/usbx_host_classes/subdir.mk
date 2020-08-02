################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usbx_host_classes/ux_host_class_hub_activate.c \
../usbx_host_classes/ux_host_class_hub_change_detect.c \
../usbx_host_classes/ux_host_class_hub_change_process.c \
../usbx_host_classes/ux_host_class_hub_configure.c \
../usbx_host_classes/ux_host_class_hub_deactivate.c \
../usbx_host_classes/ux_host_class_hub_descriptor_get.c \
../usbx_host_classes/ux_host_class_hub_entry.c \
../usbx_host_classes/ux_host_class_hub_feature.c \
../usbx_host_classes/ux_host_class_hub_hub_change_process.c \
../usbx_host_classes/ux_host_class_hub_interrupt_endpoint_start.c \
../usbx_host_classes/ux_host_class_hub_port_change_connection_process.c \
../usbx_host_classes/ux_host_class_hub_port_change_enable_process.c \
../usbx_host_classes/ux_host_class_hub_port_change_over_current_process.c \
../usbx_host_classes/ux_host_class_hub_port_change_process.c \
../usbx_host_classes/ux_host_class_hub_port_change_reset_process.c \
../usbx_host_classes/ux_host_class_hub_port_change_suspend_process.c \
../usbx_host_classes/ux_host_class_hub_port_reset.c \
../usbx_host_classes/ux_host_class_hub_ports_power.c \
../usbx_host_classes/ux_host_class_hub_status_get.c \
../usbx_host_classes/ux_host_class_hub_transfer_request_completed.c \
../usbx_host_classes/ux_host_class_storage_activate.c \
../usbx_host_classes/ux_host_class_storage_cbw_initialize.c \
../usbx_host_classes/ux_host_class_storage_configure.c \
../usbx_host_classes/ux_host_class_storage_deactivate.c \
../usbx_host_classes/ux_host_class_storage_device_initialize.c \
../usbx_host_classes/ux_host_class_storage_device_reset.c \
../usbx_host_classes/ux_host_class_storage_device_support_check.c \
../usbx_host_classes/ux_host_class_storage_driver_entry.c \
../usbx_host_classes/ux_host_class_storage_endpoints_get.c \
../usbx_host_classes/ux_host_class_storage_entry.c \
../usbx_host_classes/ux_host_class_storage_max_lun_get.c \
../usbx_host_classes/ux_host_class_storage_media_capacity_get.c \
../usbx_host_classes/ux_host_class_storage_media_characteristics_get.c \
../usbx_host_classes/ux_host_class_storage_media_format_capacity_get.c \
../usbx_host_classes/ux_host_class_storage_media_mount.c \
../usbx_host_classes/ux_host_class_storage_media_open.c \
../usbx_host_classes/ux_host_class_storage_media_protection_check.c \
../usbx_host_classes/ux_host_class_storage_media_read.c \
../usbx_host_classes/ux_host_class_storage_media_recovery_sense_get.c \
../usbx_host_classes/ux_host_class_storage_media_write.c \
../usbx_host_classes/ux_host_class_storage_partition_read.c \
../usbx_host_classes/ux_host_class_storage_request_sense.c \
../usbx_host_classes/ux_host_class_storage_sense_code_translate.c \
../usbx_host_classes/ux_host_class_storage_start_stop.c \
../usbx_host_classes/ux_host_class_storage_thread_entry.c \
../usbx_host_classes/ux_host_class_storage_transport.c \
../usbx_host_classes/ux_host_class_storage_transport_bo.c \
../usbx_host_classes/ux_host_class_storage_transport_cb.c \
../usbx_host_classes/ux_host_class_storage_transport_cbi.c \
../usbx_host_classes/ux_host_class_storage_unit_ready_test.c 

OBJS += \
./usbx_host_classes/ux_host_class_hub_activate.o \
./usbx_host_classes/ux_host_class_hub_change_detect.o \
./usbx_host_classes/ux_host_class_hub_change_process.o \
./usbx_host_classes/ux_host_class_hub_configure.o \
./usbx_host_classes/ux_host_class_hub_deactivate.o \
./usbx_host_classes/ux_host_class_hub_descriptor_get.o \
./usbx_host_classes/ux_host_class_hub_entry.o \
./usbx_host_classes/ux_host_class_hub_feature.o \
./usbx_host_classes/ux_host_class_hub_hub_change_process.o \
./usbx_host_classes/ux_host_class_hub_interrupt_endpoint_start.o \
./usbx_host_classes/ux_host_class_hub_port_change_connection_process.o \
./usbx_host_classes/ux_host_class_hub_port_change_enable_process.o \
./usbx_host_classes/ux_host_class_hub_port_change_over_current_process.o \
./usbx_host_classes/ux_host_class_hub_port_change_process.o \
./usbx_host_classes/ux_host_class_hub_port_change_reset_process.o \
./usbx_host_classes/ux_host_class_hub_port_change_suspend_process.o \
./usbx_host_classes/ux_host_class_hub_port_reset.o \
./usbx_host_classes/ux_host_class_hub_ports_power.o \
./usbx_host_classes/ux_host_class_hub_status_get.o \
./usbx_host_classes/ux_host_class_hub_transfer_request_completed.o \
./usbx_host_classes/ux_host_class_storage_activate.o \
./usbx_host_classes/ux_host_class_storage_cbw_initialize.o \
./usbx_host_classes/ux_host_class_storage_configure.o \
./usbx_host_classes/ux_host_class_storage_deactivate.o \
./usbx_host_classes/ux_host_class_storage_device_initialize.o \
./usbx_host_classes/ux_host_class_storage_device_reset.o \
./usbx_host_classes/ux_host_class_storage_device_support_check.o \
./usbx_host_classes/ux_host_class_storage_driver_entry.o \
./usbx_host_classes/ux_host_class_storage_endpoints_get.o \
./usbx_host_classes/ux_host_class_storage_entry.o \
./usbx_host_classes/ux_host_class_storage_max_lun_get.o \
./usbx_host_classes/ux_host_class_storage_media_capacity_get.o \
./usbx_host_classes/ux_host_class_storage_media_characteristics_get.o \
./usbx_host_classes/ux_host_class_storage_media_format_capacity_get.o \
./usbx_host_classes/ux_host_class_storage_media_mount.o \
./usbx_host_classes/ux_host_class_storage_media_open.o \
./usbx_host_classes/ux_host_class_storage_media_protection_check.o \
./usbx_host_classes/ux_host_class_storage_media_read.o \
./usbx_host_classes/ux_host_class_storage_media_recovery_sense_get.o \
./usbx_host_classes/ux_host_class_storage_media_write.o \
./usbx_host_classes/ux_host_class_storage_partition_read.o \
./usbx_host_classes/ux_host_class_storage_request_sense.o \
./usbx_host_classes/ux_host_class_storage_sense_code_translate.o \
./usbx_host_classes/ux_host_class_storage_start_stop.o \
./usbx_host_classes/ux_host_class_storage_thread_entry.o \
./usbx_host_classes/ux_host_class_storage_transport.o \
./usbx_host_classes/ux_host_class_storage_transport_bo.o \
./usbx_host_classes/ux_host_class_storage_transport_cb.o \
./usbx_host_classes/ux_host_class_storage_transport_cbi.o \
./usbx_host_classes/ux_host_class_storage_unit_ready_test.o 

C_DEPS += \
./usbx_host_classes/ux_host_class_hub_activate.d \
./usbx_host_classes/ux_host_class_hub_change_detect.d \
./usbx_host_classes/ux_host_class_hub_change_process.d \
./usbx_host_classes/ux_host_class_hub_configure.d \
./usbx_host_classes/ux_host_class_hub_deactivate.d \
./usbx_host_classes/ux_host_class_hub_descriptor_get.d \
./usbx_host_classes/ux_host_class_hub_entry.d \
./usbx_host_classes/ux_host_class_hub_feature.d \
./usbx_host_classes/ux_host_class_hub_hub_change_process.d \
./usbx_host_classes/ux_host_class_hub_interrupt_endpoint_start.d \
./usbx_host_classes/ux_host_class_hub_port_change_connection_process.d \
./usbx_host_classes/ux_host_class_hub_port_change_enable_process.d \
./usbx_host_classes/ux_host_class_hub_port_change_over_current_process.d \
./usbx_host_classes/ux_host_class_hub_port_change_process.d \
./usbx_host_classes/ux_host_class_hub_port_change_reset_process.d \
./usbx_host_classes/ux_host_class_hub_port_change_suspend_process.d \
./usbx_host_classes/ux_host_class_hub_port_reset.d \
./usbx_host_classes/ux_host_class_hub_ports_power.d \
./usbx_host_classes/ux_host_class_hub_status_get.d \
./usbx_host_classes/ux_host_class_hub_transfer_request_completed.d \
./usbx_host_classes/ux_host_class_storage_activate.d \
./usbx_host_classes/ux_host_class_storage_cbw_initialize.d \
./usbx_host_classes/ux_host_class_storage_configure.d \
./usbx_host_classes/ux_host_class_storage_deactivate.d \
./usbx_host_classes/ux_host_class_storage_device_initialize.d \
./usbx_host_classes/ux_host_class_storage_device_reset.d \
./usbx_host_classes/ux_host_class_storage_device_support_check.d \
./usbx_host_classes/ux_host_class_storage_driver_entry.d \
./usbx_host_classes/ux_host_class_storage_endpoints_get.d \
./usbx_host_classes/ux_host_class_storage_entry.d \
./usbx_host_classes/ux_host_class_storage_max_lun_get.d \
./usbx_host_classes/ux_host_class_storage_media_capacity_get.d \
./usbx_host_classes/ux_host_class_storage_media_characteristics_get.d \
./usbx_host_classes/ux_host_class_storage_media_format_capacity_get.d \
./usbx_host_classes/ux_host_class_storage_media_mount.d \
./usbx_host_classes/ux_host_class_storage_media_open.d \
./usbx_host_classes/ux_host_class_storage_media_protection_check.d \
./usbx_host_classes/ux_host_class_storage_media_read.d \
./usbx_host_classes/ux_host_class_storage_media_recovery_sense_get.d \
./usbx_host_classes/ux_host_class_storage_media_write.d \
./usbx_host_classes/ux_host_class_storage_partition_read.d \
./usbx_host_classes/ux_host_class_storage_request_sense.d \
./usbx_host_classes/ux_host_class_storage_sense_code_translate.d \
./usbx_host_classes/ux_host_class_storage_start_stop.d \
./usbx_host_classes/ux_host_class_storage_thread_entry.d \
./usbx_host_classes/ux_host_class_storage_transport.d \
./usbx_host_classes/ux_host_class_storage_transport_bo.d \
./usbx_host_classes/ux_host_class_storage_transport_cb.d \
./usbx_host_classes/ux_host_class_storage_transport_cbi.d \
./usbx_host_classes/ux_host_class_storage_unit_ready_test.d 


# Each subdirectory must supply rules for building sources it contributes
usbx_host_classes/ux_host_class_hub_activate.o: ../usbx_host_classes/ux_host_class_hub_activate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_change_detect.o: ../usbx_host_classes/ux_host_class_hub_change_detect.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_change_detect.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_change_process.o: ../usbx_host_classes/ux_host_class_hub_change_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_change_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_configure.o: ../usbx_host_classes/ux_host_class_hub_configure.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_configure.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_deactivate.o: ../usbx_host_classes/ux_host_class_hub_deactivate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_descriptor_get.o: ../usbx_host_classes/ux_host_class_hub_descriptor_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_descriptor_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_entry.o: ../usbx_host_classes/ux_host_class_hub_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_feature.o: ../usbx_host_classes/ux_host_class_hub_feature.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_feature.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_hub_change_process.o: ../usbx_host_classes/ux_host_class_hub_hub_change_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_hub_change_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_interrupt_endpoint_start.o: ../usbx_host_classes/ux_host_class_hub_interrupt_endpoint_start.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_interrupt_endpoint_start.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_change_connection_process.o: ../usbx_host_classes/ux_host_class_hub_port_change_connection_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_change_connection_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_change_enable_process.o: ../usbx_host_classes/ux_host_class_hub_port_change_enable_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_change_enable_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_change_over_current_process.o: ../usbx_host_classes/ux_host_class_hub_port_change_over_current_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_change_over_current_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_change_process.o: ../usbx_host_classes/ux_host_class_hub_port_change_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_change_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_change_reset_process.o: ../usbx_host_classes/ux_host_class_hub_port_change_reset_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_change_reset_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_change_suspend_process.o: ../usbx_host_classes/ux_host_class_hub_port_change_suspend_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_change_suspend_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_port_reset.o: ../usbx_host_classes/ux_host_class_hub_port_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_port_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_ports_power.o: ../usbx_host_classes/ux_host_class_hub_ports_power.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_ports_power.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_status_get.o: ../usbx_host_classes/ux_host_class_hub_status_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_status_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_hub_transfer_request_completed.o: ../usbx_host_classes/ux_host_class_hub_transfer_request_completed.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_hub_transfer_request_completed.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_activate.o: ../usbx_host_classes/ux_host_class_storage_activate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_cbw_initialize.o: ../usbx_host_classes/ux_host_class_storage_cbw_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_cbw_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_configure.o: ../usbx_host_classes/ux_host_class_storage_configure.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_configure.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_deactivate.o: ../usbx_host_classes/ux_host_class_storage_deactivate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_device_initialize.o: ../usbx_host_classes/ux_host_class_storage_device_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_device_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_device_reset.o: ../usbx_host_classes/ux_host_class_storage_device_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_device_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_device_support_check.o: ../usbx_host_classes/ux_host_class_storage_device_support_check.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_device_support_check.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_driver_entry.o: ../usbx_host_classes/ux_host_class_storage_driver_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_driver_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_endpoints_get.o: ../usbx_host_classes/ux_host_class_storage_endpoints_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_endpoints_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_entry.o: ../usbx_host_classes/ux_host_class_storage_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_max_lun_get.o: ../usbx_host_classes/ux_host_class_storage_max_lun_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_max_lun_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_capacity_get.o: ../usbx_host_classes/ux_host_class_storage_media_capacity_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_capacity_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_characteristics_get.o: ../usbx_host_classes/ux_host_class_storage_media_characteristics_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_characteristics_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_format_capacity_get.o: ../usbx_host_classes/ux_host_class_storage_media_format_capacity_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_format_capacity_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_mount.o: ../usbx_host_classes/ux_host_class_storage_media_mount.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_mount.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_open.o: ../usbx_host_classes/ux_host_class_storage_media_open.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_open.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_protection_check.o: ../usbx_host_classes/ux_host_class_storage_media_protection_check.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_protection_check.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_read.o: ../usbx_host_classes/ux_host_class_storage_media_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_recovery_sense_get.o: ../usbx_host_classes/ux_host_class_storage_media_recovery_sense_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_recovery_sense_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_media_write.o: ../usbx_host_classes/ux_host_class_storage_media_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_media_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_partition_read.o: ../usbx_host_classes/ux_host_class_storage_partition_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_partition_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_request_sense.o: ../usbx_host_classes/ux_host_class_storage_request_sense.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_request_sense.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_sense_code_translate.o: ../usbx_host_classes/ux_host_class_storage_sense_code_translate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_sense_code_translate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_start_stop.o: ../usbx_host_classes/ux_host_class_storage_start_stop.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_start_stop.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_thread_entry.o: ../usbx_host_classes/ux_host_class_storage_thread_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_thread_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_transport.o: ../usbx_host_classes/ux_host_class_storage_transport.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_transport.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_transport_bo.o: ../usbx_host_classes/ux_host_class_storage_transport_bo.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_transport_bo.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_transport_cb.o: ../usbx_host_classes/ux_host_class_storage_transport_cb.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_transport_cb.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_transport_cbi.o: ../usbx_host_classes/ux_host_class_storage_transport_cbi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_transport_cbi.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_classes/ux_host_class_storage_unit_ready_test.o: ../usbx_host_classes/ux_host_class_storage_unit_ready_test.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_classes/ux_host_class_storage_unit_ready_test.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

