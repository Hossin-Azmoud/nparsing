#include <nparsing.h>

char  *np_ftoa(float f)
{
  int sym_count;
  int j, i;
  char *bf;
  char *int_p;

  sym_count = digit_length_base(f, 10) + MAX_FLOAT_PRECISON;
  bf = malloc(sym_count + 2);
  memset(bf, 0, sym_count + 2);
  int_p = np_itoa_base(f, NULL);
  bf = memcpy(bf, int_p, sym_count - MAX_FLOAT_PRECISON);
  j = (sym_count - MAX_FLOAT_PRECISON);
  f -= (long)f;
  if (f == 0)
    return (bf);
  bf[j++] = '.';
  i = 0;

  while (i < MAX_FLOAT_PRECISON) {
    f -= (long)f;
    f *= 10;
    bf[j++] = (long)(f) + '0';
    i++;
  }
  return (bf);
}

