#include "main.h"

/**
 * is_printable - this function checks if a char is printable
 * @c: Char to evaluate.
 * Return: 1 if printable, else 0.
 */

int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}

/**
 * append_hexa_code - this function appends asci in hexadecimal
 * code tothe  buffer
 * @buffer: buffer array
 * @i: Index
 * @ascii_code: ASCI CODE.
 * Return: 3.
 */

int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;
	buffer[i++] = '\\';
	buffer[i++] = 'x';
	buffer[i++] = map[ascii_code / 16];
	buffer[i] = map[ascii_code % 16];
	return (3);
}

/**
 * is_digit - this function checks if a char is a digit
 * @c: char to evaluate
 * Return: 1 if it is a digit, else 0.
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/**
 * convert_size_number - this function casts a number to the specified size
 * @num: number to cast
 * @size: size
 * Return: value casted
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);
	return ((int)num);
}

/**
 * convert_size_unsgnd - this function casts a number to the specified size
 * @num: number to cast
 * @size: size
 * Return: the value casted
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);
	return ((unsigned int)num);
}
