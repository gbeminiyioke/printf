#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define SZ_LNG 2
#define SZ_SHRT 1

#define FLAG_SPACE 16
#define FLAG_HASH 8
#define FLAG_ZERO 4
#define FLAG_MINUS 1
#define FLAG_PLUS 2

#define BUFFER_SIZE 1024
#define NOT_USED(x) (void)(x)

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i, va_list list, char buffer[],
		int flags, int width, int precision, int size);
int prnt_char(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_str(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_int(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_hexadec(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_hexadec_upr(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_hexa(va_list types, char map_to[], char buffer[], int flags,
		char flag_ch, int width, int precision, int size);
int prnt_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int prnt_pntr(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
int prnt_rvsr(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
		int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
		int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start);
int write_unsgnd(int negative_num, int ind, char buffer[],
		int flags, int width, int precision, int size);

/**
 * struct fmt - structure
 * @fmt: format
 * @fn: associated function
 */

struct fmt
{
	char fmt;

	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - structure
 * @fmt: format
 * @fmt_t: associated function
 */

typedef struct fmt fmt_t;

int printable_yes(char);
int add_hexa_code(char, char[], int);
int digit_yes(char);

long int cnvrt_sz_num(long int num, int size);
long int cnvrt_sz_unsgnd(unsigned long int num, int size);

#endif
