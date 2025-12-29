#include <stdint.h>

#include "uart.h"
#include "utils.h"

#define MAX_DIGITS		5

void
uart_init()
{
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0 = 12;			/* baud rate = 4800 */
}

void
uart_send(uint8_t *data, int len)
{
	for (int i = 0; i < len; i++)
		uart_send_byte(*data++);
}

void 
uart_send_str(char *s)
{
	while (*s)
		uart_send_byte(*s++);
}

void
uart_send_int(uint32_t n)
{
	char		buf[MAX_DIGITS];

	int_to_str(n, buf, MAX_DIGITS);
	uart_send_str(buf);
	uart_send_newline();
}
