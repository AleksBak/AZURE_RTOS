################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usbx_device_classes/ux_device_class_cdc_acm_activate.c \
../usbx_device_classes/ux_device_class_cdc_acm_bulkin_thread.c \
../usbx_device_classes/ux_device_class_cdc_acm_bulkout_thread.c \
../usbx_device_classes/ux_device_class_cdc_acm_control_request.c \
../usbx_device_classes/ux_device_class_cdc_acm_deactivate.c \
../usbx_device_classes/ux_device_class_cdc_acm_entry.c \
../usbx_device_classes/ux_device_class_cdc_acm_initialize.c \
../usbx_device_classes/ux_device_class_cdc_acm_ioctl.c \
../usbx_device_classes/ux_device_class_cdc_acm_read.c \
../usbx_device_classes/ux_device_class_cdc_acm_unitialize.c \
../usbx_device_classes/ux_device_class_cdc_acm_write.c \
../usbx_device_classes/ux_device_class_cdc_acm_write_with_callback.c \
../usbx_device_classes/ux_device_class_storage_activate.c \
../usbx_device_classes/ux_device_class_storage_control_request.c \
../usbx_device_classes/ux_device_class_storage_csw_send.c \
../usbx_device_classes/ux_device_class_storage_deactivate.c \
../usbx_device_classes/ux_device_class_storage_entry.c \
../usbx_device_classes/ux_device_class_storage_format.c \
../usbx_device_classes/ux_device_class_storage_get_configuration.c \
../usbx_device_classes/ux_device_class_storage_get_performance.c \
../usbx_device_classes/ux_device_class_storage_get_status_notification.c \
../usbx_device_classes/ux_device_class_storage_initialize.c \
../usbx_device_classes/ux_device_class_storage_inquiry.c \
../usbx_device_classes/ux_device_class_storage_mode_select.c \
../usbx_device_classes/ux_device_class_storage_mode_sense.c \
../usbx_device_classes/ux_device_class_storage_prevent_allow_media_removal.c \
../usbx_device_classes/ux_device_class_storage_read.c \
../usbx_device_classes/ux_device_class_storage_read_capacity.c \
../usbx_device_classes/ux_device_class_storage_read_disk_information.c \
../usbx_device_classes/ux_device_class_storage_read_dvd_structure.c \
../usbx_device_classes/ux_device_class_storage_read_format_capacity.c \
../usbx_device_classes/ux_device_class_storage_read_toc.c \
../usbx_device_classes/ux_device_class_storage_report_key.c \
../usbx_device_classes/ux_device_class_storage_request_sense.c \
../usbx_device_classes/ux_device_class_storage_start_stop.c \
../usbx_device_classes/ux_device_class_storage_synchronize_cache.c \
../usbx_device_classes/ux_device_class_storage_test_ready.c \
../usbx_device_classes/ux_device_class_storage_thread.c \
../usbx_device_classes/ux_device_class_storage_uninitialize.c \
../usbx_device_classes/ux_device_class_storage_verify.c \
../usbx_device_classes/ux_device_class_storage_write.c 

