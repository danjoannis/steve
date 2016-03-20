################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../commands.c \
../i2c.c \
../main.c \
../motors.c \
../mpu9250.c \
../mpu9255.c \
../uart.c \
../ultrasonic.c \
../util.c 

OBJS += \
./adc.o \
./commands.o \
./i2c.o \
./main.o \
./motors.o \
./mpu9250.o \
./mpu9255.o \
./uart.o \
./ultrasonic.o \
./util.o 

C_DEPS += \
./adc.d \
./commands.d \
./i2c.d \
./main.d \
./motors.d \
./mpu9250.d \
./mpu9255.d \
./uart.d \
./ultrasonic.d \
./util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


