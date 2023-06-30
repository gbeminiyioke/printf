#include "main.h"

/**
 * get_precision - this function gets the precision for printing
 * @format: format print the arguments
 * @i: arguments list to be print
 * @list: arguments list
 * Return: the precision.
 */

int get_precision(const char *format, int *i, va_list list)
{
	int prec, xi;

	prec = -1;
	xi = *i + 1;
	if (format[xi] != '.')
		return (prec);
	prec = 0;
	for (xi += 1; format[xi] != '\0'; xi++)
	{
		if (is_digit(format[xi]))
		{
			prec *= 10;
			prec += format[xi] - '0';
		}
		else if (format[xi] == '*')
		{
			xi++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = xi - 1;
	return (prec);
}
