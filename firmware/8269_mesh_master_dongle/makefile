################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include vendor/8267_master_kma_dongle/subdir.mk
-include proj/mcu_spec/subdir.mk
-include proj/mcu/subdir.mk
-include proj/drivers/subdir.mk
-include proj/common/subdir.mk
-include proj/app/subdir.mk
-include drivers/8258/subdir.mk
-include drivers/8258/flash/subdir.mk
-include boot/8258/subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
8267_master_kma_dongle.lst \

FLASH_IMAGE += \

SIZEDUMMY += \
sizedummy \


# All Target
all: pre-build main-build

# Main-build Target
main-build: CCT_v.1.0.elf secondary-outputs

# Tool invocations
CCT_v.1.0.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections -L"D:\RD_CODE\CCT_v.1.0\firmware\proj_lib" -T ../boot.link -o"CCT_v.1.0.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

8267_master_kma_dongle.lst: CCT_v.1.0.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S CCT_v.1.0.elf  >"8267_master_kma_dongle.lst"
	@echo 'Finished building: $@'
	@echo ' '

: CCT_v.1.0.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy CCT_v.1.0.elf
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CCT_v.1.0.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t CCT_v.1.0.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(LST)$(SIZEDUMMY) CCT_v.1.0.elf
	-@echo ' '

pre-build:
	-"D:\RD_CODE\CCT_v.1.0\firmware/getver.sh"
	-@echo ' '

post-build:
	-"D:\RD_CODE\CCT_v.1.0\firmware/tl_check_fw.sh"   8269_mesh_master_dongle   CCT_v.1.0
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
