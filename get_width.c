#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 * Return: width.
 */

int get_width(const char *format, int *i, va_list list)
{
	int xi, wdth;

	wdth = 0;
	for (xi = *i + 1; format[xi] != '\0'; xi++)
	{
		if (is_digit(format[xi]))
		{
			wdth *= 10;
			wdth += format[xi] - '0';
		}
		else if (format[xi] == '*')
		{
			xi++;
			wdth = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = xi - 1;
	return (wdth);
}
