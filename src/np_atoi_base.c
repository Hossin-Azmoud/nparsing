#include <nparsing.h>

signed long int np_atoi_base(char *a, char *base)
{
  signed long int num;
  int blen;
  int sign;
  int iter;

  blen = is_base_valid(base);
  if (blen < 2) return (0);
  num = 0;
  iter = 0;
  sign = 1;
  while (a[iter] == '-' || a[iter] == '+' || isspace(a[iter])) {
    if (a[iter] == '-')
      sign *= -1;
    iter++;
  }
  int sym_idx = find_sym(a[iter], base);
  while (sym_idx >= 0) {
    num *= blen;
    num += sym_idx;
    sym_idx = find_sym(a[++iter], base);
  }
  return (num * sign);
}
