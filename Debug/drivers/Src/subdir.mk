################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32_gpio.c \
../drivers/Src/stm32_i2c.c \
../drivers/Src/stm32_rcc.c \
../drivers/Src/stm32_spi.c \
../drivers/Src/stm32_uart.c 

OBJS += \
./drivers/Src/stm32_gpio.o \
./drivers/Src/stm32_i2c.o \
./drivers/Src/stm32_rcc.o \
./drivers/Src/stm32_spi.o \
./drivers/Src/stm32_uart.o 

C_DEPS += \
./drivers/Src/stm32_gpio.d \
./drivers/Src/stm32_i2c.d \
./drivers/Src/stm32_rcc.d \
./drivers/Src/stm32_spi.d \
./drivers/Src/stm32_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/%.o drivers/Src/%.su: ../drivers/Src/%.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/000000NHOM/DRONE/zzzzzzDriver_ThoNV/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-Src

clean-drivers-2f-Src:
	-$(RM) ./drivers/Src/stm32_gpio.d ./drivers/Src/stm32_gpio.o ./drivers/Src/stm32_gpio.su ./drivers/Src/stm32_i2c.d ./drivers/Src/stm32_i2c.o ./drivers/Src/stm32_i2c.su ./drivers/Src/stm32_rcc.d ./drivers/Src/stm32_rcc.o ./drivers/Src/stm32_rcc.su ./drivers/Src/stm32_spi.d ./drivers/Src/stm32_spi.o ./drivers/Src/stm32_spi.su ./drivers/Src/stm32_uart.d ./drivers/Src/stm32_uart.o ./drivers/Src/stm32_uart.su

.PHONY: clean-drivers-2f-Src

