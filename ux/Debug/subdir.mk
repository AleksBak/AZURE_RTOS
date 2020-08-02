################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ux_dcd_sim_slave_address_set.c \
../ux_dcd_sim_slave_endpoint_create.c \
../ux_dcd_sim_slave_endpoint_destroy.c \
../ux_dcd_sim_slave_endpoint_reset.c \
../ux_dcd_sim_slave_endpoint_stall.c \
../ux_dcd_sim_slave_endpoint_status.c \
../ux_dcd_sim_slave_frame_number_get.c \
../ux_dcd_sim_slave_function.c \
../ux_dcd_sim_slave_initialize.c \
../ux_dcd_sim_slave_initialize_complete.c \
../ux_dcd_sim_slave_state_change.c \
../ux_dcd_sim_slave_transfer_abort.c \
../ux_dcd_sim_slave_transfer_request.c \
../ux_device_class_dpump_activate.c \
../ux_device_class_dpump_change.c \
../ux_device_class_dpump_deactivate.c \
../ux_device_class_dpump_entry.c \
../ux_device_class_dpump_initialize.c \
../ux_device_class_dpump_read.c \
../ux_device_class_dpump_thread.c \
../ux_device_class_dpump_write.c \
../ux_device_stack_alternate_setting_get.c \
../ux_device_stack_alternate_setting_set.c \
../ux_device_stack_class_register.c \
../ux_device_stack_class_unregister.c \
../ux_device_stack_clear_feature.c \
../ux_device_stack_configuration_get.c \
../ux_device_stack_configuration_set.c \
../ux_device_stack_control_request_process.c \
../ux_device_stack_descriptor_send.c \
../ux_device_stack_disconnect.c \
../ux_device_stack_endpoint_stall.c \
../ux_device_stack_get_status.c \
../ux_device_stack_host_wakeup.c \
../ux_device_stack_initialize.c \
../ux_device_stack_interface_delete.c \
../ux_device_stack_interface_get.c \
../ux_device_stack_interface_set.c \
../ux_device_stack_interface_start.c \
../ux_device_stack_microsoft_extension_register.c \
../ux_device_stack_set_feature.c \
../ux_device_stack_transfer_abort.c \
../ux_device_stack_transfer_all_request_abort.c \
../ux_device_stack_transfer_request.c \
../ux_device_stack_uninitialize.c \
../ux_hcd_sim_host_asynch_queue_process.c \
../ux_hcd_sim_host_asynch_schedule.c \
../ux_hcd_sim_host_asynchronous_endpoint_create.c \
../ux_hcd_sim_host_asynchronous_endpoint_destroy.c \
../ux_hcd_sim_host_ed_obtain.c \
../ux_hcd_sim_host_ed_td_clean.c \
../ux_hcd_sim_host_endpoint_reset.c \
../ux_hcd_sim_host_entry.c \
../ux_hcd_sim_host_frame_number_get.c \
../ux_hcd_sim_host_frame_number_set.c \
../ux_hcd_sim_host_initialize.c \
../ux_hcd_sim_host_interrupt_endpoint_create.c \
../ux_hcd_sim_host_iso_queue_process.c \
../ux_hcd_sim_host_iso_schedule.c \
../ux_hcd_sim_host_isochronous_endpoint_create.c \
../ux_hcd_sim_host_isochronous_td_obtain.c \
../ux_hcd_sim_host_least_traffic_list_get.c \
../ux_hcd_sim_host_periodic_endpoint_destroy.c \
../ux_hcd_sim_host_periodic_schedule.c \
../ux_hcd_sim_host_periodic_tree_create.c \
../ux_hcd_sim_host_port_reset.c \
../ux_hcd_sim_host_port_status_get.c \
../ux_hcd_sim_host_regular_td_obtain.c \
../ux_hcd_sim_host_request_bulk_transfer.c \
../ux_hcd_sim_host_request_control_transfer.c \
../ux_hcd_sim_host_request_interupt_transfer.c \
../ux_hcd_sim_host_request_isochronous_transfer.c \
../ux_hcd_sim_host_request_transfer.c \
../ux_hcd_sim_host_timer_function.c \
../ux_hcd_sim_host_transaction_schedule.c \
../ux_hcd_sim_host_transfer_abort.c \
../ux_host_class_dpump_activate.c \
../ux_host_class_dpump_configure.c \
../ux_host_class_dpump_deactivate.c \
../ux_host_class_dpump_endpoints_get.c \
../ux_host_class_dpump_entry.c \
../ux_host_class_dpump_ioctl.c \
../ux_host_class_dpump_read.c \
../ux_host_class_dpump_write.c \
../ux_host_stack_bandwidth_check.c \
../ux_host_stack_bandwidth_claim.c \
../ux_host_stack_bandwidth_release.c \
../ux_host_stack_class_call.c \
../ux_host_stack_class_device_scan.c \
../ux_host_stack_class_get.c \
../ux_host_stack_class_instance_create.c \
../ux_host_stack_class_instance_destroy.c \
../ux_host_stack_class_instance_get.c \
../ux_host_stack_class_instance_verify.c \
../ux_host_stack_class_interface_scan.c \
../ux_host_stack_class_register.c \
../ux_host_stack_configuration_descriptor_parse.c \
../ux_host_stack_configuration_enumerate.c \
../ux_host_stack_configuration_instance_create.c \
../ux_host_stack_configuration_instance_delete.c \
../ux_host_stack_configuration_interface_get.c \
../ux_host_stack_configuration_set.c \
../ux_host_stack_delay_ms.c \
../ux_host_stack_device_address_set.c \
../ux_host_stack_device_configuration_get.c \
../ux_host_stack_device_configuration_reset.c \
../ux_host_stack_device_configuration_select.c \
../ux_host_stack_device_descriptor_read.c \
../ux_host_stack_device_get.c \
../ux_host_stack_device_remove.c \
../ux_host_stack_device_resources_free.c \
../ux_host_stack_endpoint_instance_create.c \
../ux_host_stack_endpoint_instance_delete.c \
../ux_host_stack_endpoint_reset.c \
../ux_host_stack_endpoint_transfer_abort.c \
../ux_host_stack_enum_thread_entry.c \
../ux_host_stack_hcd_register.c \
../ux_host_stack_hcd_thread_entry.c \
../ux_host_stack_hcd_transfer_request.c \
../ux_host_stack_hnp_polling_thread_entry.c \
../ux_host_stack_initialize.c \
../ux_host_stack_interface_endpoint_get.c \
../ux_host_stack_interface_instance_create.c \
../ux_host_stack_interface_instance_delete.c \
../ux_host_stack_interface_set.c \
../ux_host_stack_interface_setting_select.c \
../ux_host_stack_interfaces_scan.c \
../ux_host_stack_new_configuration_create.c \
../ux_host_stack_new_device_create.c \
../ux_host_stack_new_device_get.c \
../ux_host_stack_new_endpoint_create.c \
../ux_host_stack_new_interface_create.c \
../ux_host_stack_rh_change_process.c \
../ux_host_stack_rh_device_extraction.c \
../ux_host_stack_rh_device_insertion.c \
../ux_host_stack_role_swap.c \
../ux_host_stack_transfer_request.c \
../ux_host_stack_transfer_request_abort.c \
../ux_system_error_handler.c \
../ux_system_initialize.c \
../ux_system_uninitialize.c \
../ux_trace_event_insert.c \
../ux_trace_event_update.c \
../ux_trace_object_register.c \
../ux_trace_object_unregister.c \
../ux_utility_debug_callback_register.c \
../ux_utility_debug_log.c \
../ux_utility_delay_ms.c \
../ux_utility_descriptor_pack.c \
../ux_utility_descriptor_parse.c \
../ux_utility_error_callback_register.c \
../ux_utility_event_flags_create.c \
../ux_utility_event_flags_delete.c \
../ux_utility_event_flags_get.c \
../ux_utility_event_flags_set.c \
../ux_utility_long_get.c \
../ux_utility_long_get_big_endian.c \
../ux_utility_long_put.c \
../ux_utility_long_put_big_endian.c \
../ux_utility_memory_allocate.c \
../ux_utility_memory_allocate_add_safe.c \
../ux_utility_memory_allocate_mulc_safe.c \
../ux_utility_memory_allocate_mulv_safe.c \
../ux_utility_memory_compare.c \
../ux_utility_memory_copy.c \
../ux_utility_memory_free.c \
../ux_utility_memory_free_block_best_get.c \
../ux_utility_memory_set.c \
../ux_utility_mutex_create.c \
../ux_utility_mutex_delete.c \
../ux_utility_mutex_off.c \
../ux_utility_mutex_on.c \
../ux_utility_pci_class_scan.c \
../ux_utility_pci_read.c \
../ux_utility_pci_write.c \
../ux_utility_physical_address.c \
../ux_utility_semaphore_create.c \
../ux_utility_semaphore_delete.c \
../ux_utility_semaphore_get.c \
../ux_utility_semaphore_put.c \
../ux_utility_set_interrupt_handler.c \
../ux_utility_short_get.c \
../ux_utility_short_get_big_endian.c \
../ux_utility_short_put.c \
../ux_utility_short_put_big_endian.c \
../ux_utility_string_length_check.c \
../ux_utility_string_length_get.c \
../ux_utility_string_to_unicode.c \
../ux_utility_thread_create.c \
../ux_utility_thread_delete.c \
../ux_utility_thread_identify.c \
../ux_utility_thread_relinquish.c \
../ux_utility_thread_resume.c \
../ux_utility_thread_schedule_other.c \
../ux_utility_thread_sleep.c \
../ux_utility_thread_suspend.c \
../ux_utility_timer_create.c \
../ux_utility_unicode_to_string.c \
../ux_utility_virtual_address.c 

