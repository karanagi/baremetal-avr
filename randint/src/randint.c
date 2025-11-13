#define	F_CPU		1000000

#include </usr/avr/include/util/delay.h>
#include "uart.h"
#include "utils.h"
#include "adc.h"

#define SLEEP_TIME		1000
#define BUFLEN			10

static void init();
static void turn_on_led();

extern void test();

/*
static void init_rng();
*/

int
main(void)
{
	init();

	test();
}

static void
init()
{
	uart_init();
	//adc_init();
	turn_on_led();
}

static void
turn_on_led()
{
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB0);
}
