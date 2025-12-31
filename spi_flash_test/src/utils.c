#include "utils.h"
#include "uart.h"

#define NDIGITS		8

static inline int count_hex_digits(int);
static inline char get_hex_char(int);
static int hex_to_str(char *, int, int);

void
int_to_str(uint32_t val, char *buf, int buflen)
{
	int		ndigits = 0;

	for (long tmp = val; tmp > 0;) {
		ndigits += 1;
		tmp /= 10;
	}

	if (ndigits > buflen)
		ndigits = buflen - 1;

	buf[ndigits--] = '\0';

	for (long i = ndigits; i >= 0; i--) {
		buf[i] = '0' + (val % 10);
		val /= 10;
	}
}

void
print_hex(int n, bool prefix)
{
	char		buf[NDIGITS] = {0};
	
	if (hex_to_str(buf, NDIGITS, n) == -1)
		uart_send_str("print_hex(): integer too long");

	if (prefix)
		uart_send_str("0x");

	uart_send_str(buf);
	uart_send_newline();
}

int
hex_to_str(char *buf, int len, int val)
{
	int		digits;
	
	digits = count_hex_digits(val);
	if (digits >= len)
		return -1;

	while (digits > 0) {
		buf[--digits] = get_hex_char(val & 0xf);
		val >>= 4;
	}

	return 0;
}

static inline int
count_hex_digits(int n)
{
	int	count = 0;

	while (n != 0) {
		count++;
		n >>= 4;
	}

	return count;
}

static inline char 
get_hex_char(int n)
{
	if (n > 0xf)
		return '\0';

	if (n < 0xa)
		return '0' + n;
	else
		return 'a' + (n - 0xa);
}
