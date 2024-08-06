#include <nparsing.h>
#include <assert.h>

char  *np_itoa_base(int i, char *base)
{
  signed long int num;
  int blength = is_base_valid(base);
  char *asci;
  int nsz;
  int iter = 0;
  
  if (blength < 2)
    return strdup("");
  num = i;
  nsz = digit_length_base(num, blength);
  asci = malloc(nsz + 1);
  asci[nsz--] = 0;
  while (num >= 0) {
    asci[nsz--] = base[(num % blength)];
    num /= blength;
    if (num == 0)
      break;
  }
  if (i < 0)
    asci[nsz] = '-';
  return (asci);
}
