################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usbx_host_controllers/ux_hcd_stm32_asynch_queue_process.c \
../usbx_host_controllers/ux_hcd_stm32_asynch_schedule.c \
../usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_create.c \
../usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_destroy.c \
../usbx_host_controllers/ux_hcd_stm32_channel_halt.c \
../usbx_host_controllers/ux_hcd_stm32_controller_disable.c \
../usbx_host_controllers/ux_hcd_stm32_delay.c \
../usbx_host_controllers/ux_hcd_stm32_ed_obtain.c \
../usbx_host_controllers/ux_hcd_stm32_ed_td_clean.c \
../usbx_host_controllers/ux_hcd_stm32_endpoint_reset.c \
../usbx_host_controllers/ux_hcd_stm32_entry.c \
../usbx_host_controllers/ux_hcd_stm32_frame_number_get.c \
../usbx_host_controllers/ux_hcd_stm32_frame_number_set.c \
../usbx_host_controllers/ux_hcd_stm32_initialize_fscore.c \
../usbx_host_controllers/ux_hcd_stm32_initialize_hscore.c \
../usbx_host_controllers/ux_hcd_stm32_interrupt_endpoint_create.c \
../usbx_host_controllers/ux_hcd_stm32_interrupt_handler.c \
../usbx_host_controllers/ux_hcd_stm32_iso_queue_process.c \
../usbx_host_controllers/ux_hcd_stm32_iso_schedule.c \
../usbx_host_controllers/ux_hcd_stm32_isochronous_endpoint_create.c \
../usbx_host_controllers/ux_hcd_stm32_isochronous_td_obtain.c \
../usbx_host_controllers/ux_hcd_stm32_least_traffic_list_get.c \
../usbx_host_controllers/ux_hcd_stm32_periodic_endpoint_destroy.c \
../usbx_host_controllers/ux_hcd_stm32_periodic_schedule.c \
../usbx_host_controllers/ux_hcd_stm32_periodic_tree_create.c \
../usbx_host_controllers/ux_hcd_stm32_port_disable.c \
../usbx_host_controllers/ux_hcd_stm32_port_enable.c \
../usbx_host_controllers/ux_hcd_stm32_port_reset.c \
../usbx_host_controllers/ux_hcd_stm32_port_resume.c \
../usbx_host_controllers/ux_hcd_stm32_port_status_get.c \
../usbx_host_controllers/ux_hcd_stm32_port_suspend.c \
../usbx_host_controllers/ux_hcd_stm32_power_down_port.c \
../usbx_host_controllers/ux_hcd_stm32_power_on_port.c \
../usbx_host_controllers/ux_hcd_stm32_register_clear.c \
../usbx_host_controllers/ux_hcd_stm32_register_read.c \
../usbx_host_controllers/ux_hcd_stm32_register_set.c \
../usbx_host_controllers/ux_hcd_stm32_register_write.c \
../usbx_host_controllers/ux_hcd_stm32_regular_td_obtain.c \
../usbx_host_controllers/ux_hcd_stm32_request_bulk_transfer.c \
../usbx_host_controllers/ux_hcd_stm32_request_control_transfer.c \
../usbx_host_controllers/ux_hcd_stm32_request_interupt_transfer.c \
../usbx_host_controllers/ux_hcd_stm32_request_isochronous_transfer.c \
../usbx_host_controllers/ux_hcd_stm32_request_transfer.c \
../usbx_host_controllers/ux_hcd_stm32_td_schedule.c \
../usbx_host_controllers/ux_hcd_stm32_transfer_abort.c 

