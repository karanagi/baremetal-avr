#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "gpio.h"

#define SLEEP_TIME		1000



/* 
 * PB2: SER
 * PB1: RCLK
 * PB0: SRCLK
 */

int
main(void)
{
	gpio_t		ser, rclk, srclk;

	gpio_init_as_output(&srclk, PB0);
	gpio_init_as_output(&rclk, PB1);
	gpio_init_as_output(&ser, PB2);

	while (1) {
		gpio_toggle(&srclk);
		_delay_ms(SLEEP_TIME);
	}
}

