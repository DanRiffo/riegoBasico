################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src/utility/twi.c 

C_DEPS += \
./libraries/Wire/src/utility/twi.c.d 

LINK_OBJ += \
./libraries/Wire/src/utility/twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/src/utility/twi.c.o: /home/alucard/Downloads/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src/utility/twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/home/alucard/Downloads/arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/variants/standard" -I"/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -I"/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/libraries/Streaming/5.0.0/src" -I"/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0" -I"/home/alucard/Downloads/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/home/alucard/Downloads/arduino/proyectos/riegoBasico/libraries/DS1302RTC" -I"/home/alucard/Downloads/arduino/proyectos/riegoBasico/libraries/Low-Power-master" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


