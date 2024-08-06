#include <stdio.h>
#include <limits.h>
#include <nparsing.h>
// NOTE: This is for tests.
static int count = 0;
static int err = 0;

void Test_np_atoi(char *nbr, char *base, long expected)
{
  long r = np_atoi_base(nbr, base);
  if (r != expected) {
    fprintf(stderr, "[ERROR] expected %ld but got %ld\n", expected, r);
    err++;
  }
  count++;
}

void Test_np_itoa(long nbr, char *base, char *expected)
{
  char *r = np_itoa_base(nbr, base);
  if (strcmp(expected, r) != 0) {
    fprintf(stderr, "[ERROR] expected %s but got %s\n", expected, r);
    err++;
  }
  free(r);
  count++;
}

int main(int ac, char **av)
{
  {
    // ATOI TESTS,
    Test_np_atoi("0xff", NULL, 255);
    Test_np_atoi("0x7fffffff", NULL, INT_MAX);
    Test_np_atoi("-0x80000000", NULL, INT_MIN);
  }
  {
    // ITOA TESTS
    Test_np_itoa(0xff, BASE_16_ASCII, "ff");
    Test_np_itoa(0x7fffffff, BASE_16_ASCII, "7fffffff");
    Test_np_itoa(-0x80000000, BASE_16_ASCII, "-80000000");
  }

  printf("OK: %i%%\n", (count - err) * 100 * 1/count);
  printf("ERR: %i%%\n", (err) * 100 * 1/count);
  return (0);
}
