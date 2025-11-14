#define	F_CPU		1000000

#include <stdlib.h>
#include </usr/avr/include/util/delay.h>

#include "display.h"
#include "adc.h"

#define SLEEP_TIME		400

static void init();
static void turn_on_led();
static void init_rng();

static void display_init();
void display_set_mask(uint16_t);
static inline int display_set(uint8_t, bool);

int
main(void)
{
	uint16_t		val;

	init();
	while(1) {
		val = rand();
		display_set_mask(val);

		_delay_ms(SLEEP_TIME);
	}
}

void 
display_set_mask(uint16_t mask)
{
	for (int i = 0; i < N_SEGMENTS; i++) {
		if (mask & 1) 
			display_set(i, true);
		else
			display_set(i, false);

		mask >>= 1;
	}
}

static inline int
display_set(uint8_t segment, bool value)
{
	if (segment < RED0 || segment >= N_SEGMENTS)
		return -1;

	if (value) 
		*display[segment].reg |= (1 << display[segment].bit);
	else
		*display[segment].reg &= ~(1 << display[segment].bit);

	return 0;
}

static void 
init()
{
	init_rng();
	display_init();

	turn_on_led();
}

static void
display_init()
{
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB0);

	DDRD |= (1 << PD7) | (1 << PD6) | (1 << PD5) | 
			(1 << PD4) | (1 << PD3) | (1 << PD2) | 
			(1 << PD1);
}

static void
turn_on_led()
{
	DDRB |= (1 << PB1);
	PORTB |= (1 << PB1);
}

static void 
init_rng()
{
	long		val;

	adc_init();

	val = adc_read();
	srandom(val);

	//adc_disable();
}
