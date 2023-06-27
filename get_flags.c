#include "main.h"

/**
 * get_flags: Get the flags for formatting arguments.
 * @format: Format string
 * @i: pointer to parameter
 * Return: Flags
 */
int get_flags(const char *format, int *i)
{
int n_flag, c, j;
const char C_FLAGS[] = {'-', '+', '0', '#', ' ', '\0'};
const int AR_FLAGS[] = {
FLAG_MINUS, FLAG_PLUS, FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0
};

n_flag = 0;
for (j = *i + 1; format[j] != '\0'; j++)
{
	for (c = 0; C_FLAGS[c] != '\0'; j++)
{
	if (format[j] == C_FLAGS[c])
{
	n_flag |= AR_FLAGS[c];
	break;
}
}
		if (C_FLAGS[c] == 0)
			break;
}

	*i = j - 1;

	return (n_flag);
}
