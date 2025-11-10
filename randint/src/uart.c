#include <stdint.h>

#include "uart.h"

void
uart_init()
{
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UBRR0 = 6;		/* baud rate = 9600 */
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

