PROJECT_DIR   = $(shell pwd)
ARDUINO_DIR   = /usr/share/arduino
ARDMK_DIR     = /usr/share/arduino
AVR_TOOLS_DIR = /usr
AVRDUDE_CONF=/etc/avrdude.conf

ARDUINO_LIBS = SPI Adafruit_DotStar
MONITOR_PORT = /dev/ttyUSB0
#BOARD_TAG = pro5v328
BOARD_TAG = mega2560

USER_LIB_PATH := $(realpath $(PROJECT_DIR)/..)

include  /usr/share/arduino/Arduino.mk

# make > out 2>&1
