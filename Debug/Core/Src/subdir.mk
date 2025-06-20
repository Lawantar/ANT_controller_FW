################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/inertia_math.c \
../Core/Src/main.c \
../Core/Src/mbdata.c \
../Core/Src/sensors.c \
../Core/Src/stm32g0xx_hal_msp.c \
../Core/Src/stm32g0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g0xx.c 

C_DEPS += \
./Core/Src/inertia_math.d \
./Core/Src/main.d \
./Core/Src/mbdata.d \
./Core/Src/sensors.d \
./Core/Src/stm32g0xx_hal_msp.d \
./Core/Src/stm32g0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g0xx.d 

OBJS += \
./Core/Src/inertia_math.o \
./Core/Src/main.o \
./Core/Src/mbdata.o \
./Core/Src/sensors.o \
./Core/Src/stm32g0xx_hal_msp.o \
./Core/Src/stm32g0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g0xx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/inertia_math.o: ../Core/Src/inertia_math.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/functions" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/include" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/port" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/rtu" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G031xx -c -I../Core/Inc -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/functions" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/include" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/port" -I"C:/Users/Lawantar/STM32CubeIDE/workspace_1.15.1/Ant-controller/Modules/modbus/rtu" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/inertia_math.cyclo ./Core/Src/inertia_math.d ./Core/Src/inertia_math.o ./Core/Src/inertia_math.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mbdata.cyclo ./Core/Src/mbdata.d ./Core/Src/mbdata.o ./Core/Src/mbdata.su ./Core/Src/sensors.cyclo ./Core/Src/sensors.d ./Core/Src/sensors.o ./Core/Src/sensors.su ./Core/Src/stm32g0xx_hal_msp.cyclo ./Core/Src/stm32g0xx_hal_msp.d ./Core/Src/stm32g0xx_hal_msp.o ./Core/Src/stm32g0xx_hal_msp.su ./Core/Src/stm32g0xx_it.cyclo ./Core/Src/stm32g0xx_it.d ./Core/Src/stm32g0xx_it.o ./Core/Src/stm32g0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g0xx.cyclo ./Core/Src/system_stm32g0xx.d ./Core/Src/system_stm32g0xx.o ./Core/Src/system_stm32g0xx.su

.PHONY: clean-Core-2f-Src

