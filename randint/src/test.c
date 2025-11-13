#define	F_CPU		1000000

#include </usr/avr/include/util/delay.h>
#include <stdint.h>

#include "uart.h"
#include "utils.h"
#include "adc.h"

#define BUFLEN			10
#define SLEEP_TIME		200

static void int_to_str_test();
static void adc_test();

/* all of the tests placed in here assume that hardware initialization
 * and configuration has been handled
 */
void 
test()
{
	//int_to_str_test();
	adc_test();
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
