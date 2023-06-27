#include "main.h"

/**
 * print_buff - This function prints the content of the buffer
 * @buff: a char array
 * @buff_index: indicates the index to add the next char
 * Return: returns void
 */

void print_buff(char buff[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buff[0], *buff_index);
	*buff_index = 0;
}

/**
 * _printf - this function produces an output according to a format
 * @format: a character string. it is composed of zero or more directives
 * Return: the number of characters printed
 */

int _printf(const char *format, ...);
{
	int i, char_printed, its_printed, width, precision, size, b_index, flag;
	char buffer[BUFFER_SIZE];
	va_list pq;

	char_printed = 0;
	its_printed = 0;
	b_index = 0;
	if (format == NULL)
		return (-1);
	va_start(pq, format); /* initialize the argument list */
	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[b_index++] = format[i];
			if (b_index == BUFFER_SIZE)
				print_buff(buffer, &b_index);
			char_printed++;
		}
		else
		{
			print_buff(buffer, &b_index);
			flags = get_flags(format, &i);
			size = get_size(format, &i);
			width = get_width(format, &i, pq);
			precision = get_precision(format, &i, pq);
			i++;
			its_printed = handle_print(format, &i, pq, buffer, flags,
					width, precision, size);
			if (its_printed == -1)
				return (-1);
			char_printed += its_printed;
		}
	}
	print_buff(buffer, &b_index);
	va_end(pq);
	return (char_printed);
}
