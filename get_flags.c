#include "main.h"

/**
 * get_flags - this function gets the active flags
 * @format: formatted to print the arguments
 * @i: parameter
 * Return: flags
 */

int get_flags(const char *format, int *i)
{
	int flag, n, x;
	const char FLAG_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAG_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	flag = 0;
	for (x = *i + 1; format[x] != '\0'; x++)
	{
		for (n = 0; FLAG_CH[n] != '\0'; n++)
			if (FLAG_CH[n] == format[x])
			{
				flag |= FLAG_ARR[n];
				break;
			}
		if (FLAG_CH[n] == 0)
			break;
	}
	*i = x - 1;
	return (flag);
}
