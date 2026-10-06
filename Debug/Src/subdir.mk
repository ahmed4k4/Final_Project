################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/APP_Program.c \
../Src/DIO_Program.c \
../Src/EXTI_Program.c \
../Src/LCD_Program.c \
../Src/RTOS_Program.c \
../Src/TIMER_Program.c \
../Src/UART_Program.c \
../Src/main.c 

OBJS += \
./Src/APP_Program.o \
./Src/DIO_Program.o \
./Src/EXTI_Program.o \
./Src/LCD_Program.o \
./Src/RTOS_Program.o \
./Src/TIMER_Program.o \
./Src/UART_Program.o \
./Src/main.o 

C_DEPS += \
./Src/APP_Program.d \
./Src/DIO_Program.d \
./Src/EXTI_Program.d \
./Src/LCD_Program.d \
./Src/RTOS_Program.d \
./Src/TIMER_Program.d \
./Src/UART_Program.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


