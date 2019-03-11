# For compling sketch

MCU = atmega328p
F_CPU = 16000000

CC = /usr/bin/avr-gcc
CXX = /usr/bin/avr-g++
OBJCOPY=/usr/bin/avr-objcopy
DUDE=/usr/bin/avr-dude

# Pre-processor
CPPFLAGS=-DF_CPU=$(F_CPU)L

CFLAGS= -Os -g -Wall -std=gnu11 -mmcu=$(MCU) -DARDUINO=105 -D__PROG_TYPES_COMPAT__
CXXFLAGS= -Os -g -Wall -mmcu=$(MCU) -DARDUINO=105 -D__PROG_TYPES_COMPAT__

LDFLAGS     = -Os -Wl,--gc-sections -mmcu=$(MCU) # .a -L/XXX/.tmp -lm

MCU1 = ATMEGA328P
DEVPORT = /dev/ttyUSB0
BAUDRATE=57600

TARGET=strandtest

# Compile
# avr-gcc -g -Os -mmcu=atmega8 -c demo.c
# Link
# avr-gcc -g -mmcu=atmega8 -o demo.elf demo.o

# avr-objdump -h -S demo.elf > demo.lst

# /usr/share/arduino/hardware/arduino/cores/arduino/main.cpp

all: $(TARGET).hex

clean:
	rm -f $(TARGET).elf *.o *.hex

%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c  $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(TARGET).elf: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJ_FILES)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $(TARGET).elf eeprom.hex

upload: $(TARGET).hex
	$(DUDE) $(PGMER) -U flash:w:main.hex

size: main.elf
	avr-size --format=avr --mcu=$(MCU) main.elf

# Pull .txt and .data segments into .hex
# avr-objcopy -j .text -j .data -O ihex demo.elf demo.hex

# Program EEPROM
# avr-objcopy -j .eeprom --change-section-lma .eeprom=0 -O ihex demo.elf demo_eeprom.hex
# it is empty

# avr-objcopy -O ihex -R .eeprom /tmp/build4470352176114379890.tmp/strandtest.cpp.elf /tmp/build4470352176114379890.tmp/strandtest.cpp.hex