OBJS += \
./ux_dcd_sim_slave_address_set.o \
./ux_dcd_sim_slave_endpoint_create.o \
./ux_dcd_sim_slave_endpoint_destroy.o \
./ux_dcd_sim_slave_endpoint_reset.o \
./ux_dcd_sim_slave_endpoint_stall.o \
./ux_dcd_sim_slave_endpoint_status.o \
./ux_dcd_sim_slave_frame_number_get.o \
./ux_dcd_sim_slave_function.o \
./ux_dcd_sim_slave_initialize.o \
./ux_dcd_sim_slave_initialize_complete.o \
./ux_dcd_sim_slave_state_change.o \
./ux_dcd_sim_slave_transfer_abort.o \
./ux_dcd_sim_slave_transfer_request.o \
./ux_device_class_dpump_activate.o \
./ux_device_class_dpump_change.o \
./ux_device_class_dpump_deactivate.o \
./ux_device_class_dpump_entry.o \
./ux_device_class_dpump_initialize.o \
./ux_device_class_dpump_read.o \
./ux_device_class_dpump_thread.o \
./ux_device_class_dpump_write.o \
./ux_device_stack_alternate_setting_get.o \
./ux_device_stack_alternate_setting_set.o \
./ux_device_stack_class_register.o \
./ux_device_stack_class_unregister.o \
./ux_device_stack_clear_feature.o \
./ux_device_stack_configuration_get.o \
./ux_device_stack_configuration_set.o \
./ux_device_stack_control_request_process.o \
./ux_device_stack_descriptor_send.o \
./ux_device_stack_disconnect.o \
./ux_device_stack_endpoint_stall.o \
./ux_device_stack_get_status.o \
./ux_device_stack_host_wakeup.o \
./ux_device_stack_initialize.o \
./ux_device_stack_interface_delete.o \
./ux_device_stack_interface_get.o \
./ux_device_stack_interface_set.o \
./ux_device_stack_interface_start.o \
./ux_device_stack_microsoft_extension_register.o \
./ux_device_stack_set_feature.o \
./ux_device_stack_transfer_abort.o \
./ux_device_stack_transfer_all_request_abort.o \
./ux_device_stack_transfer_request.o \
./ux_device_stack_uninitialize.o \
./ux_hcd_sim_host_asynch_queue_process.o \
./ux_hcd_sim_host_asynch_schedule.o \
./ux_hcd_sim_host_asynchronous_endpoint_create.o \
./ux_hcd_sim_host_asynchronous_endpoint_destroy.o \
./ux_hcd_sim_host_ed_obtain.o \
./ux_hcd_sim_host_ed_td_clean.o \
./ux_hcd_sim_host_endpoint_reset.o \
./ux_hcd_sim_host_entry.o \
./ux_hcd_sim_host_frame_number_get.o \
./ux_hcd_sim_host_frame_number_set.o \
./ux_hcd_sim_host_initialize.o \
./ux_hcd_sim_host_interrupt_endpoint_create.o \
./ux_hcd_sim_host_iso_queue_process.o \
./ux_hcd_sim_host_iso_schedule.o \
./ux_hcd_sim_host_isochronous_endpoint_create.o \
./ux_hcd_sim_host_isochronous_td_obtain.o \
./ux_hcd_sim_host_least_traffic_list_get.o \
./ux_hcd_sim_host_periodic_endpoint_destroy.o \
./ux_hcd_sim_host_periodic_schedule.o \
./ux_hcd_sim_host_periodic_tree_create.o \
./ux_hcd_sim_host_port_reset.o \
./ux_hcd_sim_host_port_status_get.o \
./ux_hcd_sim_host_regular_td_obtain.o \
./ux_hcd_sim_host_request_bulk_transfer.o \
./ux_hcd_sim_host_request_control_transfer.o \
./ux_hcd_sim_host_request_interupt_transfer.o \
./ux_hcd_sim_host_request_isochronous_transfer.o \
./ux_hcd_sim_host_request_transfer.o \
./ux_hcd_sim_host_timer_function.o \
./ux_hcd_sim_host_transaction_schedule.o \
./ux_hcd_sim_host_transfer_abort.o \
./ux_host_class_dpump_activate.o \
./ux_host_class_dpump_configure.o \
./ux_host_class_dpump_deactivate.o \
./ux_host_class_dpump_endpoints_get.o \
./ux_host_class_dpump_entry.o \
./ux_host_class_dpump_ioctl.o \
./ux_host_class_dpump_read.o \
./ux_host_class_dpump_write.o \
./ux_host_stack_bandwidth_check.o \
./ux_host_stack_bandwidth_claim.o \
./ux_host_stack_bandwidth_release.o \
./ux_host_stack_class_call.o \
./ux_host_stack_class_device_scan.o \
./ux_host_stack_class_get.o \
./ux_host_stack_class_instance_create.o \
./ux_host_stack_class_instance_destroy.o \
./ux_host_stack_class_instance_get.o \
./ux_host_stack_class_instance_verify.o \
./ux_host_stack_class_interface_scan.o \
./ux_host_stack_class_register.o \
./ux_host_stack_configuration_descriptor_parse.o \
./ux_host_stack_configuration_enumerate.o \
./ux_host_stack_configuration_instance_create.o \
./ux_host_stack_configuration_instance_delete.o \
./ux_host_stack_configuration_interface_get.o \
./ux_host_stack_configuration_set.o \
./ux_host_stack_delay_ms.o \
./ux_host_stack_device_address_set.o \
./ux_host_stack_device_configuration_get.o \
./ux_host_stack_device_configuration_reset.o \
./ux_host_stack_device_configuration_select.o \
./ux_host_stack_device_descriptor_read.o \
./ux_host_stack_device_get.o \
./ux_host_stack_device_remove.o \
./ux_host_stack_device_resources_free.o \
./ux_host_stack_endpoint_instance_create.o \
./ux_host_stack_endpoint_instance_delete.o \
./ux_host_stack_endpoint_reset.o \
./ux_host_stack_endpoint_transfer_abort.o \
./ux_host_stack_enum_thread_entry.o \
./ux_host_stack_hcd_register.o \
./ux_host_stack_hcd_thread_entry.o \
./ux_host_stack_hcd_transfer_request.o \
./ux_host_stack_hnp_polling_thread_entry.o \
./ux_host_stack_initialize.o \
./ux_host_stack_interface_endpoint_get.o \
./ux_host_stack_interface_instance_create.o \
./ux_host_stack_interface_instance_delete.o \
./ux_host_stack_interface_set.o \
./ux_host_stack_interface_setting_select.o \
./ux_host_stack_interfaces_scan.o \
./ux_host_stack_new_configuration_create.o \
./ux_host_stack_new_device_create.o \
./ux_host_stack_new_device_get.o \
./ux_host_stack_new_endpoint_create.o \
./ux_host_stack_new_interface_create.o \
./ux_host_stack_rh_change_process.o \
./ux_host_stack_rh_device_extraction.o \
./ux_host_stack_rh_device_insertion.o \
./ux_host_stack_role_swap.o \
./ux_host_stack_transfer_request.o \
./ux_host_stack_transfer_request_abort.o \
./ux_system_error_handler.o \
./ux_system_initialize.o \
./ux_system_uninitialize.o \
./ux_trace_event_insert.o \
./ux_trace_event_update.o \
./ux_trace_object_register.o \
./ux_trace_object_unregister.o \
./ux_utility_debug_callback_register.o \
./ux_utility_debug_log.o \
./ux_utility_delay_ms.o \
./ux_utility_descriptor_pack.o \
./ux_utility_descriptor_parse.o \
./ux_utility_error_callback_register.o \
./ux_utility_event_flags_create.o \
./ux_utility_event_flags_delete.o \
./ux_utility_event_flags_get.o \
./ux_utility_event_flags_set.o \
./ux_utility_long_get.o \
./ux_utility_long_get_big_endian.o \
./ux_utility_long_put.o \
./ux_utility_long_put_big_endian.o \
./ux_utility_memory_allocate.o \
./ux_utility_memory_allocate_add_safe.o \
./ux_utility_memory_allocate_mulc_safe.o \
./ux_utility_memory_allocate_mulv_safe.o \
./ux_utility_memory_compare.o \
./ux_utility_memory_copy.o \
./ux_utility_memory_free.o \
./ux_utility_memory_free_block_best_get.o \
./ux_utility_memory_set.o \
./ux_utility_mutex_create.o \
./ux_utility_mutex_delete.o \
./ux_utility_mutex_off.o \
./ux_utility_mutex_on.o \
./ux_utility_pci_class_scan.o \
./ux_utility_pci_read.o \
./ux_utility_pci_write.o \
./ux_utility_physical_address.o \
./ux_utility_semaphore_create.o \
./ux_utility_semaphore_delete.o \
./ux_utility_semaphore_get.o \
./ux_utility_semaphore_put.o \
./ux_utility_set_interrupt_handler.o \
./ux_utility_short_get.o \
./ux_utility_short_get_big_endian.o \
./ux_utility_short_put.o \
./ux_utility_short_put_big_endian.o \
./ux_utility_string_length_check.o \
./ux_utility_string_length_get.o \
./ux_utility_string_to_unicode.o \
./ux_utility_thread_create.o \
./ux_utility_thread_delete.o \
./ux_utility_thread_identify.o \
./ux_utility_thread_relinquish.o \
./ux_utility_thread_resume.o \
./ux_utility_thread_schedule_other.o \
./ux_utility_thread_sleep.o \
./ux_utility_thread_suspend.o \
./ux_utility_timer_create.o \
./ux_utility_unicode_to_string.o \
./ux_utility_virtual_address.o 