OBJS += \
./usbx_device_classes/ux_device_class_cdc_acm_activate.o \
./usbx_device_classes/ux_device_class_cdc_acm_bulkin_thread.o \
./usbx_device_classes/ux_device_class_cdc_acm_bulkout_thread.o \
./usbx_device_classes/ux_device_class_cdc_acm_control_request.o \
./usbx_device_classes/ux_device_class_cdc_acm_deactivate.o \
./usbx_device_classes/ux_device_class_cdc_acm_entry.o \
./usbx_device_classes/ux_device_class_cdc_acm_initialize.o \
./usbx_device_classes/ux_device_class_cdc_acm_ioctl.o \
./usbx_device_classes/ux_device_class_cdc_acm_read.o \
./usbx_device_classes/ux_device_class_cdc_acm_unitialize.o \
./usbx_device_classes/ux_device_class_cdc_acm_write.o \
./usbx_device_classes/ux_device_class_cdc_acm_write_with_callback.o \
./usbx_device_classes/ux_device_class_storage_activate.o \
./usbx_device_classes/ux_device_class_storage_control_request.o \
./usbx_device_classes/ux_device_class_storage_csw_send.o \
./usbx_device_classes/ux_device_class_storage_deactivate.o \
./usbx_device_classes/ux_device_class_storage_entry.o \
./usbx_device_classes/ux_device_class_storage_format.o \
./usbx_device_classes/ux_device_class_storage_get_configuration.o \
./usbx_device_classes/ux_device_class_storage_get_performance.o \
./usbx_device_classes/ux_device_class_storage_get_status_notification.o \
./usbx_device_classes/ux_device_class_storage_initialize.o \
./usbx_device_classes/ux_device_class_storage_inquiry.o \
./usbx_device_classes/ux_device_class_storage_mode_select.o \
./usbx_device_classes/ux_device_class_storage_mode_sense.o \
./usbx_device_classes/ux_device_class_storage_prevent_allow_media_removal.o \
./usbx_device_classes/ux_device_class_storage_read.o \
./usbx_device_classes/ux_device_class_storage_read_capacity.o \
./usbx_device_classes/ux_device_class_storage_read_disk_information.o \
./usbx_device_classes/ux_device_class_storage_read_dvd_structure.o \
./usbx_device_classes/ux_device_class_storage_read_format_capacity.o \
./usbx_device_classes/ux_device_class_storage_read_toc.o \
./usbx_device_classes/ux_device_class_storage_report_key.o \
./usbx_device_classes/ux_device_class_storage_request_sense.o \
./usbx_device_classes/ux_device_class_storage_start_stop.o \
./usbx_device_classes/ux_device_class_storage_synchronize_cache.o \
./usbx_device_classes/ux_device_class_storage_test_ready.o \
./usbx_device_classes/ux_device_class_storage_thread.o \
./usbx_device_classes/ux_device_class_storage_uninitialize.o \
./usbx_device_classes/ux_device_class_storage_verify.o \
./usbx_device_classes/ux_device_class_storage_write.o 

C_DEPS += \
./usbx_device_classes/ux_device_class_cdc_acm_activate.d \
./usbx_device_classes/ux_device_class_cdc_acm_bulkin_thread.d \
./usbx_device_classes/ux_device_class_cdc_acm_bulkout_thread.d \
./usbx_device_classes/ux_device_class_cdc_acm_control_request.d \
./usbx_device_classes/ux_device_class_cdc_acm_deactivate.d \
./usbx_device_classes/ux_device_class_cdc_acm_entry.d \
./usbx_device_classes/ux_device_class_cdc_acm_initialize.d \
./usbx_device_classes/ux_device_class_cdc_acm_ioctl.d \
./usbx_device_classes/ux_device_class_cdc_acm_read.d \
./usbx_device_classes/ux_device_class_cdc_acm_unitialize.d \
./usbx_device_classes/ux_device_class_cdc_acm_write.d \
./usbx_device_classes/ux_device_class_cdc_acm_write_with_callback.d \
./usbx_device_classes/ux_device_class_storage_activate.d \
./usbx_device_classes/ux_device_class_storage_control_request.d \
./usbx_device_classes/ux_device_class_storage_csw_send.d \
./usbx_device_classes/ux_device_class_storage_deactivate.d \
./usbx_device_classes/ux_device_class_storage_entry.d \
./usbx_device_classes/ux_device_class_storage_format.d \
./usbx_device_classes/ux_device_class_storage_get_configuration.d \
./usbx_device_classes/ux_device_class_storage_get_performance.d \
./usbx_device_classes/ux_device_class_storage_get_status_notification.d \
./usbx_device_classes/ux_device_class_storage_initialize.d \
./usbx_device_classes/ux_device_class_storage_inquiry.d \
./usbx_device_classes/ux_device_class_storage_mode_select.d \
./usbx_device_classes/ux_device_class_storage_mode_sense.d \
./usbx_device_classes/ux_device_class_storage_prevent_allow_media_removal.d \
./usbx_device_classes/ux_device_class_storage_read.d \
./usbx_device_classes/ux_device_class_storage_read_capacity.d \
./usbx_device_classes/ux_device_class_storage_read_disk_information.d \
./usbx_device_classes/ux_device_class_storage_read_dvd_structure.d \
./usbx_device_classes/ux_device_class_storage_read_format_capacity.d \
./usbx_device_classes/ux_device_class_storage_read_toc.d \
./usbx_device_classes/ux_device_class_storage_report_key.d \
./usbx_device_classes/ux_device_class_storage_request_sense.d \
./usbx_device_classes/ux_device_class_storage_start_stop.d \
./usbx_device_classes/ux_device_class_storage_synchronize_cache.d \
./usbx_device_classes/ux_device_class_storage_test_ready.d \
./usbx_device_classes/ux_device_class_storage_thread.d \
./usbx_device_classes/ux_device_class_storage_uninitialize.d \
./usbx_device_classes/ux_device_class_storage_verify.d \
./usbx_device_classes/ux_device_class_storage_write.d 


