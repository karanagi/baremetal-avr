#define F_CPU		1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/avr/interrupt.h>
#include </usr/avr/include/util/delay.h>

#include "uart.h"
#include "utils.h"

#define BUFLEN			5
#define SLEEP_TIME		500

static volatile int count = 0;
static volatile bool button_pressed = false;
static volatile int timer = 0;

static void init();
static void init_interrupts();
static void init_timer();

static inline void save_timer_value();
static inline void clear_timer_value();
static inline bool has_n_times_elapsed(int);
static inline bool is_button_press();
static inline int abs(int);

int
main(void)
{
	char		buf[BUFLEN];

	init();
	while (1) {
		int_to_str(count, buf, BUFLEN);
		uart_send_str(buf);
		uart_send_newline();
		_delay_ms(SLEEP_TIME);
	}
}

static void
init()
{
	uart_init();

	init_timer();

	init_interrupts();

	DDRC |= (1 << PC5);
}

static void 
init_interrupts()
{
	PORTD |= (1 << PD2);
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();
}

static void
init_timer()
{
	//TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);
}

ISR(INT0_vect)
{
	/*
	if (is_button_press() && has_n_times_elapsed(10)) {
		save_timer_value();
		count++;
	}
	*/

	if (is_button_press()) {
		save_timer_value();
		count++;
	}
}

static inline bool 
is_button_press()
{
	_delay_ms(3);
	return (PIND & (1 << PD2)) ? false : true;
}

static inline void
save_timer_value()
{
	timer = TCNT1;
}

static inline void
clear_timer_value()
{
	timer = 0;
}

static inline bool 
has_n_times_elapsed(int n)
{
	int		elapsed_time;

	elapsed_time = abs(TCNT1 - timer);

	return elapsed_time > n ? true : false;
}

static inline int
abs(int x)
{
	return (x < 0) ? (x * -1) : x;
}
