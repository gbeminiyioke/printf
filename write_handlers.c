#include "main.h"

/**
 * handle_write_char - this function prints a string
 * @c: char
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width.
 * @precision: accuracy
 * @size: size
 * Return: the chars printed
 */

int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int i, pad;

	i = 0;
	pad = ' ';
	UNUSED(precision);
	UNUSED(size);
	if (flags & F_ZERO)
		pad = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = pad;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_number - this function prints a number
 * @is_negative: arguments list
 * @ind: index.
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width.
 * @precision: accuracy
 * @size: size
 * Return: a number.
 */

int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int len;
	char pad, xc;

	len = BUFF_SIZE - ind - 1;
	pad = ' ';
	xc = 0;
	UNUSED(size);
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (is_negative)
		xc = '-';
	else if (flags & F_PLUS)
		xc = '+';
	else if (flags & F_SPACE)
		xc = ' ';
	return (write_num(ind, buffer, flags, width, precision, len,
				pad, xc));
}

/**
 * write_num - ths function write a number
 * @ind: index
 * @buffer: buffer for printing
 * @flags: flags
 * @width: width
 * @prec:  accuracy
 * @length: length
 * @padd: pading
 * @extra_c: extra character
 * Return: the printed number.
 */

int write_num(int ind, char buffer[], int flags, int width, int prec,
		int length, char padd, char extra_c)
{
	int i, s_pad;

	s_pad = 1;
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--s_pad] = extra_c;
			return (write(1, &buffer[s_pad], i - s_pad) +
					write(1, &buffer[ind], length - (1 - s_pad)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - this function writes an unsigned number
 * @is_negative: shows if the num is negative
 * @ind: Index
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: unsigned characters
 */

int write_unsgnd(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int len, i;
	char pad;

	len = BUFF_SIZE - ind - 1;
	i = 0;
	pad = ' ';
	UNUSED(is_negative);
	UNUSED(size);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < len)
		pad = ' ';
	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], len));
		}
	}
	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - this function write a memory address
 * @buffer: buffer array for printing
 * @ind: index
 * @length: length
 * @width: width
 * @flags: flags
 * @padd: padding
 * @extra_c: extra charracter
 * @padd_start: index where padding starts
 * Return: a pointer
 */

int write_pointer(char buffer[], int ind, int length, int width,
		int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
