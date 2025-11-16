#define F_CPU		1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/avr/interrupt.h>

#include "utils.h"

#define BUFLEN			5
#define SLEEP_TIME		500

static volatile int count = 0;

static void init();
static void init_interrupts();
static void init_timer();


int
main(void)
{
	init();
	while (1) {
	}
}

static void
init()
{
	init_timer();
	
	init_interrupts();

	DDRC |= (1 << PC5);
}

static void 
init_interrupts()
{
	PIND |= (1 << 2);
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();
}

static void
init_timer()
{
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = 976;
}


ISR(INT0_vect)
{
	count++;
}

ISR(TIMER1_COMPA_vect)
{
	PORTC ^= (1 << PC5);
}
