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
