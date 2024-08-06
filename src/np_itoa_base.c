#include <nparsing.h>
#include <stdio.h>

char  *np_itoa_base(int i, char *base)
{
  long num;
  int blength;
  char *asci;
  int nsz;

  if (base == NULL)
    base = BASE_10_ASCII;  
  blength = is_base_valid(base);
  if (blength < 2)
    return strdup("");
  if (i == 0)
    return strdup("0");
  num = i;
  nsz = digit_length_base(num, blength);
  if (i < 0)
    num = -num;
  asci = malloc(nsz + 1);
  asci[nsz--] = 0;
  while (num >= 0) {
    if (num == 0)
      break;
    asci[nsz--] = base[(num % blength)];
    num /= blength;
  }
  if (i < 0)
    asci[nsz] = '-';
  return (asci);
}
