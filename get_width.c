#include "main.h"

/**
 * get_width – this function gets the width
 * @format: Format to print the arguments.
 * @i: list of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: returns the width.
 */
int get_width(const char *format, int *i, va_list list)
{
int j, wdth = 0;

	for (j = *i + 1; format[j] != '\0'; j++)
{
	if (digit_yes(format[j]))
{
	wdth *= 10;
	wdth += format[j] - '0';
}
else if (format[j] == '*')
{
	j++;
	wdth = va_arg(list, int);
	break;
}
else
		break;
}
*i = j - 1;
return (wdth);
}
