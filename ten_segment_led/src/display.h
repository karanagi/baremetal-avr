#ifndef		_DISPLAY_H
#define		_DISPLAY_H

#include </usr/avr/include/avr/io.h>

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

#endif
