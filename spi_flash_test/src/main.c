#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "uart.h"
#include "flash.h"
#include "spi.h"

void init();
void dump_jedec();

int
main(void)
{

	init();

	while (1) {
		dump_jedec();
		_delay_ms(1000);
	}
}

void 
dump_jedec()
{
	jedec_t		jedec_id;

	jedec_id = flash_get_jedec_id();

	uart_send_str("Manufacturer id: ");
	uart_send_int(jedec_id.manufacturer_id);

	uart_send_str("Memory type id: ");
	uart_send_int(jedec_id.memtype);

	uart_send_str("Capacity id: ");
	uart_send_int(jedec_id.capacity);

	uart_send_newline();
}

void 
init()
{
	spi_init();
	uart_init();
}
