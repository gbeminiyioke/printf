#include "main.h"

/**
 * printable_yes - this function checks if a char is printable
 * @c: char to be evaluated
 * Return: 1 if c is printable, else 0.
 */

int printable_yes(char c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

/**
 * add_hexa_code - this function appends ascii code to buffer
 * in hexadecimal code
 * @buffer: Array of chars
 * @i: Index to start appending
 * @ascii_code: ASCII CODE
 * Return: 3.
 */
int add_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;
	buffer[i++] = '\\';
	buffer[i++] = 'x';
	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];
	return (3);
}

/**
 * digit_yes - YTHIS FUNCTION Verifies if a char is a digit
 * @c: Char to evaluated
 * Return: 1 if c is a digit, else 0.
 */
int digit_yes(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * cnvrt_sz_unsgnd - this function casts a number to the specified size
 * @num: Number to be casted
 * @size: size
 * Return: value of num
 */
long int cnvrt_sz_unsgnd(unsigned long int num, int size)
{
	if (size == SZ_LNG)
		return (num);
	else if (size == SZ_SHRT)
		return ((unsigned short)num);
	return ((unsigned int)num);
}

/**
 * cnvrt_sz_num - this function casts a number to the specified size
 * @num: Number to be casted.
 * @size: size
 * Return: value of num
 */

long int cnvrt_sz_num(long int num, int size)
{
	if (size == SZ_LNG)
		return (num);
	else if (size == SZ_SHRT)
		return ((short)num);
	return ((int)num);
}
