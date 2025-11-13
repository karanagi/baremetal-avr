#include </usr/avr/include/avr/io.h>
#include <stdint.h>

void 
adc_init()
{
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
}

uint16_t 
adc_read()
{
	uint16_t		val;

	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC))
		;

	val = (((uint16_t) ADCH << 8) | (uint16_t) ADCL);
	return val;
}
