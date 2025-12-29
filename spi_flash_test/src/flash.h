#ifndef		__FLASH_H
#define		__FLASH_H

#include <stdint.h>

enum {
	FLASH_CMD_READ_STATUS_REG1		= 0x05,
	FLASH_CMD_READ_STATUS_REG2		= 0x35,
	FLASH_CMD_ENABLE_RESET			= 0x66,
	FLASH_CMD_GET_ID				= 0x90,
	FLASH_CMD_RESET					= 0x99,
	FLASH_CMD_GET_JEDEC_ID			= 0x9f,
};

typedef struct id {
	uint8_t		manufacturer_id;
	uint8_t		device_id;
} id_t;

typedef struct jedec {
	uint8_t		manufacturer_id;
	uint8_t		memtype;
	uint8_t		capacity;
} jedec_t;


id_t flash_read_id();
jedec_t flash_get_jedec_id();
void flash_reset();

#endif