OBJS += \
./usbx_host_controllers/ux_hcd_stm32_asynch_queue_process.o \
./usbx_host_controllers/ux_hcd_stm32_asynch_schedule.o \
./usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_create.o \
./usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_destroy.o \
./usbx_host_controllers/ux_hcd_stm32_channel_halt.o \
./usbx_host_controllers/ux_hcd_stm32_controller_disable.o \
./usbx_host_controllers/ux_hcd_stm32_delay.o \
./usbx_host_controllers/ux_hcd_stm32_ed_obtain.o \
./usbx_host_controllers/ux_hcd_stm32_ed_td_clean.o \
./usbx_host_controllers/ux_hcd_stm32_endpoint_reset.o \
./usbx_host_controllers/ux_hcd_stm32_entry.o \
./usbx_host_controllers/ux_hcd_stm32_frame_number_get.o \
./usbx_host_controllers/ux_hcd_stm32_frame_number_set.o \
./usbx_host_controllers/ux_hcd_stm32_initialize_fscore.o \
./usbx_host_controllers/ux_hcd_stm32_initialize_hscore.o \
./usbx_host_controllers/ux_hcd_stm32_interrupt_endpoint_create.o \
./usbx_host_controllers/ux_hcd_stm32_interrupt_handler.o \
./usbx_host_controllers/ux_hcd_stm32_iso_queue_process.o \
./usbx_host_controllers/ux_hcd_stm32_iso_schedule.o \
./usbx_host_controllers/ux_hcd_stm32_isochronous_endpoint_create.o \
./usbx_host_controllers/ux_hcd_stm32_isochronous_td_obtain.o \
./usbx_host_controllers/ux_hcd_stm32_least_traffic_list_get.o \
./usbx_host_controllers/ux_hcd_stm32_periodic_endpoint_destroy.o \
./usbx_host_controllers/ux_hcd_stm32_periodic_schedule.o \
./usbx_host_controllers/ux_hcd_stm32_periodic_tree_create.o \
./usbx_host_controllers/ux_hcd_stm32_port_disable.o \
./usbx_host_controllers/ux_hcd_stm32_port_enable.o \
./usbx_host_controllers/ux_hcd_stm32_port_reset.o \
./usbx_host_controllers/ux_hcd_stm32_port_resume.o \
./usbx_host_controllers/ux_hcd_stm32_port_status_get.o \
./usbx_host_controllers/ux_hcd_stm32_port_suspend.o \
./usbx_host_controllers/ux_hcd_stm32_power_down_port.o \
./usbx_host_controllers/ux_hcd_stm32_power_on_port.o \
./usbx_host_controllers/ux_hcd_stm32_register_clear.o \
./usbx_host_controllers/ux_hcd_stm32_register_read.o \
./usbx_host_controllers/ux_hcd_stm32_register_set.o \
./usbx_host_controllers/ux_hcd_stm32_register_write.o \
./usbx_host_controllers/ux_hcd_stm32_regular_td_obtain.o \
./usbx_host_controllers/ux_hcd_stm32_request_bulk_transfer.o \
./usbx_host_controllers/ux_hcd_stm32_request_control_transfer.o \
./usbx_host_controllers/ux_hcd_stm32_request_interupt_transfer.o \
./usbx_host_controllers/ux_hcd_stm32_request_isochronous_transfer.o \
./usbx_host_controllers/ux_hcd_stm32_request_transfer.o \
./usbx_host_controllers/ux_hcd_stm32_td_schedule.o \
./usbx_host_controllers/ux_hcd_stm32_transfer_abort.o 

