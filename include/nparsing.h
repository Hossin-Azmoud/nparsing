#ifndef NPARSING_H
#define NPARSING_H

#include <stdlib.h>
#include <ctype.h>
#define BASE_16_ASCII   "0123456789abcdef"
#define BASE_10_ASCII   "0123456789"
#define BASE_BIN_ASCII  "01"

signed long int np_atoi_base(char *a, char *base);
float np_atof(char *a);
char  *np_ftoa(float f);
char  *np_itoa_base(int i, char *base);

// UTIL FUNCTIONS TO WORK WITH.
int	find_sym(char sym, char *base);
int is_base_valid(char *base);
int digit_length_base(signed long int num, int base);

#endif // NPARSING_H
