#define F_CPU	1000000

#include <stddef.h>
#include </usr/avr/include/avr/io.h>
#include </usr/avr/include/util/delay.h>

#define BUFSIZE		64

void init();
void init_uart();
void uart_send(uint8_t *, int);
void uart_read(uint8_t *, int);
int uart_recv_until(uint8_t *, int, uint8_t);
uint8_t uart_recv(void);

int
main(void)
{
	uint8_t		buf[BUFSIZE];
	int			n;

	init();

	while (1) {
		n = uart_recv_until(buf, BUFSIZE, '\r');
		uart_send(buf, n);
		uart_send("\r\n", 2);
	}
}

void
init()
{
	init_uart();
}

void 
init_uart()
{
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H = 0;
	UBRR0L = 6;			// set baud rate to 9600
}

void 
uart_send(uint8_t *buf, int len)
{
	for (int i = 0; i < len; i++) {
		while (!(UCSR0A & (1 << UDRE0)))
			;
		UDR0 = *buf++;
	}
}

/* This is an inherently insecure function that trusts the user
 * to provide a valid buffer which mathces the `size` argument.
 */
void 
uart_read(uint8_t *buf, int size)
{
	for (int i = 0; i < size; i++) {
		while (!(UCSR0A & (1 << RXC0)))
			;
		buf[i] = UDR0;
	}
}

uint8_t 
uart_recv(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		;

	return UDR0;
}

/* 
 * recieve bytes until `len` bytes have been read, or the 
 * termination character is found 
 */
int
uart_recv_until(uint8_t *buf, int len, uint8_t term)
{
	int		n;

	if (buf == NULL)
		return -1;

	for (n = 0; n < len; n++) {
		buf[n] = uart_recv();
		if (buf[n] == term)
			break;
	}	

	return n;
}
