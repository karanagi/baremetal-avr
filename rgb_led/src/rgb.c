#define F_CPU	1000000

#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#define SLEEP_TIME		1000
#define N_COLORS		7

typedef struct color {
	uint8_t		red;
	uint8_t		green;
	uint8_t		blue;
} color_t ;

color_t rainbow_colors[N_COLORS] = {
	{0xff, 0x00, 0x00},			/* red */
	{0xff, 0x10, 0x00},			/* orange */
	{0xd0, 0x30, 0x00},			/* yellow */
	{0x00, 0xff, 0x00},			/* green */
	{0x00, 0x00, 0xff},			/* blue */
	{0x28, 0x00, 0xff},			/* indigo */
	{0x50, 0x00, 0x82},			/* violet */
};

void init();
void set_color(color_t);
void set_color_by_value(uint8_t, uint8_t, uint8_t);

int
main(void)
{
	init();

	while (1) {
		for (int i = 0; i < N_COLORS; i++) {
			set_color(rainbow_colors[i]);
			_delay_ms(SLEEP_TIME);
		}
	}
}

/* 
 * PD6 (OC0A) = blue
 * PD5 (OC0B) = green
 * PB1 (OC1A) = red
 */
void
init()
{
	DDRD |= (1 << PD6) | (1 << PD5);
	DDRB |= (1 << PB1);

	TCCR0A |= ((1 << COM0A1) | (1 << COM0B1) | 
				(1 << WGM01) | (1 << WGM00));

	TCCR0B |= (1 << CS00);
	OCR0A = 0xff;
	OCR0B = 0xff;

	TCCR1A |= (1 << COM1A1) | (1 << WGM12) | (1 << WGM10);
	TCCR1B |= (1 << CS10);
	OCR1AL = 0xff;
}

void 
set_color(color_t color)
{
	set_color_by_value(color.red, color.green, color.blue);
}

void 
set_color_by_value(uint8_t red, uint8_t green, uint8_t blue)
{
	OCR1AL = red;
	OCR0B = green;
	OCR0A = blue;
}
