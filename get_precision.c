 #include "main.h"

/**
 * get_precision - this function gets the printing precision
 * @format: format to print the arguments
 * @i: list of arguments to print
 * @list: list of arguments
 * Return: accuracy
 */

int get_precision(const char *format, int *i, va_list list)
{
int j, accuracy;

j = *i + 1;
accuracy = -1;
if (format[j] != '.')
	return (accuracy);
accuracy = 0;
for (j += 1; format[j] != '\0'; j++)
{
	if (digit_yes(format[j]))
{
	accuracy *= 10;
	accuracy += format[j] - '0';
}
else if (format[j] == '*')
{
j++;
accuracy = va_arg(list, int);
break;
}
	else
		break;
}
	*i = j - 1;
	return (accuracy);
}
