#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "uart.h"
#include "flash.h"
#include "spi.h"

void init();

int
main(void)
{
	id_t		id;

	init();

	while (1) {
		id = flash_read_id();
		uart_send_int((uint32_t) id.manufacturer_id);
		uart_send_int((uint32_t) id.device_id);
	}
}

void 
init()
{
	spi_init();
	uart_init();
}
