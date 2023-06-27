#include "main.h"

/**
 * get_size - this function gets the size to cast the argument
 * @format: format to print the argument
 * @i: list of arguments
 * Return: accuracy
 */

int get_size(const char *format, int *i)
{
	int j, sz;

	j = *i + 1;
	sz = 0, j = *i;
	if (format[j] == 'l')
		sz = SZ_LNG;
	else if (format[j] == 'h')
		sz = SZ_SHRT;
	if (sz == 0)
		*i = j - 1;
	else
		*i = j;
	return (sz);
}
