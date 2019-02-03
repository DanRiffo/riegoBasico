################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/Wire/src/utility/subdir.mk
-include libraries/Wire/src/subdir.mk
-include libraries/Time/subdir.mk
-include libraries/SPI/src/subdir.mk
-include libraries/SD/src/utility/subdir.mk
-include libraries/SD/src/subdir.mk
-include libraries/Low-Power-master/subdir.mk
-include libraries/LiquidCrystal/src/subdir.mk
-include libraries/DS1302RTC/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/media/Datos/Descargas/arduino/proyectos/riegoBasico/Release/arduino.ar \

ELF += \
riegoBasico.elf \

HEX += \
riegoBasico.hex \


# All Target
all: riegoBasico

# Tool invocations
riegoBasico: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/media/Datos/Descargas/arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-size" -A "/media/Datos/Descargas/arduino/proyectos/riegoBasico/Release/riegoBasico.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/media/Datos/Descargas/arduino/proyectos/riegoBasico/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/media/Datos/Descargas/arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs     /media/Datos/Descargas/arduino/proyectos/riegoBasico/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

riegoBasico.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/media/Datos/Descargas/arduino/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p  -o "/media/Datos/Descargas/arduino/proyectos/riegoBasico/Release/riegoBasico.elf"   $(LINK_OBJ)   /media/Datos/Descargas/arduino/proyectos/riegoBasico/Release/arduino.ar  "-L/media/Datos/Descargas/arduino/proyectos/riegoBasico/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

riegoBasico.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
