MCU = atmega328p
F_CPU = 16000000

CC = avr-gcc
CFLAGS= -Os -g -Wall -std=gnu11 -mmcu=$(MCU)
CPPFLAGS=-DF_CPU=$(F_CPU)L

LDFLAGS     = -g -mmcu=$(MCU) -lm -Wl,--gc-sections -Os

OBJCOPY=avr-objcopy

CMD_FLASH=avrdude
MCU1 = ATMEGA328P
DEVPORT = /dev/ttyUSB0
BAUDRATE=57600


# Compile
# avr-gcc -g -Os -mmcu=atmega8 -c demo.c
# Link
# avr-gcc -g -mmcu=atmega8 -o demo.elf demo.o

# avr-objdump -h -S demo.elf > demo.lst


#%.o: %.c
#$(CC) -c

# Pull .txt and .data segments into .hex
# avr-objcopy -j .text -j .data -O ihex demo.elf demo.hex

# Program EEPROM
# avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex demo.elf demo_eeprom.hex
# it is empty

# avr-objcopy -O ihex -R .eeprom /tmp/build4470352176114379890.tmp/strandtest.cpp.elf /tmp/build4470352176114379890.tmp/strandtest.cpp.hex
