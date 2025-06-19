################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/port/mt_port.c \
../Modules/modbus/port/portevent.c \
../Modules/modbus/port/portserial.c \
../Modules/modbus/port/porttimer.c 

C_DEPS += \
./Modules/modbus/port/mt_port.d \
./Modules/modbus/port/portevent.d \
./Modules/modbus/port/portserial.d \
./Modules/modbus/port/porttimer.d 

OBJS += \
./Modules/modbus/port/mt_port.o \
./Modules/modbus/port/portevent.o \
./Modules/modbus/port/portserial.o \
./Modules/modbus/port/porttimer.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/port/%.o Modules/modbus/port/%.su Modules/modbus/port/%.cyclo: ../Modules/modbus/port/%.c Modules/modbus/port/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/functions" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/include" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/port" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/rtu" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-port

clean-Modules-2f-modbus-2f-port:
	-$(RM) ./Modules/modbus/port/mt_port.cyclo ./Modules/modbus/port/mt_port.d ./Modules/modbus/port/mt_port.o ./Modules/modbus/port/mt_port.su ./Modules/modbus/port/portevent.cyclo ./Modules/modbus/port/portevent.d ./Modules/modbus/port/portevent.o ./Modules/modbus/port/portevent.su ./Modules/modbus/port/portserial.cyclo ./Modules/modbus/port/portserial.d ./Modules/modbus/port/portserial.o ./Modules/modbus/port/portserial.su ./Modules/modbus/port/porttimer.cyclo ./Modules/modbus/port/porttimer.d ./Modules/modbus/port/porttimer.o ./Modules/modbus/port/porttimer.su

.PHONY: clean-Modules-2f-modbus-2f-port

