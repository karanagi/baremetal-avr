#define	F_CPU		1000000

#include </usr/avr/include/util/delay.h>
#include </usr/avr/include/stdlib.h>
#include "uart.h"
#include "utils.h"
#include "adc.h"

#define SLEEP_TIME		1000
#define BUFLEN			10

static void init();
static void turn_on_led();
static void init_rng();

extern void test();

int
main(void)
{
	uint32_t		val;
	char			buf[BUFLEN];

	init();
	while (1) {
		val = rand();
		int_to_str(val, buf, BUFLEN);

		uart_send_str(buf);
		uart_send_newline();

		_delay_ms(SLEEP_TIME);
	}
}

static void
init()
{
	uart_init();
	adc_init();
	init_rng();

	turn_on_led();
}

static void
turn_on_led()
{
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB0);
}

static void 
init_rng()
{
	uint16_t		val;

	val = adc_read();
	srandom(val);
}
