#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>
#include <stdlib.h>

#include "gpio.h"

#define SLEEP_TIME		300

typedef struct shift_reg {
	gpio_t		srclk;
	gpio_t		rclk;
	gpio_t		ser;
} shift_reg_t;

void shift_reg_init(shift_reg_t *, uint8_t, uint8_t, uint8_t);
void shift_reg_set(shift_reg_t *, uint8_t);
void generate_pulse(gpio_t *);

void sequential(shift_reg_t *);
void binary_counter(shift_reg_t *);
void random_set(shift_reg_t *sr);

/* 
 * PB2: SER
 * PB1: RCLK
 * PB0: SRCLK
 */

int
main(void)
{
	shift_reg_t		sr;

	shift_reg_init(&sr, PB0, PB1, PB2);

	while (1) {
		binary_counter(&sr);
		//sequantial(&sr);
		//random_set(&sr);
		_delay_ms(SLEEP_TIME);
	}
}

void 
sequential(shift_reg_t *sr)
{
	for (int i = 0; i < 8; i++) {
		shift_reg_set(sr, 1 << i);
		_delay_ms(SLEEP_TIME);
	}
}

void 
binary_counter(shift_reg_t *sr)
{
	for (int i = 0; i < 255; i++) {
		shift_reg_set(sr, i);
		_delay_ms(100);
	}
}

/* 
 * NOTE: Not truly random
 */
void
random_set(shift_reg_t *sr)
{
	int		val;

	srand((unsigned int) val);
	
	while (1) {
		shift_reg_set(sr, rand());
		_delay_ms(SLEEP_TIME);
	}
}


void 
shift_reg_init(shift_reg_t *sr, uint8_t srclk, uint8_t rclk, uint8_t ser)
{
	gpio_init_as_output(&sr->srclk, srclk);
	gpio_init_as_output(&sr->rclk, rclk);
	gpio_init_as_output(&sr->ser, ser);
}

void 
shift_reg_set(shift_reg_t *sr, uint8_t val)
{
	for (int i = 0; i < 8; i++) {
		gpio_set(&sr->ser, val & 1);
		generate_pulse(&sr->srclk);
		val >>= 1;
	}

	generate_pulse(&sr->rclk);
}

void
generate_pulse(gpio_t *gpio)
{
	gpio_set(gpio, GPIO_HIGH);
	_delay_us(5);
	gpio_set(gpio, GPIO_LOW);
}