# Each subdirectory must supply rules for building sources it contributes
usbx_device_classes/ux_device_class_cdc_acm_activate.o: ../usbx_device_classes/ux_device_class_cdc_acm_activate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_bulkin_thread.o: ../usbx_device_classes/ux_device_class_cdc_acm_bulkin_thread.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_bulkin_thread.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_bulkout_thread.o: ../usbx_device_classes/ux_device_class_cdc_acm_bulkout_thread.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_bulkout_thread.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_control_request.o: ../usbx_device_classes/ux_device_class_cdc_acm_control_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_control_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_deactivate.o: ../usbx_device_classes/ux_device_class_cdc_acm_deactivate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_entry.o: ../usbx_device_classes/ux_device_class_cdc_acm_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_initialize.o: ../usbx_device_classes/ux_device_class_cdc_acm_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_ioctl.o: ../usbx_device_classes/ux_device_class_cdc_acm_ioctl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_ioctl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_read.o: ../usbx_device_classes/ux_device_class_cdc_acm_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_unitialize.o: ../usbx_device_classes/ux_device_class_cdc_acm_unitialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_unitialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_write.o: ../usbx_device_classes/ux_device_class_cdc_acm_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_cdc_acm_write_with_callback.o: ../usbx_device_classes/ux_device_class_cdc_acm_write_with_callback.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_cdc_acm_write_with_callback.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_activate.o: ../usbx_device_classes/ux_device_class_storage_activate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_control_request.o: ../usbx_device_classes/ux_device_class_storage_control_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_control_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_csw_send.o: ../usbx_device_classes/ux_device_class_storage_csw_send.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_csw_send.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_deactivate.o: ../usbx_device_classes/ux_device_class_storage_deactivate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_entry.o: ../usbx_device_classes/ux_device_class_storage_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_format.o: ../usbx_device_classes/ux_device_class_storage_format.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_format.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_get_configuration.o: ../usbx_device_classes/ux_device_class_storage_get_configuration.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_get_configuration.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_get_performance.o: ../usbx_device_classes/ux_device_class_storage_get_performance.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_get_performance.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_get_status_notification.o: ../usbx_device_classes/ux_device_class_storage_get_status_notification.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_get_status_notification.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_initialize.o: ../usbx_device_classes/ux_device_class_storage_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_inquiry.o: ../usbx_device_classes/ux_device_class_storage_inquiry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_inquiry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_mode_select.o: ../usbx_device_classes/ux_device_class_storage_mode_select.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_mode_select.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_mode_sense.o: ../usbx_device_classes/ux_device_class_storage_mode_sense.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_mode_sense.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_prevent_allow_media_removal.o: ../usbx_device_classes/ux_device_class_storage_prevent_allow_media_removal.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_prevent_allow_media_removal.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_read.o: ../usbx_device_classes/ux_device_class_storage_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_read_capacity.o: ../usbx_device_classes/ux_device_class_storage_read_capacity.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_read_capacity.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_read_disk_information.o: ../usbx_device_classes/ux_device_class_storage_read_disk_information.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_read_disk_information.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_read_dvd_structure.o: ../usbx_device_classes/ux_device_class_storage_read_dvd_structure.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_read_dvd_structure.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_read_format_capacity.o: ../usbx_device_classes/ux_device_class_storage_read_format_capacity.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_read_format_capacity.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_read_toc.o: ../usbx_device_classes/ux_device_class_storage_read_toc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_read_toc.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_report_key.o: ../usbx_device_classes/ux_device_class_storage_report_key.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_report_key.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_request_sense.o: ../usbx_device_classes/ux_device_class_storage_request_sense.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_request_sense.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_start_stop.o: ../usbx_device_classes/ux_device_class_storage_start_stop.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_start_stop.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_synchronize_cache.o: ../usbx_device_classes/ux_device_class_storage_synchronize_cache.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_synchronize_cache.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_test_ready.o: ../usbx_device_classes/ux_device_class_storage_test_ready.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_test_ready.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_thread.o: ../usbx_device_classes/ux_device_class_storage_thread.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_thread.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_uninitialize.o: ../usbx_device_classes/ux_device_class_storage_uninitialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_uninitialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_verify.o: ../usbx_device_classes/ux_device_class_storage_verify.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_verify.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_device_classes/ux_device_class_storage_write.o: ../usbx_device_classes/ux_device_class_storage_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_device_classes/ux_device_class_storage_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

