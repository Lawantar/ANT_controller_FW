################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/modbus/tcp/mbtcp.c 

C_DEPS += \
./Modules/modbus/tcp/mbtcp.d 

OBJS += \
./Modules/modbus/tcp/mbtcp.o 


# Each subdirectory must supply rules for building sources it contributes
Modules/modbus/tcp/%.o Modules/modbus/tcp/%.su Modules/modbus/tcp/%.cyclo: ../Modules/modbus/tcp/%.c Modules/modbus/tcp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/ascii" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/functions" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/include" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/port" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/rtu" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/tcp" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules-2f-modbus-2f-tcp

clean-Modules-2f-modbus-2f-tcp:
	-$(RM) ./Modules/modbus/tcp/mbtcp.cyclo ./Modules/modbus/tcp/mbtcp.d ./Modules/modbus/tcp/mbtcp.o ./Modules/modbus/tcp/mbtcp.su

.PHONY: clean-Modules-2f-modbus-2f-tcp

