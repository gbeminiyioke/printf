#include "main.h"

/**
 * print_pointer - this function prints the value of a pointer
 * @types: arguments list
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: pointer value.
 */

int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char map[] = "0123456789abcdef";
	unsigned long val_ad;
	void *ad = va_arg(types, void *);
	char pad, cx;
	int idx;
	int len;
	int st_pad;

	pad = ' ';
	cx = 0;
	idx = BUFF_SIZE - 2;
	len = 2;
	st_pad = 1;
	UNUSED(width);
	UNUSED(size);
	if (ad == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	val_ad = (unsigned long)ad;
	while (val_ad > 0)
	{
		buffer[idx--] = map[val_ad % 16];
		val_ad /= 16;
		len++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';
	if (flags & F_PLUS)
		cx = '+', len++;
	else if (flags & F_SPACE)
		cx = ' ', len++;
	idx++;
	return (write_pointer(buffer, idx, len, width, flags,
				pad, cx, st_pad));
}

/**
 * print_non_printable - this function prints ascii codes
 * in hexa for non printable characters
 * @types: arguments list
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: none printable characters
 */

int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int offset, i;
	char *s = va_arg(types, char *);

	offset = 0;
	i = 0;
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
	{
		if (is_printable(s[i]))
			buffer[i + offset] = s[i];
		else
			offset += append_hexa_code(s[i], buffer, i + offset);
		i++;
	}
	buffer[i + offset] = '\0';
	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - this function prints a string in reverse
 * @types: Lista of arguments
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: string printed in reverse
 */

int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int cnt, i;
	char *s;

	cnt = 0;
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	s = va_arg(types, char *);
	if (s == NULL)
	{
		UNUSED(precision);
		s = ")Null(";
	}
	for (i = 0; s[i]; i++)
		;
	for (i = i - 1; i >= 0; i--)
	{
		char c = s[i];

		write(1, &c, 1);
		cnt++;
	}
	return (cnt);
}

/**
 * print_rot13string - this function prints a string in rot13.
 * @types: arguments list
 * @buffer:  buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: string in rot13
 */

int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int i, j;
	char str_in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char str_out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	char c, *s;
	int cnt;

	cnt = 0;
	s = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
		s = "(AHYY)";
	for (i = 0; s[i]; i++)
	{
		for (j = 0; str_in[j]; j++)
		{
			if (str_in[j] == s[i])
			{
				c = str_out[j];
				write(1, &c, 1);
				cnt++;
				break;
			}
		}
		if (!str_in[j])
		{
			c = s[i];
			write(1, &c, 1);
			cnt++;
		}
	}
	return (cnt);
}
