#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "uart.h"
#include "spi_test.h"

int
main(void)
{
	id_t		id;

	spi_init();
	uart_init();

	while (1) {
		id = spi_read_id();
		uart_send_int((uint32_t) id.manufacturer_id);
		uart_send_int((uint32_t) id.device_id);
	}
}

void
spi_init()
{
	SPI_DDR |= (1 << SPI_SCK) | (1 << SPI_MOSI) | (1 << SPI_SS);	/* enable SCK, MOSI, and SS */
	SPI_PORT |= (1 << SPI_MISO) | (1 << SPI_SS);				/* enable pull-up on MISO, set SS high*/

	SPCR |= (1 << MSTR) | (1 << SPE);
}

uint8_t 
spi_xchg_data(uint8_t data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)))
		;
	return SPDR;
}

id_t 
spi_read_id()
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
