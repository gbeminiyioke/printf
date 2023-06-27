#include "main.h"

/**
 * handle_write_char - this function prints a string
 * @c: char types
 * @buffer: this buffer array for printing
 * @flags: flags.
 * @width: width.
 * @precision: accuracy
 * @size: Size
 * Return: Number of chars printed.
 */

int handle_write_char(char c, char buffer[], int flags, int width,
		int precision, int size)
{
	int i = 0;
	char pad = ' ';

	NOT_USED(precision);
	NOT_USED(size);
	if (flags & FLAG_ZERO)
		pad = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = padd;
		if (flags & FLAG_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
				write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_num - this function writes a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer for printing
 * @flags: Flags
 * @width: width
 * @prec: Precision
 * @length: length
 * @padd: Pading char
 * @extra_c: Extra char
 * Return: Number.
 */
int write_num(int ind, char buffer[], int flags, int width, int prec,
		int length, char padd, char extra_c)
{
	int i, pad_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
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
		if (flags & FLAG_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & FLAG_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & FLAG_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			return (write(1, &buffer[pad_start], i - pad_start) +
					write(1, &buffer[ind], length - (1 - pad_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - this function write a memory address
 * @buffer: Arrays for printing
 * @ind: Index at which the number starts in the buffer
 * @length: Length
 * @width: Wwidth
 * @flags: Flags
 * @padd: padding
 * @extra_c: extra char
 * @padd_start: Index for padding start
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & FLAG_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & FLAG_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & FLAG_MINUS) && padd == '0')
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
	return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}

/**
 * write_number - this function prints a number
 * @negative_num: arguments
 * @ind: char types
 * @buffer: Buffer array for printing
 * @flags: flags
 * @width: width.
 * @precision: precision specifier
 * @size: Size
 * Return: Number of chars printed.
 */

int write_number(int negative_num, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	int len;
	char pad, extra_ch;

	len = BUFFER_SIZE - ind - 1;
	pad = ' ';
	extra_ch = 0;
	NOT_USED(size);
	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
	pad = '0';
	if (negative_num)
		extra_ch = '-';
	else if (flags & FLAG_PLUS)
		extra_ch = '+';
	else if (flags & FLAG_SPACE)
		extra_ch = ' ';
	return (write_num(ind, buffer, flags, width, precision, len, pad, extra_ch));
}

/**
 * write_unsgnd - this function writes an unsigned number
 * @negative_num: indicates if the num is negative
 * @ind: Index to start in the buffer
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: Number of written chars.
 */

int write_unsgnd(int negative_num, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	char pad;
	int i, len;

	pad = ' ';
	len = BUFFER_SIZE - ind - 1;
	i = 0;
	NOT_USED(negative_num);
	NOT_USED(size);
	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < len)
		pad = ' ';
	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}
	if (!(flags & FLAG_MINUS) && (flags & FLAG_ZERO))
		pad = '0';
	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flags & FLAG_MINUS)
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], len));
		}
	}
	return (write(1, &buffer[ind], length));
}
