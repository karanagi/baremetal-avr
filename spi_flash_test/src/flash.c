#define 	F_CPU 100000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "spi.h"
#include "flash.h"

id_t 
flash_read_id()
{
	id_t	id = {0};

	ss_slave_select();

	(void) spi_xchg_data(FLASH_CMD_GET_ID);

	spi_send_dummy_bytes(3);

	id.manufacturer_id = spi_xchg_data(0);
	id.device_id = spi_xchg_data(0);

	ss_slave_deselect();

	return id;
}

uint8_t 
flash_get_status(status_reg_t reg)
{
	uint8_t		command, status;

	command = (reg == FLASH_STATUS_REG1) ? FLASH_CMD_READ_STATUS_REG1 
										 : FLASH_CMD_READ_STATUS_REG2;

	ss_slave_select();

	(void) spi_xchg_data(command);
	status = spi_read();

	ss_slave_deselect();

	return status;
}

void 
flash_reset()
{
	ss_slave_select();

	(void) spi_xchg_data(FLASH_CMD_ENABLE_RESET);
	(void) spi_xchg_data(FLASH_CMD_RESET);

	ss_slave_deselect();

	_delay_us(50);
}

jedec_t 
flash_get_jedec_id()
{
	jedec_t		id;

	ss_slave_select();

	(void) spi_xchg_data(FLASH_CMD_GET_JEDEC_ID);

	id.manufacturer_id = spi_read();
	id.memtype = spi_read();
	id.capacity = spi_read();

	ss_slave_deselect();

	return id;
}
