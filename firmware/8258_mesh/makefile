################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include vendor/user_app/subdir.mk
-include vendor/mesh/subdir.mk
-include vendor/common/subdir.mk
-include vendor/common/nl_api/subdir.mk
-include vendor/common/mi_api/subdir.mk
-include vendor/common/mi_api/mijia_ble_api/subdir.mk
-include vendor/common/mi_api/mi_vendor/subdir.mk
-include vendor/common/mi_api/libs/third_party/micro-ecc/subdir.mk
-include vendor/common/mi_api/libs/subdir.mk
-include vendor/Training_CCT/subdir.mk
-include vendor/RD_Type_Device/subdir.mk
-include vendor/RD_Mess_Data/subdir.mk
-include vendor/RD_Add_RoomSceen/subdir.mk
-include proj/mcu_spec/subdir.mk
-include proj/mcu/subdir.mk
-include proj/drivers/subdir.mk
-include proj/common/subdir.mk
-include proj/app/subdir.mk
-include drivers/8258/subdir.mk
-include drivers/8258/flash/subdir.mk
-include boot/8258/subdir.mk
-include 8269_mesh_master_dongle/vendor/8267_master_kma_dongle/subdir.mk
-include 8269_mesh_master_dongle/proj/mcu_spec/subdir.mk
-include 8269_mesh_master_dongle/proj/mcu/subdir.mk
-include 8269_mesh_master_dongle/proj/drivers/subdir.mk
-include 8269_mesh_master_dongle/proj/common/subdir.mk
-include 8269_mesh_master_dongle/proj/app/subdir.mk
-include 8269_mesh_master_dongle/drivers/8258/subdir.mk
-include 8269_mesh_master_dongle/drivers/8258/flash/subdir.mk
-include 8269_mesh_master_dongle/subdir.mk
-include 8269_mesh_master_dongle/boot/8258/subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
8258_mesh.lst \

FLASH_IMAGE += \

SIZEDUMMY += \
sizedummy \


# All Target
all: pre-build main-build

# Main-build Target
main-build: firmware.elf secondary-outputs

# Tool invocations
firmware.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections -L"C:\Users\NV-Smart03\Downloads\RD_CTT_v3\firmware\proj_lib" -T ../boot.link -o"firmware.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

8258_mesh.lst: firmware.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S firmware.elf  >"8258_mesh.lst"
	@echo 'Finished building: $@'
	@echo ' '

: firmware.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy -O binary firmware.elf
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: firmware.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t firmware.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(LST)$(SIZEDUMMY) firmware.elf
	-@echo ' '

pre-build:
	-"C:\Users\NV-Smart03\Downloads\RD_CTT_v3\firmware/getver.sh"
	-@echo ' '

post-build:
	-"C:\Users\NV-Smart03\Downloads\RD_CTT_v3\firmware/tl_check_fw.sh"   8258_mesh   firmware
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
