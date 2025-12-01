#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>
#include </usr/avr/include/avr/wdt.h>
#include </usr/avr/include/avr/interrupt.h>

enum {
	SLEEP_TIME		= 5000,
	WDT_TIMEOUT		= WDTO_15MS, 
};

enum {
	INPUT_PIN			= PC5,
	POWER_LED			= PD0,
	WDT_LED				= PD7,
};

void init_gpio();
void initiate_reset();
static inline void wdr();
__attribute__((naked)) __attribute__((section(".init3"))) void wdt_init();

int
main(void)
{
	init_gpio();

	_delay_ms(SLEEP_TIME);
	PORTD |= (1 << WDT_LED);

	while (1) {
		if (PINC & (1 << INPUT_PIN))
			continue;
		initiate_reset();
	}
}

void
initiate_reset()
{
	wdt_disable();
	wdt_enable(WDT_TIMEOUT);
	cli();

	while (1) {
	}
}

void 
init_gpio()
{
	DDRD |= (1 << POWER_LED) | (1 << WDT_LED);
	PORTD |= (1 << POWER_LED);
	PORTC |= (1 << INPUT_PIN);
}

static inline void 
wdr()
{
	asm volatile ( "wdr" );
}

/* 
 * A timer that resets the watch dog timer using the `wdt` instruction
 * every 1ms.
 * Placed in the `.init3` section to ensure that it is enabled before
 * the watch dog timer expires at boot. 
 */
__attribute__((naked)) __attribute__((section(".init3"))) void
init_wdr_timer()
{
	OCR0A = 1;
	TIMSK0 |= (1 << OCIE0A);
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS02) | (1 << CS00);

	sei();
}

ISR(TIMER0_COMPA_vect)
{
	wdr();
}
