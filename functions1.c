#include "main.h"

/**
 * print_unsigned - this function prints an unsigned number
 * @types: arguments
 * @buffer:  buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: Number of chars printed.
 */

int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned long int val = va_arg(types, unsigned long int);
	int i;

	i = BUFF_SIZE - 2;
	val = convert_size_unsgnd(val, size);
	if (val == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (val > 0)
	{
		buffer[i--] = (val % 10) + '0';
		val /= 10;
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned long int val = va_arg(types, unsigned long int);
	unsigned long int i_val = val;
	int i;

	i = BUFF_SIZE - 2;
	UNUSED(width);
	val = convert_size_unsgnd(val, size);
	if (val == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (val > 0)
	{
		buffer[i--] = (val % 8) + '0';
		val /= 8;
	}
	if (flags & F_HASH && i_val != 0)
		buffer[i--] = '0';
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - this function prints an unsigned number in hexadecimal
 * @types: arguments list
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: chars printed in hexadecimal
 */

int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - this function prints an unsigned number in
 * upper hexadecimal
 * @types: arguments list
 * @buffer: buffer array for printing
 * @flags: flags
 * @width: width
 * @precision: accuracy
 * @size: size
 * Return: chars printed in upper hexadecimal
 */

int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/**
 * print_hexa - this function prints a hexadecimal number in lower or upper
 * @types: arguments list
 * @map_to: array to map the number to
 * @buffer: buffer array for printing
 * @flags: flags
 * @flag_ch: more flags
 * @width: width
 * @precision:  accuracy
 * @size: size
 * Return: upper or lower hexadecimal char
 */

int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	unsigned long int val = va_arg(types, unsigned long int);
	unsigned long int i_val = val;
	int i;

	i = BUFF_SIZE - 2;
	UNUSED(width);
	val = convert_size_unsgnd(val, size);
	if (val == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (val > 0)
	{
		buffer[i--] = map_to[val % 16];
		val /= 16;
	}
	if (flags & F_HASH && i_val != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
