PROGRAM_NAME = default
SRC_DIR = src
BUILD_DIR = build
MCU = attiny85
AVRDUDE_PARTNUM = t85

all: $(PROGRAM_NAME)

# Create the build directory
$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR)

$(PROGRAM_NAME): $(BUILD_DIR)
	avr-gcc -mmcu=$(MCU) -Wall -Os -o $(BUILD_DIR)/$(PROGRAM_NAME).elf $(SRC_DIR)/$(PROGRAM_NAME).c
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/$(PROGRAM_NAME).elf $(BUILD_DIR)/$(PROGRAM_NAME).hex

flash: $(PROGRAM_NAME)
	avrdude -c usbasp-clone -p $(AVRDUDE_PARTNUM) -U flash:w:$(BUILD_DIR)/$(PROGRAM_NAME).hex

# Remove build directory with all built files
clean:
	rm -rf $(BUILD_DIR) 
