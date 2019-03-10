MCU = atmega328p
F_CPU = 16000000
CC = avr-gcc
CFLAGS= -O2 -Wall -std=gnu11 -mmcu=$(MCU)
CPPFLAGS=-DF_CPU=$(F_CPU)L -I/usr/share/arduino/hardware/arduino/cores/arduino -I/usr/share/arduino/hardware/arduino/variants/standard
OBJCOPY=avr-objcopy

CMD_FLASH=avrdude
MCU1 = ATMEGA328P
DEVPORT = /dev/ttyUSB0
BAUDRATE=57600

FNAME = hall

.PHONY: default
default : EXE_FILE HEX_FILE flash

EXE_FILE: $(FNAME).c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $(FNAME)
HEX_FILE: $(FNAME)
	$(OBJCOPY) -O ihex $< $(FNAME).hex
flash : $(FNAME).hex
	$(CMD_FLASH) -F -V -c arduino -p $(MCU1) -P $(DEVPORT) -b $(BAUDRATE) -U $@:w:$<
clean:
	rm $(FNAME).hex $(FNAME)
# avrdude.conf -v -v -v -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:/tmp/build1674805407551196116.tmp/Blink2.cpp.hex:i
