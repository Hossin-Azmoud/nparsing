#include <stdio.h>
#include <nparsing.h>

int main(int ac, char **av)
{
	if (ac == 3)
  {
    signed long int x = np_atoi_base(av[1], av[2]);
    printf("Hello %s -> %ld\n", av[1], x);  
  }
  return (0);
}
