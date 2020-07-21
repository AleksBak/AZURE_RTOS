################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
sample_usbx_host_mass_storage.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
sample_usbx_host_mass_storage.list \

OBJCOPY_BIN += \
sample_usbx_host_mass_storage.bin \


# All Target
all: sample_usbx_host_mass_storage.elf secondary-outputs

# Tool invocations
sample_usbx_host_mass_storage.elf: $(OBJS) $(USER_OBJS) ../../common/STM32F746NGHX_FLASH.ld
	arm-none-eabi-gcc -o "sample_usbx_host_mass_storage.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"../../common/STM32F746NGHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="sample_usbx_host_mass_storage.map" -Wl,--gc-sections -static -L"../../stm32f7xx_library/Debug" -L"../../ux/Debug" -L"../../fx/Debug" -L"../../tx/Debug" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

sample_usbx_host_mass_storage.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "sample_usbx_host_mass_storage.list"
	@echo 'Finished building: $@'
	@echo ' '

sample_usbx_host_mass_storage.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "sample_usbx_host_mass_storage.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
