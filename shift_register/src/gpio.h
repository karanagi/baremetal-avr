#ifndef		__GPIO_H
#define		__GPIO_H

#include </usr/avr/include/avr/io.h>
#include <stdint.h>

#define DEFINE_MMIO_ADDR(val)		((volatile uint8_t *) (val + __SFR_OFFSET))

#define PINB_ADDR		DEFINE_MMIO_ADDR(0x16)
#define DDRB_ADDR		DEFINE_MMIO_ADDR(0x17)
#define PORTB_ADDR		DEFINE_MMIO_ADDR(0x18)

enum {
	GPIO_INPUT,
	GPIO_OUTPUT,
};

typedef struct gpio {
	volatile uint8_t		*input;
	volatile uint8_t		*ddr;
	volatile uint8_t		*port;
	uint8_t					pin;
} gpio_t;

void gpio_init(gpio_t *, uint8_t);
void gpio_set_dir(gpio_t *, int);
void gpio_toggle(gpio_t *);

#endif
