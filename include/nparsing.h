#ifndef NPARSING_H
#define NPARSING_H

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#define BASE_16_ASCII     "0123456789abcdef"
#define BASE_16_ASCII_UP  "0123456789abcdef"
#define BASE_10_ASCII     "0123456789"
#define BASE_BIN_ASCII    "01"

#define BASE_16_PREFIX      "0X"
#define BASE_16_PREFIX_UP   "0x"
#define BASE_BIN_PREFIX     "0b"

#define MAX_FLOAT_PRECISON 6
long np_atoi_base(char *a, char *base);
float np_atof(char *a);
char  *np_ftoa(float f);
char  *np_itoa_base(int i, char *base);
char *np_itoa(int m);
long np_atoi(char *s);
int	find_sym(char sym, char *base);
int is_base_valid(char *base);
int digit_length_base(long num, int base);
int count_number_syms(double f);
char	**split(char *str, char *charset);
char *read_next_line(int fd);
#endif // NPARSING_H
