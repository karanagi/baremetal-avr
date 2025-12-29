#ifndef		__SPI_TEST_H
#define		__SPI_TEST_H

#include <stdint.h>

enum {
	SPI_SS		= PB2,
	SPI_MOSI	= PB3,
	SPI_MISO	= PB4,
	SPI_SCK		= PB5,
};

#define SPI_PORT	PORTB
#define SPI_DDR		DDRB		

void spi_init();
static inline void ss_slave_select();
static inline void ss_slave_deselect();
uint8_t spi_xchg_data(uint8_t);
static inline void spi_send_dummy_bytes(int);

static inline void 
ss_slave_select()
{
	SPI_PORT &= ~(1 << SPI_SS);		/* select slave by pulling SS pin low */
}

static inline void 
ss_slave_deselect()
{
	SPI_PORT |= (1 << SPI_SS);		/* deselct slave by pull SS pin high */
}

static inline void 
spi_send_dummy_bytes(int count)
{
	for (int i = 0; i < count; i++)
		(void) spi_xchg_data(0);
}

static inline uint8_t
spi_read()
{
	return spi_xchg_data(0);
}

#endif
