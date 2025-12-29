#include </usr/avr/include/avr/io.h>

#include "spi.h"
#include "flash.h"

id_t 
flash_read_id()
{
	id_t	id = {0};

	ss_slave_select();

	(void) spi_xchg_data(SPI_CMD_GET_ID);

	spi_send_dummy_bytes(3);

	id.manufacturer_id = spi_xchg_data(0);
	id.device_id = spi_xchg_data(0);

	ss_slave_deselect();

	return id;
}
