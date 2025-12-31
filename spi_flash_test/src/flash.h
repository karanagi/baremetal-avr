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

enum {
	FLASH_SUSP_STATUS		= (1 << 15),
	FLASH_COMPLMENT_PROT 	= (1 << 14),
	FLASH_SEC_REG_LCK2		= (1 << 13),
	FLASH_SEC_REG_LCK1		= (1 << 12),
	FLASH_SEC_REG_LCK0		= (1 << 11),
	FLASH_RESV0				= (1 << 10),
	FLASH_QUAD_ENABLE		= (1 << 9),
	FLASH_STATUS_REG_PROT1	= (1 << 8),
	FLASH_STATUS_REG_PROT0	= (1 << 7),
	FLASH_SECTOR_PROT		= (1 << 6),
	FLASH_TOP_PROT			= (1 << 5),
	FLASH_BLK_PROT2			= (1 << 4),
	FLASH_BLK_PROT1			= (1 << 3),
	FLASH_BLK_PROT0			= (1 << 2),
	FLASH_WRITE_ENABLE		= (1 << 1),
	FLASH_BUSY				= (1 << 0),
};

typedef enum status_reg {
	FLASH_STATUS_REG1,
	FLASH_STATUS_REG2,
} status_reg_t ;

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
uint8_t flash_get_status(status_reg_t);
void flash_reset();

#endif
