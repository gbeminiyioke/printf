#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */

int _printf(const char *format, ...)
{
	int i, printed_yes, chars_printed;
	va_list lst;
	char buffer[BUFF_SIZE];
	int flg, width, prec, sz, b_idx;

	printed_yes = 0;
	b_idx = 0;
	chars_printed = 0;
	if (format == NULL)
		return (-1);
	va_start(lst, format);
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[b_idx++] = format[i];
			if (b_idx == BUFF_SIZE)
				print_buffer(buffer, &b_idx);
			chars_printed++;
		}
		else
		{
			print_buffer(buffer, &b_idx);
			flg = get_flags(format, &i);
			width = get_width(format, &i, lst);
			prec = get_precision(format, &i, lst);
			sz = get_size(format, &i);
			++i;
			printed_yes = handle_print(format, &i, lst, buffer,
					flg, width, prec, sz);
			if (printed_yes == -1)
				return (-1);
			chars_printed += printed_yes;
		}
	}
	print_buffer(buffer, &b_idx);
	va_end(lst);
	return (chars_printed);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);
	*buff_ind = 0;
}

