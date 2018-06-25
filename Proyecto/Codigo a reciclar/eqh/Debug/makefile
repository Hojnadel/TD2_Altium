################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include my_freertos/subdir.mk
-include freertos/src/subdir.mk
-include efectos/subdir.mk
-include display/subdir.mk
-include adc_dac/subdir.mk
-include SD/subdir.mk
-include FFT/subdir.mk
-include EEPROM/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: eqh.axf

# Tool invocations
eqh.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\pablo\Desktop\eqh_lpc\fw\fft_vieja\src" -L"C:\Users\pablo\Desktop\eqh_lpc\fw\lpc_board_nxp_lpcxpresso_1769\Debug" -L"C:\Users\pablo\Desktop\eqh_lpc\fw\lpc_chip_175x_6x\Debug" -L"C:\Users\pablo\Desktop\eqh_lpc\fw\CMSIS_DSPLIB_CM3\lib" -Xlinker -Map="eqh.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "eqh_Debug.ld" -o "eqh.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) eqh.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "eqh.axf"; # arm-none-eabi-objcopy -v -O binary "eqh.axf" "eqh.bin" ; # checksum -p LPC1769 -d "eqh.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
