#include <nparsing.h>

int is_base_valid(char *base)
{
  int	i;
	int	j;

	i = 0;
	while (base[i]) {
		j = i + 1;
		while (base[j]) {
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (i);
}

int	find_sym(char sym, char *base)
{
	int	i;	

	i = 0;
	while (base[i])
	{
		if (sym == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int digit_length_base(long num, int base)
{
  int n = 0;
  if (num < 0)
  {
    num = -num;
    n++;
  }
  if (num == 0)
    return (1);

  while (num >= 0)
  {
    if (num == 0)
      return (n);
    num /= base;
    n++;
  }
  return (n);
}
