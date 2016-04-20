## Local build configuration
## Parameters configured here will override default and ENV values.
## Uncomment and change examples:

#Add your source directories here separated by space
MODULES = app

## ESP_HOME sets the path where ESP tools and SDK are located.
## Windows:
# ESP_HOME = c:/Espressif

## MacOS / Linux:
ESP_HOME = $(HOME)/git/esp-open-sdk

## SMING_HOME sets the path where Sming framework is located.
## Windows:
# SMING_HOME = c:/tools/sming/Sming 

# MacOS / Linux
SMING_HOME = $(HOME)/git/Sming/Sming

## COM port parameter is reqruied to flash firmware correctly.
## Windows: 
# COM_PORT = COM3

# MacOS / Linux:
COM_PORT = /dev/ttyAMA0

# Com port speed (Program transfer)
COM_SPEED	= 115200

# Com port speed serial (& python r/w)
COM_SPEED_SERIAL	= 9600

# SPIFFs Location
SPIFF_FILES = web/build

## Configure flash parameters (for ESP12-E and other new boards):
# SPI_MODE = dio

## Altri parametri
#RBOOT_ENABLED ?= 0
#SPI_SPEED ?= 40
#SPI_MODE ?= qio
#SPI_SIZE ?= 512K