#include </usr/avr/include/avr/io.h>
#include "spi.h"

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
