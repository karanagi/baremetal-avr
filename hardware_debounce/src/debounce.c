#define F_CPU	8000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/avr/interrupt.h>
#include </usr/avr/include/util/delay.h>

#include "uart.h"
#include "utils.h"

#define SLEEP_TIME		100
#define BUFSIZE			16

enum {
	INPUT_PIN		= PC5,
};

enum {
	GPIO_LOW		= false,
	GPIO_HIGH	 	= true,
};

static volatile int counter = 0;

static void init();
static void pcint_init();
static void print_counter();

int
main(void)
{
	init();
	while (1) 
		print_counter();
}

void
init()
{
	uart_init();
	pcint_init();
	sei();
}

static void 
print_counter()
{
	char		buf[BUFSIZE];

	int_to_str(counter, buf, BUFSIZE);
	uart_send_strln(buf);
}

static void
pcint_init()
{
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT13);
}

ISR(PCINT1_vect)
{
	static bool last_state = GPIO_HIGH;

	if (last_state == GPIO_HIGH)
		counter++;

	last_state = !last_state;
}
