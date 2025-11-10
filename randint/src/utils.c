void
int_to_str(long val, char *buf, int buflen)
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
