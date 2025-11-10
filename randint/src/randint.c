#define	F_CPU		1000000

#include </usr/avr/include/util/delay.h>
#include "uart.h"
#include "utils.h"

#define SLEEP_TIME		1000
#define BUFLEN			5

static void init();
/*
static void init_adc();
static void init_rng();
*/

int
main(void)
{
	uint32_t	testint = 0xfffffff;
	char		buf[BUFLEN];

	init();
	while (1) {
		int_to_str(testint, buf, BUFLEN);

		uart_send_str(buf);
		uart_send((uint8_t *) "\r\n", 2);
		_delay_ms(SLEEP_TIME);
	}
}

static void
init()
{
	uart_init();
}



