#include <nparsing.h>

long np_atoi(char *s)
{
  return (np_atoi_base(s, NULL));
}
