#include "main.h"

/**
 * prnt_char - this function prints a character
 * @types: this lists the argumentds
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns the number of characters printed
 */

int prnt_char(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char c;

	c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
 * prnt_str - this function prints a string
 * @types: this lists the arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns the number of characters printed
 */

int prnt_str(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char *s;
	int i = 0, len = 0;

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);
	s = va_arg(types, char *);
	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}
	while (s[len] != '\0')
		len++;
	if (precision < len && precision >= 0)
		len = precision;
	if (len < width)
	{
		if (flags & FLAG_MINUS)
		{
			write(1, &s[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &s[0], len);
			return (width);
		}
	}
	return (write(1, s, len));
}

/**
 * prnt_percent - this function prints the percentage sign
 * @types: this lists the arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: precision
 * @size: size
 * Return: returns the mod of char printed
 */

int prnt_percent(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	NOT_USED(types);
	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);
	return (write(1, "%%", 1));
}

/**
 * prnt_int - this function prints an int
 * @types: this lists the arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returna int
 */

int prnt_int(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	unsigned long int l_int;
	long int c;
	int neg = 0, i;

	i = BUFFER_SIZE - 2;
	neg = 0;
	c = va_arg(types, long int);
	c = cnvrt_sz_num(c, size);
	if (c == 0)
		buffer[i--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';
	l_int = (unsigned long int)c;
	if (c < 0)
	{
		l_int = (unsigned long int)((-1) * c);
		neg = 1;
	}
	while (l_int > 0)
	{
		buffer[i--] = (l_int % 10) + '0';
		l_int /= 10;
	}
	i++;
	return  (write_number(neg, i, buffer, flags, width, precision, size));
}

/**
 * prnt_binary - this function prints a binary number
 * @types: this is lists the arguments
 * @buffer: this is the buffer array fro printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns a number
 */

int prnt_binary(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int tot_c = 0;
	unsigned int i, j, k, tot, arr[32];

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);

	j = 2147483648;
	i = va_arg(types, unsigned int);
	arr[0] = i / j;
	for (k = 1; k < 32; k++)
	{
		j /= 2;
		arr[k] = (i / j) % 2;
	}
	for (k = 0, tot = 0, tot_c = 0; k < 32; k++)
	{
		tot += arr[k];
		if (k == 31 || tot)
		{
			char c = '0' + arr[k];

			write(1, &c, 1);
			tot_c++;
		}
	}
return (tot_c);
}
