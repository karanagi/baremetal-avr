#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#define SLEEP_TIME		100

void init();

int
main(void)
{
	init();

	while (1) {
		PORTB ^= (1 << PB0);
		_delay_ms(SLEEP_TIME);
	}
}

void
init()
{
	DDRB |= (1 << PB0);
}