C_DEPS += \
./usbx_host_controllers/ux_hcd_stm32_asynch_queue_process.d \
./usbx_host_controllers/ux_hcd_stm32_asynch_schedule.d \
./usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_create.d \
./usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_destroy.d \
./usbx_host_controllers/ux_hcd_stm32_channel_halt.d \
./usbx_host_controllers/ux_hcd_stm32_controller_disable.d \
./usbx_host_controllers/ux_hcd_stm32_delay.d \
./usbx_host_controllers/ux_hcd_stm32_ed_obtain.d \
./usbx_host_controllers/ux_hcd_stm32_ed_td_clean.d \
./usbx_host_controllers/ux_hcd_stm32_endpoint_reset.d \
./usbx_host_controllers/ux_hcd_stm32_entry.d \
./usbx_host_controllers/ux_hcd_stm32_frame_number_get.d \
./usbx_host_controllers/ux_hcd_stm32_frame_number_set.d \
./usbx_host_controllers/ux_hcd_stm32_initialize_fscore.d \
./usbx_host_controllers/ux_hcd_stm32_initialize_hscore.d \
./usbx_host_controllers/ux_hcd_stm32_interrupt_endpoint_create.d \
./usbx_host_controllers/ux_hcd_stm32_interrupt_handler.d \
./usbx_host_controllers/ux_hcd_stm32_iso_queue_process.d \
./usbx_host_controllers/ux_hcd_stm32_iso_schedule.d \
./usbx_host_controllers/ux_hcd_stm32_isochronous_endpoint_create.d \
./usbx_host_controllers/ux_hcd_stm32_isochronous_td_obtain.d \
./usbx_host_controllers/ux_hcd_stm32_least_traffic_list_get.d \
./usbx_host_controllers/ux_hcd_stm32_periodic_endpoint_destroy.d \
./usbx_host_controllers/ux_hcd_stm32_periodic_schedule.d \
./usbx_host_controllers/ux_hcd_stm32_periodic_tree_create.d \
./usbx_host_controllers/ux_hcd_stm32_port_disable.d \
./usbx_host_controllers/ux_hcd_stm32_port_enable.d \
./usbx_host_controllers/ux_hcd_stm32_port_reset.d \
./usbx_host_controllers/ux_hcd_stm32_port_resume.d \
./usbx_host_controllers/ux_hcd_stm32_port_status_get.d \
./usbx_host_controllers/ux_hcd_stm32_port_suspend.d \
./usbx_host_controllers/ux_hcd_stm32_power_down_port.d \
./usbx_host_controllers/ux_hcd_stm32_power_on_port.d \
./usbx_host_controllers/ux_hcd_stm32_register_clear.d \
./usbx_host_controllers/ux_hcd_stm32_register_read.d \
./usbx_host_controllers/ux_hcd_stm32_register_set.d \
./usbx_host_controllers/ux_hcd_stm32_register_write.d \
./usbx_host_controllers/ux_hcd_stm32_regular_td_obtain.d \
./usbx_host_controllers/ux_hcd_stm32_request_bulk_transfer.d \
./usbx_host_controllers/ux_hcd_stm32_request_control_transfer.d \
./usbx_host_controllers/ux_hcd_stm32_request_interupt_transfer.d \
./usbx_host_controllers/ux_hcd_stm32_request_isochronous_transfer.d \
./usbx_host_controllers/ux_hcd_stm32_request_transfer.d \
./usbx_host_controllers/ux_hcd_stm32_td_schedule.d \
./usbx_host_controllers/ux_hcd_stm32_transfer_abort.d 


