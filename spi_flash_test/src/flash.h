#ifndef		__FLASH_H
#define		__FLASH_H

#include <stdint.h>

enum {
	SPI_CMD_ENABLE_RESET	= 0x66,
	SPI_CMD_GET_ID			= 0x90,
	SPI_CMD_RESET			= 0x99,
};

typedef struct id {
	uint8_t		manufacturer_id;
	uint8_t		device_id;
} id_t;


id_t flash_read_id();

#endif
