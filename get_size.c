#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * Return: Precision.
 */

int get_size(const char *format, int *i)
{
	int xi, sz;

	xi = *i + 1;
	sz = 0;
	if (format[xi] == 'l')
		sz = S_LONG;
	else if (format[xi] == 'h')
		sz = S_SHORT;
	if (sz == 0)
		*i = xi - 1;
	else
		*i = xi;
	return (sz);
}
