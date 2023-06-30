#include "main.h"

/**
 * print_char - this function prints a char
 * @types: list of arguments
 * @buffer: buffer array for printing
 * @flags:  the active flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: chars printed
 */

int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char a = va_arg(types, int);

	return (handle_write_char(a, buffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * print_string - this function prints a string
 * @types: list of arguments
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: chars printed
 */

int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *s = va_arg(types, char *);
	int len, i;

	len = 0;
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}
	while (s[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;
	if (width > len)
	{
		if (flags & F_MINUS)
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
 * print_percent - this function prints a percent sign
 * @types: list of arguments
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width.
 * @precision: accuracy
 * @size: size
 * Return: chars printed
 */

int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - this function prints int
 * @types: list of arguments
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width.
 * @precision: accuracy
 * @size: size
 * Return: chars printed
 */

int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int i, neg;
	unsigned long int val;
	long int l = va_arg(types, long int);

	i = BUFF_SIZE - 2;
	neg = 0;
	l = convert_size_number(l, size);
	if (l == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	val = (unsigned long int)l;
	if (l < 0)
	{
		val = (unsigned long int)((-1) * l);
		neg = 1;
	}
	while (val > 0)
	{
		buffer[i--] = (val % 10) + '0';
		val /= 10;
	}
	i++;
	return (write_number(neg, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - this function prints an unsigned number
 * @types: arguments
 * @buffer: buffer array tfor printing
 * @flags: flags
 * @width: width.
 * @precision: acccuracy
 * @size: size
 * Return: char printed.
 */

int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int cnt;
	unsigned int b[32];
	unsigned int tot, x, y, i;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	y = 2147483648;
	x = va_arg(types, unsigned int);
	b[0] = x / y;
	for (i = 1; i < 32; i++)
	{
		y /= 2;
		b[i] = (x / y) % 2;
	}
	for (i = 0, tot = 0, cnt = 0; i < 32; i++)
	{
		tot += b[i];
		if (i == 31 || tot == 31)
		{
			char c = '0' + b[i];

			write(1, &c, 1);
			cnt++;
		}
	}
	return (cnt);
}
