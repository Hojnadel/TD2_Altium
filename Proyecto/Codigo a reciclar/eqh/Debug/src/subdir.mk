################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/eqh.c \
../src/init.c \
../src/sysinit.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/eqh.o \
./src/init.o \
./src/sysinit.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/eqh.d \
./src/init.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__NEWLIB__ -I"C:\Users\pablo\Desktop\eqh_lpc\fw\fft_vieja\src" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\freertos\inc" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\freertos\src" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\adc_dac" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\display" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\EEPROM" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\efectos" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\FFT" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\gpio" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\inc" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\my_freertos" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\SD" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\eqh\inc" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\lpc_chip_175x_6x\inc" -I"C:\Users\pablo\Desktop\eqh_lpc\fw\CMSIS_DSPLIB_CM3\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


