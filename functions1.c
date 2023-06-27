#include "main.h"

/**
 * prnt_unsigned - this function prints an unsigned number
 * @types: this lists the arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns an unsigned number
 */

int prnt_unsigned(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	unsigned long int c;
	int i;

	c = va_arg(types, unsigned long int);
	i = BUFFER_SIZE - 2;
	if (c == 0)
		buffer[i--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';
	while (c > 0)
	{
		buffer[i--] = (c % 10) + '0';
		c /= 10;
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * prnt_octal - this function prints an unsigned number in octal
 * @types: this lists the arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns what was printed
 */

int prnt_octal(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	unsigned long int c, a;
	int i;

	c = va_arg(types, unsigned long int);
	a = c;

	i = BUFFER_SIZE - 2;
	NOT_USED(width);
	c = cnvrt_sz_unsgnd(c, size);
	if (c == 0)
		buffer[i--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';
	while (c  > 0)
	{
		buffer[i--] = (c % 8) + '0';
		c /= 8;
	}
	if (a != 0 && flags & FLAG_HASH)
		buffer[i--] = '0';
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * prnt hexadec - this function prints an unsigned number in hexadecimal
 * @types: this lists the arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: return the number in hexadecimal
 */

int prnt_hexcadec(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	return (prnt_hexa(types, "0123456789abcdef", buffer, flags, 'x', width,
				precision, size));
}

/**
 * prnt_hexadec_upr - this function prints an unsigned number in
 * upper heaxdecimal
 * @types: this is the list of arguments
 * @buffer: this is the buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns the printed char in upper
 */

int prnt_hexadec_upr(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	return (prnt_hexa(types, "0123456789ABCDEF", buffer, flags, 'X', width,
				precision, size));
}

/**
 * prnt_hexa - this function prints number in lower or uper hexadecimal
 * @types: this is the list of arguments
 * @map_to: array values to map number to
 * @buffer: this is the buffer array for printing
 * @flags: flag
 * @flag_ch: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns the upper or lower case of hexa
 */

int prnt_hexa(va_list types, char map_to[], char buffer[], int flags,
		char flag_ch, int width, int precision, int size)
{
	unsigned long int c, x;
	int i;

	i = BUFFER_SIZE - 2;
	c = va_arg(types, unsigned long int);
	x = c;
	NOT_USED(width);
	c = cnvrt_sz_unsgnd(c, size);
	if (c == 0)
		buffer[i--] = '0';
	buffer[BUFFER_SIZE - 1] = '\0';
	while (c > 0)
	{
		buffer[i--] = map_to[c % 16];
		c /= 16;
	}
	if (flags & FLAG_HASH && x != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
