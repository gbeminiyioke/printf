#include "main.h"

/**
 * prnt_pntr - this function prints the value of a pointer variable
 * @types: this is a list of arguments
 * @buffer: this is the buffer for printing
 * @flags: flag
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns a pointer
 */

int prnt_pntr(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	unsigned long n_adr;
	int i, len, pad_start;
	char c, pad, map_to[] = "0123456789abcdef";
	void *ads = va_arg(types, void *);

	c = 0;
	pad = ' ';
	i = BUFFER_SIZE - 2;
	len = 2;
	pad_start = 1;

	NOT_USED(width);
	NOT_USED(size);
	if (ads == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFFER_SIZE - 1] = '\0';
	NOT_USED(precision);
	n_adr = (unsigned long)ads;
	while (n_adr > 0)
	{
		buffer[i--] = map_to[n_adr % 16];
		n_adr /= 16;
		len++;
	}
	if (!(flags & FLAG_MINUS) && (flags & FLAG_ZERO))
		pad = '0';
	if (flags & FLAG_PLUS)
		c = '+', len++;
	else if (flags & FLAG_SPACE)
		c = ' ', len++;
	i++;
	return (write_pointer(buffer, i, len, width, flags,
				pad, c, pad_start));
}

/**
 * prnt_non_printable - this function prints asci codes of non
 * printable characters
 * @types: this is the list of arguments
 * @buffer: this is the buffer for printing
 * @flags: falg
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns ascii printed
 */

int prnt_non_printable(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char *c = va_arg(types, char *);
	int i, offset;

	i = 0;
	offset = 0;
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);
	if (c == NULL)
		return (write(1, "(null)", 6));
	while (c[i] != '\0')
	{
		if (printable_yes(c[i]))
			buffer[i + offset] = c[i];
		else
			offset += add_hexa_code(c[i], buffer, i + offset);
		i++;
	}
	buffer[i + offset] = '\0';
	return (write(1, buffer, i + offset));
}

/**
 * prnt_rvsr - this function prints a string in reverse
 * @types: this is the list of arguments
 * @buffer: this is the buffer for printing
 * @flags: flag
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: returns the reversed string
 */

int prnt_rvsr(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	int i, cnt;
	char *s;

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(size);
	cnt = 0;
	s = va_arg(types, char *);
	if (s == NULL)
	{
		NOT_USED(precision);
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
 * print_rot13string - this function prints a string in rot13
 * @types: this is the list of arguments
 * @buffer: this is the buffer for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: the printed string in rot13
 */

int print_rot13string(va_list types, char buffer[], int flags, int width,
		int precision, int size)
{
	char c, *s;
	char str_in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char str_out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	unsigned int i, j;
	int cnt;

	NOT_USED(buffer);
	NOT_USED(flags);
	NOT_USED(width);
	NOT_USED(precision);
	NOT_USED(size);
	cnt = 0;
	s = va_arg(types, char *);
	if (s == NULL)
		s = "(AHYY)";
	for (i = 0; s[i]; i++)
	{
		for (j = 0; str_in[j]; j++)
		{
			if (s[i] == str_in[j])
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