# Each subdirectory must supply rules for building sources it contributes
usbx_host_controllers/ux_hcd_stm32_asynch_queue_process.o: ../usbx_host_controllers/ux_hcd_stm32_asynch_queue_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_asynch_queue_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_asynch_schedule.o: ../usbx_host_controllers/ux_hcd_stm32_asynch_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_asynch_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_create.o: ../usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_destroy.o: ../usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_asynchronous_endpoint_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_channel_halt.o: ../usbx_host_controllers/ux_hcd_stm32_channel_halt.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_channel_halt.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_controller_disable.o: ../usbx_host_controllers/ux_hcd_stm32_controller_disable.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_controller_disable.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_delay.o: ../usbx_host_controllers/ux_hcd_stm32_delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_delay.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_ed_obtain.o: ../usbx_host_controllers/ux_hcd_stm32_ed_obtain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_ed_obtain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_ed_td_clean.o: ../usbx_host_controllers/ux_hcd_stm32_ed_td_clean.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_ed_td_clean.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_endpoint_reset.o: ../usbx_host_controllers/ux_hcd_stm32_endpoint_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_endpoint_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_entry.o: ../usbx_host_controllers/ux_hcd_stm32_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_frame_number_get.o: ../usbx_host_controllers/ux_hcd_stm32_frame_number_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_frame_number_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_frame_number_set.o: ../usbx_host_controllers/ux_hcd_stm32_frame_number_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_frame_number_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_initialize_fscore.o: ../usbx_host_controllers/ux_hcd_stm32_initialize_fscore.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_initialize_fscore.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_initialize_hscore.o: ../usbx_host_controllers/ux_hcd_stm32_initialize_hscore.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_initialize_hscore.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_interrupt_endpoint_create.o: ../usbx_host_controllers/ux_hcd_stm32_interrupt_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_interrupt_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_interrupt_handler.o: ../usbx_host_controllers/ux_hcd_stm32_interrupt_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_interrupt_handler.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_iso_queue_process.o: ../usbx_host_controllers/ux_hcd_stm32_iso_queue_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_iso_queue_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_iso_schedule.o: ../usbx_host_controllers/ux_hcd_stm32_iso_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_iso_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_isochronous_endpoint_create.o: ../usbx_host_controllers/ux_hcd_stm32_isochronous_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_isochronous_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_isochronous_td_obtain.o: ../usbx_host_controllers/ux_hcd_stm32_isochronous_td_obtain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_isochronous_td_obtain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_least_traffic_list_get.o: ../usbx_host_controllers/ux_hcd_stm32_least_traffic_list_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_least_traffic_list_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_periodic_endpoint_destroy.o: ../usbx_host_controllers/ux_hcd_stm32_periodic_endpoint_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_periodic_endpoint_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_periodic_schedule.o: ../usbx_host_controllers/ux_hcd_stm32_periodic_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_periodic_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_periodic_tree_create.o: ../usbx_host_controllers/ux_hcd_stm32_periodic_tree_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_periodic_tree_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_port_disable.o: ../usbx_host_controllers/ux_hcd_stm32_port_disable.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_port_disable.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_port_enable.o: ../usbx_host_controllers/ux_hcd_stm32_port_enable.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_port_enable.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_port_reset.o: ../usbx_host_controllers/ux_hcd_stm32_port_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_port_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_port_resume.o: ../usbx_host_controllers/ux_hcd_stm32_port_resume.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_port_resume.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_port_status_get.o: ../usbx_host_controllers/ux_hcd_stm32_port_status_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_port_status_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_port_suspend.o: ../usbx_host_controllers/ux_hcd_stm32_port_suspend.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_port_suspend.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_power_down_port.o: ../usbx_host_controllers/ux_hcd_stm32_power_down_port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_power_down_port.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_power_on_port.o: ../usbx_host_controllers/ux_hcd_stm32_power_on_port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_power_on_port.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_register_clear.o: ../usbx_host_controllers/ux_hcd_stm32_register_clear.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_register_clear.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_register_read.o: ../usbx_host_controllers/ux_hcd_stm32_register_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_register_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_register_set.o: ../usbx_host_controllers/ux_hcd_stm32_register_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_register_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_register_write.o: ../usbx_host_controllers/ux_hcd_stm32_register_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_register_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_regular_td_obtain.o: ../usbx_host_controllers/ux_hcd_stm32_regular_td_obtain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_regular_td_obtain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_request_bulk_transfer.o: ../usbx_host_controllers/ux_hcd_stm32_request_bulk_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_request_bulk_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_request_control_transfer.o: ../usbx_host_controllers/ux_hcd_stm32_request_control_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_request_control_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_request_interupt_transfer.o: ../usbx_host_controllers/ux_hcd_stm32_request_interupt_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_request_interupt_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_request_isochronous_transfer.o: ../usbx_host_controllers/ux_hcd_stm32_request_isochronous_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_request_isochronous_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_request_transfer.o: ../usbx_host_controllers/ux_hcd_stm32_request_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_request_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_td_schedule.o: ../usbx_host_controllers/ux_hcd_stm32_td_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_td_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
usbx_host_controllers/ux_hcd_stm32_transfer_abort.o: ../usbx_host_controllers/ux_hcd_stm32_transfer_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"usbx_host_controllers/ux_hcd_stm32_transfer_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

