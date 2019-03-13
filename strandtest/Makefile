MCU = atmega328p
F_CPU = 16000000
CC = avr-gcc

CPPFLAGS=-DF_CPU=$(F_CPU)L
CFLAGS= -Os -g -Wall -std=gnu11 -mmcu=$(MCU)
LDFLAGS = -g -mmcu=$(MCU) -lm -Wl,--gc-sections -Os

OBJCOPY=avr-objcopy

ARDUINO_LIBS += Wire \
SPI \


USER_LIB_PATH+=.

CORE_LIB_SRC =  \
	$(ARDUINO)/pins_arduino.c \
	$(ARDUINO)/wiring.c \
	$(ARDUINO)/wiring_analog.c \
	$(ARDUINO)/wiring_digital.c \
	$(ARDUINO)/wiring_pulse.c \
	$(ARDUINO)/wiring_shift.c \
	$(ARDUINO)/WInterrupts.c


#avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=105 -D__PROG_TYPES_COMPAT__

# -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/hardware/arduino/variants/standard -I/root/sketchbook/libraries/AdafruitDotStarMaster -I/usr/share/arduino/libraries/SPI

CMD_FLASH=avrdude
MCU1 = ATMEGA328P
DEVPORT = /dev/ttyUSB0
BAUDRATE=57600
