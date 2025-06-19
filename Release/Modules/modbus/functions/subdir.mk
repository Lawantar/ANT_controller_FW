################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/functions/mbfunccoils.c \
../Modules/modbus/functions/mbfuncdiag.c \
../Modules/modbus/functions/mbfuncdisc.c \
../Modules/modbus/functions/mbfuncholding.c \
../Modules/modbus/functions/mbfuncinput.c \
../Modules/modbus/functions/mbfuncother.c \
../Modules/modbus/functions/mbutils.c 

C_DEPS += \
./Modules/modbus/functions/mbfunccoils.d \
./Modules/modbus/functions/mbfuncdiag.d \
./Modules/modbus/functions/mbfuncdisc.d \
./Modules/modbus/functions/mbfuncholding.d \
./Modules/modbus/functions/mbfuncinput.d \
./Modules/modbus/functions/mbfuncother.d \
./Modules/modbus/functions/mbutils.d 

OBJS += \
./Modules/modbus/functions/mbfunccoils.o \
./Modules/modbus/functions/mbfuncdiag.o \
./Modules/modbus/functions/mbfuncdisc.o \
./Modules/modbus/functions/mbfuncholding.o \
./Modules/modbus/functions/mbfuncinput.o \
./Modules/modbus/functions/mbfuncother.o \
./Modules/modbus/functions/mbutils.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/functions/%.o Modules/modbus/functions/%.su Modules/modbus/functions/%.cyclo: ../Modules/modbus/functions/%.c Modules/modbus/functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-functions

clean-Modules-2f-modbus-2f-functions:
	-$(RM) ./Modules/modbus/functions/mbfunccoils.cyclo ./Modules/modbus/functions/mbfunccoils.d ./Modules/modbus/functions/mbfunccoils.o ./Modules/modbus/functions/mbfunccoils.su ./Modules/modbus/functions/mbfuncdiag.cyclo ./Modules/modbus/functions/mbfuncdiag.d ./Modules/modbus/functions/mbfuncdiag.o ./Modules/modbus/functions/mbfuncdiag.su ./Modules/modbus/functions/mbfuncdisc.cyclo ./Modules/modbus/functions/mbfuncdisc.d ./Modules/modbus/functions/mbfuncdisc.o ./Modules/modbus/functions/mbfuncdisc.su ./Modules/modbus/functions/mbfuncholding.cyclo ./Modules/modbus/functions/mbfuncholding.d ./Modules/modbus/functions/mbfuncholding.o ./Modules/modbus/functions/mbfuncholding.su ./Modules/modbus/functions/mbfuncinput.cyclo ./Modules/modbus/functions/mbfuncinput.d ./Modules/modbus/functions/mbfuncinput.o ./Modules/modbus/functions/mbfuncinput.su ./Modules/modbus/functions/mbfuncother.cyclo ./Modules/modbus/functions/mbfuncother.d ./Modules/modbus/functions/mbfuncother.o ./Modules/modbus/functions/mbfuncother.su ./Modules/modbus/functions/mbutils.cyclo ./Modules/modbus/functions/mbutils.d ./Modules/modbus/functions/mbutils.o ./Modules/modbus/functions/mbutils.su

.PHONY: clean-Modules-2f-modbus-2f-functions

