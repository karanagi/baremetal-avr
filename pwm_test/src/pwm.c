#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#define PWM_MAX			200

void init();

int
main(void)
{
	init();
	while (1) {
		for (int i = 0; i < PWM_MAX; i++) {
			OCR0B = i;
			_delay_us(100);
		}

		for (int i = PWM_MAX; i >= 0; i--) {
			OCR0B = i;
			_delay_ms(20);
		}
	}
}


void
init()
{
	DDRD |= (1 << PD5);
	TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS00);
}
