#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/avr/interrupt.h>
#include </usr/avr/include/util/delay.h>

#include "adc.h"

#define TIMER_MASK			(1 << CS21)

/* sleep should be between 100 and 1000 */

static volatile int sleep_time = 500;
static volatile int counter = 0;

void init();
void init_timers();
void round_robin_toggle();
void sleep();

int
main(void)
{
	init();
	while (1) 
		round_robin_toggle();
}

void 
round_robin_toggle()
{
	for (int bit = 1; bit < 6; bit++) {
		PORTB ^= (1 << bit);
		sleep();
		PORTB ^= (1 << bit);
	}

}

void
init()
{
	DDRB |= 0x3e;
	adc_init();
	init_timers();
	sei();
}

void 
init_timers()
{
	TCCR2A |= (1 << WGM21);
	TCCR2B |= TIMER_MASK;
	TIMSK2 |= (1 << OCIE0B) | (1 << OCIE0A);
	OCR2A = 100;			/* timer for sleep */
	OCR2B = 5;				/* timer for ADC poll */

}

void 
sleep()
{
	counter = 0;
	while (counter < sleep_time)
		;
}

ISR(TIMER2_COMPA_vect)
{
	counter++;
}

ISR(TIMER2_COMPB_vect)
{
	uint16_t		val;

	val = (adc_read() / 10) * 10;
	if (val < 100)
		val = 100;

	sleep_time = val;
}