C_DEPS += \
./ux_dcd_sim_slave_address_set.d \
./ux_dcd_sim_slave_endpoint_create.d \
./ux_dcd_sim_slave_endpoint_destroy.d \
./ux_dcd_sim_slave_endpoint_reset.d \
./ux_dcd_sim_slave_endpoint_stall.d \
./ux_dcd_sim_slave_endpoint_status.d \
./ux_dcd_sim_slave_frame_number_get.d \
./ux_dcd_sim_slave_function.d \
./ux_dcd_sim_slave_initialize.d \
./ux_dcd_sim_slave_initialize_complete.d \
./ux_dcd_sim_slave_state_change.d \
./ux_dcd_sim_slave_transfer_abort.d \
./ux_dcd_sim_slave_transfer_request.d \
./ux_device_class_dpump_activate.d \
./ux_device_class_dpump_change.d \
./ux_device_class_dpump_deactivate.d \
./ux_device_class_dpump_entry.d \
./ux_device_class_dpump_initialize.d \
./ux_device_class_dpump_read.d \
./ux_device_class_dpump_thread.d \
./ux_device_class_dpump_write.d \
./ux_device_stack_alternate_setting_get.d \
./ux_device_stack_alternate_setting_set.d \
./ux_device_stack_class_register.d \
./ux_device_stack_class_unregister.d \
./ux_device_stack_clear_feature.d \
./ux_device_stack_configuration_get.d \
./ux_device_stack_configuration_set.d \
./ux_device_stack_control_request_process.d \
./ux_device_stack_descriptor_send.d \
./ux_device_stack_disconnect.d \
./ux_device_stack_endpoint_stall.d \
./ux_device_stack_get_status.d \
./ux_device_stack_host_wakeup.d \
./ux_device_stack_initialize.d \
./ux_device_stack_interface_delete.d \
./ux_device_stack_interface_get.d \
./ux_device_stack_interface_set.d \
./ux_device_stack_interface_start.d \
./ux_device_stack_microsoft_extension_register.d \
./ux_device_stack_set_feature.d \
./ux_device_stack_transfer_abort.d \
./ux_device_stack_transfer_all_request_abort.d \
./ux_device_stack_transfer_request.d \
./ux_device_stack_uninitialize.d \
./ux_hcd_sim_host_asynch_queue_process.d \
./ux_hcd_sim_host_asynch_schedule.d \
./ux_hcd_sim_host_asynchronous_endpoint_create.d \
./ux_hcd_sim_host_asynchronous_endpoint_destroy.d \
./ux_hcd_sim_host_ed_obtain.d \
./ux_hcd_sim_host_ed_td_clean.d \
./ux_hcd_sim_host_endpoint_reset.d \
./ux_hcd_sim_host_entry.d \
./ux_hcd_sim_host_frame_number_get.d \
./ux_hcd_sim_host_frame_number_set.d \
./ux_hcd_sim_host_initialize.d \
./ux_hcd_sim_host_interrupt_endpoint_create.d \
./ux_hcd_sim_host_iso_queue_process.d \
./ux_hcd_sim_host_iso_schedule.d \
./ux_hcd_sim_host_isochronous_endpoint_create.d \
./ux_hcd_sim_host_isochronous_td_obtain.d \
./ux_hcd_sim_host_least_traffic_list_get.d \
./ux_hcd_sim_host_periodic_endpoint_destroy.d \
./ux_hcd_sim_host_periodic_schedule.d \
./ux_hcd_sim_host_periodic_tree_create.d \
./ux_hcd_sim_host_port_reset.d \
./ux_hcd_sim_host_port_status_get.d \
./ux_hcd_sim_host_regular_td_obtain.d \
./ux_hcd_sim_host_request_bulk_transfer.d \
./ux_hcd_sim_host_request_control_transfer.d \
./ux_hcd_sim_host_request_interupt_transfer.d \
./ux_hcd_sim_host_request_isochronous_transfer.d \
./ux_hcd_sim_host_request_transfer.d \
./ux_hcd_sim_host_timer_function.d \
./ux_hcd_sim_host_transaction_schedule.d \
./ux_hcd_sim_host_transfer_abort.d \
./ux_host_class_dpump_activate.d \
./ux_host_class_dpump_configure.d \
./ux_host_class_dpump_deactivate.d \
./ux_host_class_dpump_endpoints_get.d \
./ux_host_class_dpump_entry.d \
./ux_host_class_dpump_ioctl.d \
./ux_host_class_dpump_read.d \
./ux_host_class_dpump_write.d \
./ux_host_stack_bandwidth_check.d \
./ux_host_stack_bandwidth_claim.d \
./ux_host_stack_bandwidth_release.d \
./ux_host_stack_class_call.d \
./ux_host_stack_class_device_scan.d \
./ux_host_stack_class_get.d \
./ux_host_stack_class_instance_create.d \
./ux_host_stack_class_instance_destroy.d \
./ux_host_stack_class_instance_get.d \
./ux_host_stack_class_instance_verify.d \
./ux_host_stack_class_interface_scan.d \
./ux_host_stack_class_register.d \
./ux_host_stack_configuration_descriptor_parse.d \
./ux_host_stack_configuration_enumerate.d \
./ux_host_stack_configuration_instance_create.d \
./ux_host_stack_configuration_instance_delete.d \
./ux_host_stack_configuration_interface_get.d \
./ux_host_stack_configuration_set.d \
./ux_host_stack_delay_ms.d \
./ux_host_stack_device_address_set.d \
./ux_host_stack_device_configuration_get.d \
./ux_host_stack_device_configuration_reset.d \
./ux_host_stack_device_configuration_select.d \
./ux_host_stack_device_descriptor_read.d \
./ux_host_stack_device_get.d \
./ux_host_stack_device_remove.d \
./ux_host_stack_device_resources_free.d \
./ux_host_stack_endpoint_instance_create.d \
./ux_host_stack_endpoint_instance_delete.d \
./ux_host_stack_endpoint_reset.d \
./ux_host_stack_endpoint_transfer_abort.d \
./ux_host_stack_enum_thread_entry.d \
./ux_host_stack_hcd_register.d \
./ux_host_stack_hcd_thread_entry.d \
./ux_host_stack_hcd_transfer_request.d \
./ux_host_stack_hnp_polling_thread_entry.d \
./ux_host_stack_initialize.d \
./ux_host_stack_interface_endpoint_get.d \
./ux_host_stack_interface_instance_create.d \
./ux_host_stack_interface_instance_delete.d \
./ux_host_stack_interface_set.d \
./ux_host_stack_interface_setting_select.d \
./ux_host_stack_interfaces_scan.d \
./ux_host_stack_new_configuration_create.d \
./ux_host_stack_new_device_create.d \
./ux_host_stack_new_device_get.d \
./ux_host_stack_new_endpoint_create.d \
./ux_host_stack_new_interface_create.d \
./ux_host_stack_rh_change_process.d \
./ux_host_stack_rh_device_extraction.d \
./ux_host_stack_rh_device_insertion.d \
./ux_host_stack_role_swap.d \
./ux_host_stack_transfer_request.d \
./ux_host_stack_transfer_request_abort.d \
./ux_system_error_handler.d \
./ux_system_initialize.d \
./ux_system_uninitialize.d \
./ux_trace_event_insert.d \
./ux_trace_event_update.d \
./ux_trace_object_register.d \
./ux_trace_object_unregister.d \
./ux_utility_debug_callback_register.d \
./ux_utility_debug_log.d \
./ux_utility_delay_ms.d \
./ux_utility_descriptor_pack.d \
./ux_utility_descriptor_parse.d \
./ux_utility_error_callback_register.d \
./ux_utility_event_flags_create.d \
./ux_utility_event_flags_delete.d \
./ux_utility_event_flags_get.d \
./ux_utility_event_flags_set.d \
./ux_utility_long_get.d \
./ux_utility_long_get_big_endian.d \
./ux_utility_long_put.d \
./ux_utility_long_put_big_endian.d \
./ux_utility_memory_allocate.d \
./ux_utility_memory_allocate_add_safe.d \
./ux_utility_memory_allocate_mulc_safe.d \
./ux_utility_memory_allocate_mulv_safe.d \
./ux_utility_memory_compare.d \
./ux_utility_memory_copy.d \
./ux_utility_memory_free.d \
./ux_utility_memory_free_block_best_get.d \
./ux_utility_memory_set.d \
./ux_utility_mutex_create.d \
./ux_utility_mutex_delete.d \
./ux_utility_mutex_off.d \
./ux_utility_mutex_on.d \
./ux_utility_pci_class_scan.d \
./ux_utility_pci_read.d \
./ux_utility_pci_write.d \
./ux_utility_physical_address.d \
./ux_utility_semaphore_create.d \
./ux_utility_semaphore_delete.d \
./ux_utility_semaphore_get.d \
./ux_utility_semaphore_put.d \
./ux_utility_set_interrupt_handler.d \
./ux_utility_short_get.d \
./ux_utility_short_get_big_endian.d \
./ux_utility_short_put.d \
./ux_utility_short_put_big_endian.d \
./ux_utility_string_length_check.d \
./ux_utility_string_length_get.d \
./ux_utility_string_to_unicode.d \
./ux_utility_thread_create.d \
./ux_utility_thread_delete.d \
./ux_utility_thread_identify.d \
./ux_utility_thread_relinquish.d \
./ux_utility_thread_resume.d \
./ux_utility_thread_schedule_other.d \
./ux_utility_thread_sleep.d \
./ux_utility_thread_suspend.d \
./ux_utility_timer_create.d \
./ux_utility_unicode_to_string.d \
./ux_utility_virtual_address.d 


