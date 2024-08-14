#include <nparsing.h>
#include <stdio.h>
#include <string.h>

static char *decimal;
static char *integer;

static char *safe_strdup(char *s)
{
  return (s == NULL) ? NULL : strdup(s);
}

static int parse_f(char *f)
{
  char *int_, *dec_;
  char *copy = safe_strdup(f);
  int_ = strtok(copy, ".");
  integer = safe_strdup(int_);
  if (integer == NULL || *integer == 0)
  {
    free(copy);
    return (0);
  }

  dec_ = strtok(NULL, ".");
  decimal = safe_strdup(dec_);
  free(copy);
  return (1);
}
#define cache 0
#if cache
  static float _prev_out;
  static char *prev_in;
#endif

float np_atof(char *f)
{
  #if cache
    if (prev_in) {
      if (strcmp(prev_in, (const char *)f) == 0)
        return (_prev_out);
    }
    prev_in = f;
  #endif
  long int_ = 0.0f;
  float exp_pos = -1;
  float final = 0.0f;
  char *ptr;
  if (f == NULL)
    return (final);
  decimal = NULL;
  integer = NULL;
  if (parse_f(f)) {
    int_ = np_atoi_base(integer, NULL);
    if (decimal) {
      ptr = decimal;
      while (*ptr) {
        final += (*ptr - '0') * powf(10.0f, exp_pos);
        ptr++;
        exp_pos--;
      }
      free(decimal);
    }
    free(integer);
  }
  final += int_;
  #if cache
    _prev_out = final;
  #endif
  return (final);
}

#define MAX_PRECISON 8
char  *np_ftoa(float f)
{
  int sym_count;
  int j, i;
  char *bf;
  char *int_p;

  sym_count = digit_length_base(f, 10) + MAX_PRECISON;
  bf = malloc(sym_count + 2);
  memset(bf, 0, sym_count + 2);
  int_p = np_itoa_base(f, NULL);
  bf = memcpy(bf, int_p, sym_count - MAX_PRECISON);
  j = (sym_count - MAX_PRECISON);
  f -= (long)f;
  if (f == 0)
    return (bf);
  bf[j++] = '.';
  i = 0;
  while (i < MAX_PRECISON) {
    f -= (long)f;
    f *= 10;
    bf[j++] = (long)(f) + '0';
    i++;
  }
  return (bf);
}

