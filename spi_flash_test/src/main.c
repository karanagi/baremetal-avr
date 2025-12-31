#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "uart.h"
#include "flash.h"
#include "spi.h"
#include "utils.h"

void init();
void dump_status();
void dump_jedec();

int
main(void)
{

	init();

	while (1) {
		uart_send_str("Before reset: \r\n");
		dump_status();

		flash_reset();

		uart_send_str("\r\nAfter reset: \r\n");
		dump_status();
		uart_send_newline();

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
	print_hex(jedec_id.manufacturer_id);

	uart_send_str("Memory type id: ");
	print_hex(jedec_id.memtype);

	uart_send_str("Capacity id: ");
	print_hex(jedec_id.capacity);

	uart_send_newline();
}

void
dump_status()
{
	uint8_t		status1, status2;

	status1 = flash_get_status(FLASH_STATUS_REG1);
	status2 = flash_get_status(FLASH_STATUS_REG2);

	uart_send_str("status1: ");
	uart_send_int(status1);

	uart_send_str("status2: ");
	uart_send_int(status2);
}

void 
init()
{
	spi_init();
	uart_init();
}