# Each subdirectory must supply rules for building sources it contributes
ux_dcd_sim_slave_address_set.o: ../ux_dcd_sim_slave_address_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_address_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_endpoint_create.o: ../ux_dcd_sim_slave_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_endpoint_destroy.o: ../ux_dcd_sim_slave_endpoint_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_endpoint_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_endpoint_reset.o: ../ux_dcd_sim_slave_endpoint_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_endpoint_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_endpoint_stall.o: ../ux_dcd_sim_slave_endpoint_stall.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_endpoint_stall.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_endpoint_status.o: ../ux_dcd_sim_slave_endpoint_status.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_endpoint_status.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_frame_number_get.o: ../ux_dcd_sim_slave_frame_number_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_frame_number_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_function.o: ../ux_dcd_sim_slave_function.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_function.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_initialize.o: ../ux_dcd_sim_slave_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_initialize_complete.o: ../ux_dcd_sim_slave_initialize_complete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_initialize_complete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_state_change.o: ../ux_dcd_sim_slave_state_change.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_state_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_transfer_abort.o: ../ux_dcd_sim_slave_transfer_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_transfer_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_dcd_sim_slave_transfer_request.o: ../ux_dcd_sim_slave_transfer_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_dcd_sim_slave_transfer_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_activate.o: ../ux_device_class_dpump_activate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_change.o: ../ux_device_class_dpump_change.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_change.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_deactivate.o: ../ux_device_class_dpump_deactivate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_entry.o: ../ux_device_class_dpump_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_initialize.o: ../ux_device_class_dpump_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_read.o: ../ux_device_class_dpump_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_thread.o: ../ux_device_class_dpump_thread.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_thread.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_class_dpump_write.o: ../ux_device_class_dpump_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_class_dpump_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_alternate_setting_get.o: ../ux_device_stack_alternate_setting_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_alternate_setting_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_alternate_setting_set.o: ../ux_device_stack_alternate_setting_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_alternate_setting_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_class_register.o: ../ux_device_stack_class_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_class_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_class_unregister.o: ../ux_device_stack_class_unregister.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_class_unregister.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_clear_feature.o: ../ux_device_stack_clear_feature.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_clear_feature.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_configuration_get.o: ../ux_device_stack_configuration_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_configuration_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_configuration_set.o: ../ux_device_stack_configuration_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_configuration_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_control_request_process.o: ../ux_device_stack_control_request_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_control_request_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_descriptor_send.o: ../ux_device_stack_descriptor_send.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_descriptor_send.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_disconnect.o: ../ux_device_stack_disconnect.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_disconnect.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_endpoint_stall.o: ../ux_device_stack_endpoint_stall.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_endpoint_stall.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_get_status.o: ../ux_device_stack_get_status.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_get_status.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_host_wakeup.o: ../ux_device_stack_host_wakeup.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_host_wakeup.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_initialize.o: ../ux_device_stack_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_interface_delete.o: ../ux_device_stack_interface_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_interface_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_interface_get.o: ../ux_device_stack_interface_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_interface_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_interface_set.o: ../ux_device_stack_interface_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_interface_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_interface_start.o: ../ux_device_stack_interface_start.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_interface_start.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_microsoft_extension_register.o: ../ux_device_stack_microsoft_extension_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_microsoft_extension_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_set_feature.o: ../ux_device_stack_set_feature.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_set_feature.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_transfer_abort.o: ../ux_device_stack_transfer_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_transfer_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_transfer_all_request_abort.o: ../ux_device_stack_transfer_all_request_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_transfer_all_request_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_transfer_request.o: ../ux_device_stack_transfer_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_transfer_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_device_stack_uninitialize.o: ../ux_device_stack_uninitialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_device_stack_uninitialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_asynch_queue_process.o: ../ux_hcd_sim_host_asynch_queue_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_asynch_queue_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_asynch_schedule.o: ../ux_hcd_sim_host_asynch_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_asynch_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_asynchronous_endpoint_create.o: ../ux_hcd_sim_host_asynchronous_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_asynchronous_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_asynchronous_endpoint_destroy.o: ../ux_hcd_sim_host_asynchronous_endpoint_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_asynchronous_endpoint_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_ed_obtain.o: ../ux_hcd_sim_host_ed_obtain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_ed_obtain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_ed_td_clean.o: ../ux_hcd_sim_host_ed_td_clean.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_ed_td_clean.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_endpoint_reset.o: ../ux_hcd_sim_host_endpoint_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_endpoint_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_entry.o: ../ux_hcd_sim_host_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_frame_number_get.o: ../ux_hcd_sim_host_frame_number_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_frame_number_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_frame_number_set.o: ../ux_hcd_sim_host_frame_number_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_frame_number_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_initialize.o: ../ux_hcd_sim_host_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_interrupt_endpoint_create.o: ../ux_hcd_sim_host_interrupt_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_interrupt_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_iso_queue_process.o: ../ux_hcd_sim_host_iso_queue_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_iso_queue_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_iso_schedule.o: ../ux_hcd_sim_host_iso_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_iso_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_isochronous_endpoint_create.o: ../ux_hcd_sim_host_isochronous_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_isochronous_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_isochronous_td_obtain.o: ../ux_hcd_sim_host_isochronous_td_obtain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_isochronous_td_obtain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_least_traffic_list_get.o: ../ux_hcd_sim_host_least_traffic_list_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_least_traffic_list_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_periodic_endpoint_destroy.o: ../ux_hcd_sim_host_periodic_endpoint_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_periodic_endpoint_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_periodic_schedule.o: ../ux_hcd_sim_host_periodic_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_periodic_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_periodic_tree_create.o: ../ux_hcd_sim_host_periodic_tree_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_periodic_tree_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_port_reset.o: ../ux_hcd_sim_host_port_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_port_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_port_status_get.o: ../ux_hcd_sim_host_port_status_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_port_status_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_regular_td_obtain.o: ../ux_hcd_sim_host_regular_td_obtain.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_regular_td_obtain.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_request_bulk_transfer.o: ../ux_hcd_sim_host_request_bulk_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_request_bulk_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_request_control_transfer.o: ../ux_hcd_sim_host_request_control_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_request_control_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_request_interupt_transfer.o: ../ux_hcd_sim_host_request_interupt_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_request_interupt_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_request_isochronous_transfer.o: ../ux_hcd_sim_host_request_isochronous_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_request_isochronous_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_request_transfer.o: ../ux_hcd_sim_host_request_transfer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_request_transfer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_timer_function.o: ../ux_hcd_sim_host_timer_function.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_timer_function.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_transaction_schedule.o: ../ux_hcd_sim_host_transaction_schedule.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_transaction_schedule.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_hcd_sim_host_transfer_abort.o: ../ux_hcd_sim_host_transfer_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_hcd_sim_host_transfer_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_activate.o: ../ux_host_class_dpump_activate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_activate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_configure.o: ../ux_host_class_dpump_configure.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_configure.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_deactivate.o: ../ux_host_class_dpump_deactivate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_deactivate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_endpoints_get.o: ../ux_host_class_dpump_endpoints_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_endpoints_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_entry.o: ../ux_host_class_dpump_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_ioctl.o: ../ux_host_class_dpump_ioctl.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_ioctl.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_read.o: ../ux_host_class_dpump_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_class_dpump_write.o: ../ux_host_class_dpump_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_class_dpump_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_bandwidth_check.o: ../ux_host_stack_bandwidth_check.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_bandwidth_check.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_bandwidth_claim.o: ../ux_host_stack_bandwidth_claim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_bandwidth_claim.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_bandwidth_release.o: ../ux_host_stack_bandwidth_release.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_bandwidth_release.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_call.o: ../ux_host_stack_class_call.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_call.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_device_scan.o: ../ux_host_stack_class_device_scan.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_device_scan.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_get.o: ../ux_host_stack_class_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_instance_create.o: ../ux_host_stack_class_instance_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_instance_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_instance_destroy.o: ../ux_host_stack_class_instance_destroy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_instance_destroy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_instance_get.o: ../ux_host_stack_class_instance_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_instance_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_instance_verify.o: ../ux_host_stack_class_instance_verify.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_instance_verify.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_interface_scan.o: ../ux_host_stack_class_interface_scan.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_interface_scan.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_class_register.o: ../ux_host_stack_class_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_class_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_configuration_descriptor_parse.o: ../ux_host_stack_configuration_descriptor_parse.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_configuration_descriptor_parse.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_configuration_enumerate.o: ../ux_host_stack_configuration_enumerate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_configuration_enumerate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_configuration_instance_create.o: ../ux_host_stack_configuration_instance_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_configuration_instance_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_configuration_instance_delete.o: ../ux_host_stack_configuration_instance_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_configuration_instance_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_configuration_interface_get.o: ../ux_host_stack_configuration_interface_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_configuration_interface_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_configuration_set.o: ../ux_host_stack_configuration_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_configuration_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_delay_ms.o: ../ux_host_stack_delay_ms.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_delay_ms.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_address_set.o: ../ux_host_stack_device_address_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_address_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_configuration_get.o: ../ux_host_stack_device_configuration_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_configuration_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_configuration_reset.o: ../ux_host_stack_device_configuration_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_configuration_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_configuration_select.o: ../ux_host_stack_device_configuration_select.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_configuration_select.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_descriptor_read.o: ../ux_host_stack_device_descriptor_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_descriptor_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_get.o: ../ux_host_stack_device_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_remove.o: ../ux_host_stack_device_remove.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_remove.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_device_resources_free.o: ../ux_host_stack_device_resources_free.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_device_resources_free.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_endpoint_instance_create.o: ../ux_host_stack_endpoint_instance_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_endpoint_instance_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_endpoint_instance_delete.o: ../ux_host_stack_endpoint_instance_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_endpoint_instance_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_endpoint_reset.o: ../ux_host_stack_endpoint_reset.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_endpoint_reset.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_endpoint_transfer_abort.o: ../ux_host_stack_endpoint_transfer_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_endpoint_transfer_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_enum_thread_entry.o: ../ux_host_stack_enum_thread_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_enum_thread_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_hcd_register.o: ../ux_host_stack_hcd_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_hcd_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_hcd_thread_entry.o: ../ux_host_stack_hcd_thread_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_hcd_thread_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_hcd_transfer_request.o: ../ux_host_stack_hcd_transfer_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_hcd_transfer_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_hnp_polling_thread_entry.o: ../ux_host_stack_hnp_polling_thread_entry.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_hnp_polling_thread_entry.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_initialize.o: ../ux_host_stack_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_interface_endpoint_get.o: ../ux_host_stack_interface_endpoint_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_interface_endpoint_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_interface_instance_create.o: ../ux_host_stack_interface_instance_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_interface_instance_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_interface_instance_delete.o: ../ux_host_stack_interface_instance_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_interface_instance_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_interface_set.o: ../ux_host_stack_interface_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_interface_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_interface_setting_select.o: ../ux_host_stack_interface_setting_select.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_interface_setting_select.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_interfaces_scan.o: ../ux_host_stack_interfaces_scan.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_interfaces_scan.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_new_configuration_create.o: ../ux_host_stack_new_configuration_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_new_configuration_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_new_device_create.o: ../ux_host_stack_new_device_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_new_device_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_new_device_get.o: ../ux_host_stack_new_device_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_new_device_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_new_endpoint_create.o: ../ux_host_stack_new_endpoint_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_new_endpoint_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_new_interface_create.o: ../ux_host_stack_new_interface_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_new_interface_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_rh_change_process.o: ../ux_host_stack_rh_change_process.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_rh_change_process.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_rh_device_extraction.o: ../ux_host_stack_rh_device_extraction.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_rh_device_extraction.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_rh_device_insertion.o: ../ux_host_stack_rh_device_insertion.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_rh_device_insertion.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_role_swap.o: ../ux_host_stack_role_swap.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_role_swap.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_transfer_request.o: ../ux_host_stack_transfer_request.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_transfer_request.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_host_stack_transfer_request_abort.o: ../ux_host_stack_transfer_request_abort.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_host_stack_transfer_request_abort.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_system_error_handler.o: ../ux_system_error_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_system_error_handler.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_system_initialize.o: ../ux_system_initialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_system_initialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_system_uninitialize.o: ../ux_system_uninitialize.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_system_uninitialize.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_trace_event_insert.o: ../ux_trace_event_insert.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_trace_event_insert.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_trace_event_update.o: ../ux_trace_event_update.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_trace_event_update.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_trace_object_register.o: ../ux_trace_object_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_trace_object_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_trace_object_unregister.o: ../ux_trace_object_unregister.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_trace_object_unregister.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_debug_callback_register.o: ../ux_utility_debug_callback_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_debug_callback_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_debug_log.o: ../ux_utility_debug_log.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_debug_log.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_delay_ms.o: ../ux_utility_delay_ms.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_delay_ms.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_descriptor_pack.o: ../ux_utility_descriptor_pack.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_descriptor_pack.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_descriptor_parse.o: ../ux_utility_descriptor_parse.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_descriptor_parse.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_error_callback_register.o: ../ux_utility_error_callback_register.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_error_callback_register.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_event_flags_create.o: ../ux_utility_event_flags_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_event_flags_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_event_flags_delete.o: ../ux_utility_event_flags_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_event_flags_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_event_flags_get.o: ../ux_utility_event_flags_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_event_flags_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_event_flags_set.o: ../ux_utility_event_flags_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_event_flags_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_long_get.o: ../ux_utility_long_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_long_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_long_get_big_endian.o: ../ux_utility_long_get_big_endian.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_long_get_big_endian.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_long_put.o: ../ux_utility_long_put.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_long_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_long_put_big_endian.o: ../ux_utility_long_put_big_endian.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_long_put_big_endian.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_allocate.o: ../ux_utility_memory_allocate.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_allocate.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_allocate_add_safe.o: ../ux_utility_memory_allocate_add_safe.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_allocate_add_safe.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_allocate_mulc_safe.o: ../ux_utility_memory_allocate_mulc_safe.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_allocate_mulc_safe.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_allocate_mulv_safe.o: ../ux_utility_memory_allocate_mulv_safe.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_allocate_mulv_safe.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_compare.o: ../ux_utility_memory_compare.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_compare.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_copy.o: ../ux_utility_memory_copy.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_copy.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_free.o: ../ux_utility_memory_free.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_free.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_free_block_best_get.o: ../ux_utility_memory_free_block_best_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_free_block_best_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_memory_set.o: ../ux_utility_memory_set.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_memory_set.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_mutex_create.o: ../ux_utility_mutex_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_mutex_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_mutex_delete.o: ../ux_utility_mutex_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_mutex_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_mutex_off.o: ../ux_utility_mutex_off.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_mutex_off.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_mutex_on.o: ../ux_utility_mutex_on.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_mutex_on.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_pci_class_scan.o: ../ux_utility_pci_class_scan.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_pci_class_scan.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_pci_read.o: ../ux_utility_pci_read.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_pci_read.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_pci_write.o: ../ux_utility_pci_write.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_pci_write.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_physical_address.o: ../ux_utility_physical_address.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_physical_address.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_semaphore_create.o: ../ux_utility_semaphore_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_semaphore_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_semaphore_delete.o: ../ux_utility_semaphore_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_semaphore_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_semaphore_get.o: ../ux_utility_semaphore_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_semaphore_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_semaphore_put.o: ../ux_utility_semaphore_put.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_semaphore_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_set_interrupt_handler.o: ../ux_utility_set_interrupt_handler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_set_interrupt_handler.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_short_get.o: ../ux_utility_short_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_short_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_short_get_big_endian.o: ../ux_utility_short_get_big_endian.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_short_get_big_endian.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_short_put.o: ../ux_utility_short_put.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_short_put.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_short_put_big_endian.o: ../ux_utility_short_put_big_endian.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_short_put_big_endian.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_string_length_check.o: ../ux_utility_string_length_check.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_string_length_check.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_string_length_get.o: ../ux_utility_string_length_get.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_string_length_get.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_string_to_unicode.o: ../ux_utility_string_to_unicode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_string_to_unicode.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_create.o: ../ux_utility_thread_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_delete.o: ../ux_utility_thread_delete.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_delete.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_identify.o: ../ux_utility_thread_identify.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_identify.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_relinquish.o: ../ux_utility_thread_relinquish.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_relinquish.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_resume.o: ../ux_utility_thread_resume.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_resume.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_schedule_other.o: ../ux_utility_thread_schedule_other.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_schedule_other.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_sleep.o: ../ux_utility_thread_sleep.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_sleep.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_thread_suspend.o: ../ux_utility_thread_suspend.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_thread_suspend.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_timer_create.o: ../ux_utility_timer_create.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_timer_create.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_unicode_to_string.o: ../ux_utility_unicode_to_string.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_unicode_to_string.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ux_utility_virtual_address.o: ../ux_utility_virtual_address.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUX_DISABLE_INCLUDE_SOURCE_CODE -c -I"../../tx" -I"../../fx" -I"../../ux" -I"../../nxd" -I"../../stm32f7xx_library" -Og -ffunction-sections -fdata-sections -Wall -Wno-maybe-uninitialized -fstack-usage -MMD -MP -MF"ux_utility_virtual_address.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

