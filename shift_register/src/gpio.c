#define F_CPU	1000000

#include </usr/avr/include/util/delay.h>
#include "gpio.h"

void
gpio_init(gpio_t *gpio, uint8_t pin)
{
	gpio->input = PINB_ADDR;
	gpio->ddr = DDRB_ADDR;
	gpio->port = PORTB_ADDR;
	gpio->pin = pin;
}

void 
gpio_init_as_output(gpio_t *gpio, uint8_t pin)
{
	gpio_init(gpio, pin);
	gpio_set_dir(gpio, GPIO_OUTPUT);
}

void 
gpio_set_dir(gpio_t *gpio, int dir)
{
	if (dir == GPIO_INPUT) 
		*(gpio->ddr) &= ~(1 << gpio->pin);
	else
		*(gpio->ddr) |= (1 << gpio->pin);
}

void
gpio_toggle(gpio_t *gpio)
{
	*gpio->port ^= (1 << gpio->pin);
}

void
gpio_set(gpio_t *gpio, int val)
{
	uint8_t		mask;

	mask = (1 << gpio->pin);

	/* return if gpio not configured as output */
	if (!(*gpio->ddr & mask))
		return;

	if (val == GPIO_LOW)
		*gpio->port &= ~mask;
	else
		*gpio->port |= mask;
}

