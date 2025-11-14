#define	F_CPU		1000000

#include </usr/avr/include/util/delay.h>
#include <stdint.h>

#include "uart.h"
#include "utils.h"
#include "adc.h"

#define BUFLEN			10
#define SLEEP_TIME		10

#define N_MASKS		10

/* test masks 
778: 1100001010
727: 1011010111
664: 1010011000
754: 1011110010
546: 1000100010
87: 1010111
822: 1100110110
51: 110011
550: 1000100110
229: 11100101
*/

uint16_t test_masks[N_MASKS] = {
	778, 727, 664, 754, 546, 87, 822, 51, 550, 229,
};

static void int_to_str_test();
static void adc_test();
static void led_mask_test();
extern void display_set_mask(uint16_t);

/* all of the tests placed in here assume that hardware initialization
 * and configuration has been handled
 */
void 
test()
{
	//int_to_str_test();
	//adc_test();
	led_mask_test();
}

static void
led_mask_test()
{
	while(1) {
		for (int i = 0; i < N_MASKS; i++) {
			display_set_mask(test_masks[i]);
			_delay_ms(SLEEP_TIME);
		}
	}
}

static void
adc_test()
{
	uint32_t		adcval;
	char			buf[BUFLEN];

	while (1) {
		adcval = adc_read();
		int_to_str(adcval, buf, BUFLEN);

		uart_send_str(buf);
		uart_send_newline();

		_delay_ms(SLEEP_TIME);
	}
}

static void
int_to_str_test()
{
	uint32_t		adcval;
	char			buf[BUFLEN];

	while (1) {
		//adcval = adc_read();
		adcval = 43243242;
		int_to_str(adcval, buf, BUFLEN);

		uart_send_str(buf);
		uart_send_newline();

		_delay_ms(SLEEP_TIME);
	}
}
