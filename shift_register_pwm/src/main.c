#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>
#include <stdlib.h>

#define SLEEP_TIME			400
#define FADE_UP_DELAY		10
#define FADE_DOWN_DELAY		7000

#define SHIFT_REGISTER_OE		(PB0)
#define SHIFT_REGISTER_SRCLK		(PB1)
#define SHIFT_REGISTER_RCLK		(PB2)
#define SHIFT_REGISTER_SER		(PB3)

enum {
	GPIO_LOW,
	GPIO_HIGH,
};

void init();
void init_gpio();
void init_pwm();
void shift_register_set(uint8_t);
int generate_pulse(uint8_t);
int gpio_set(uint8_t, uint8_t);
void fade_leds();

void sequential();
void pseudo_random();

int
main(void)
{
	init();

	while (1) {
		//sequential();
		pseudo_random();
	}
}

void 
pseudo_random()
{
	int			val;

	srand((int) &val);

	while (1) {
		shift_register_set(rand() % 0xff);
		fade_leds();
		_delay_ms(SLEEP_TIME);
	}
}

void 
sequential()
{
	for (int i = 0; i < 8; i++) {
		shift_register_set(1 << i);
		fade_leds();
	}
}

void
init()
{
	init_gpio();
	init_pwm();
}

void 
init_gpio()
{
	DDRB |= (1 << SHIFT_REGISTER_SRCLK) | (1 << SHIFT_REGISTER_RCLK) | 
			(1 << SHIFT_REGISTER_SER);

}

void
init_pwm()
{
	DDRB |= (1 << SHIFT_REGISTER_OE);

	TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS00);
	OCR0A = 0xff;
}

void 
fade_leds()
{
	for (int i = 200; i >= 0; i--) {
		OCR0A = i;
		_delay_us(FADE_UP_DELAY);
	}

	for (int i = 0; i < 255; i++) {
		OCR0A = i;
		_delay_us(FADE_DOWN_DELAY);
	}
}

void 
shift_register_set(uint8_t val)
{
	for (int i = 0; i < 8; i++) {
		gpio_set(SHIFT_REGISTER_SER, val & 1);
		generate_pulse(SHIFT_REGISTER_SRCLK);
		val >>= 1;
	}

	generate_pulse(SHIFT_REGISTER_RCLK);
}

int
gpio_set(uint8_t pin, uint8_t val)
{
	uint8_t			mask;

	if (pin > PB5)
		return -1;

	mask = (1 << pin);

	if (val == GPIO_LOW)
		PORTB &= ~mask;
	else
		PORTB |= mask;

	return 0;
}

int
generate_pulse(uint8_t pin)
{
	uint8_t		mask;

	if (pin > PB5)
		return -1;

	mask = (1 << pin);

	PORTB |= mask;
	_delay_us(5);
	PORTB &= ~mask;

	return 0;
}
