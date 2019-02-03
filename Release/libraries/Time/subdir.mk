################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0/DateStrings.cpp \
/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0/Time.cpp 

LINK_OBJ += \
./libraries/Time/DateStrings.cpp.o \
./libraries/Time/Time.cpp.o 

CPP_DEPS += \
./libraries/Time/DateStrings.cpp.d \
./libraries/Time/Time.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Time/DateStrings.cpp.o: /media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0/DateStrings.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/media/Datos/Descargas/arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/variants/standard" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Streaming/5.0.0/src" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/media/Datos/Descargas/arduino/proyectos/riegoBasico/libraries/DS1302RTC" -I"/media/Datos/Descargas/arduino/proyectos/riegoBasico/libraries/Low-Power-master" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/SD/1.2.3/src" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/Time/Time.cpp.o: /media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0/Time.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/media/Datos/Descargas/arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR     -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/variants/standard" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/LiquidCrystal/1.0.7/src" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Streaming/5.0.0/src" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/Time/1.5.0" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/media/Datos/Descargas/arduino/proyectos/riegoBasico/libraries/DS1302RTC" -I"/media/Datos/Descargas/arduino/proyectos/riegoBasico/libraries/Low-Power-master" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/libraries/SD/1.2.3/src" -I"/media/Datos/Descargas/arduino/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.23/libraries/SPI/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


