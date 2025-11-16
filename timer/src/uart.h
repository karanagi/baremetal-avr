#ifndef		__UART_H
#define		__UART_H

#include </usr/avr/include/avr/io.h>
#include <stdint.h>

void uart_init();
void uart_send(uint8_t *, int);
void uart_send_str(char *);


static inline void 
uart_send_byte(uint8_t byte)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = byte;
}

static inline void 
uart_send_newline(void)
{
	uart_send((uint8_t *) "\r\n", 2);
}

#endif
