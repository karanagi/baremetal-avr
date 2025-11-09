#define	F_CPU		1000000

#include <stdlib.h>
#include </usr/avr/include/util/delay.h>

#include "display.h"
#include "test.h"

#define SLEEP_TIME		500

static void init();
static void display_set_mask(uint16_t);
static inline int display_set(uint8_t, bool);

int
main(void)
{
	init();
	while(1) {
		for (int i = 0; i < N_MASKS; i++) {
			display_set_mask(test_masks[i]);
			_delay_ms(SLEEP_TIME);
		}
	}
}

static void 
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
	DDRB |= (1 << PB7) | (1 << PB6) | (1 << PB0);
	DDRD |= 0xfe;
}
