#define	F_CPU		1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#include "test.h"

#define SLEEP_TIME		10000

enum {
	RED0,
	RED1,
	YELLOW0,
	YELLOW1,
	YELLOW2,
	GREEN0,
	GREEN1,
	GREEN2,
	GREEN3,
	BLUE0,
	N_SEGMENTS,
};

typedef struct gpio {
	volatile uint8_t	*reg;
	uint8_t				bit;
} gpio_t; 

gpio_t display[N_SEGMENTS] = {
	[RED0]		= { &PORTB, PB0 },
	[RED1]		= { &PORTD, PD7 },
	[YELLOW0]	= { &PORTD, PD6 },
	[YELLOW1]	= { &PORTD, PD5 },
	[YELLOW2]	= { &PORTB, PB7 },
	[GREEN0]	= { &PORTB, PB6 },
	[GREEN1]	= { &PORTD, PD4 },
	[GREEN2]	= { &PORTD, PD3 },
	[GREEN3]	= { &PORTD, PD2 },
	[BLUE0]		= { &PORTD, PD1 },
};

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
