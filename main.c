#include "include/nparsing.h"
#include <stdio.h>
#include <limits.h>
#include <time.h>
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

void Test_np_atof(char *fs, float expected)
{
  float f = np_atof(fs);
  if (f - expected != 0) {
    fprintf(stderr, "[ERROR] expected %f but got %f\n", expected, f);
    err++;
  }
  count++;
}
#define COUNT 100 * 1000
void speed_test_atof()
{
  int count = COUNT;
  const char *n = "0.72873823";
  clock_t s = clock(); 
  double x;
  while (count > 0) {
    x = atof(n);
    count--;
  }
  count = COUNT;
  printf("[x - %f] TOKK ATOF: %.4f ms\n",
x, (clock() - s) * 1000.0 / CLOCKS_PER_SEC);
  s = clock();
  while (count > 0) {
    x = np_atof((char *)n);
    count--;
  }
  printf("[x - %f] TOKK ATOF: %.4f ms\n", x, (clock() - s) * 1000.0 / CLOCKS_PER_SEC);
}

int main()
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
  {
    Test_np_atof("1.2", 1.2f);
    Test_np_atof("232.113230923", 232.113230923f);
    Test_np_atof("10.2", 10.2f);
    Test_np_atof("3.14", 3.14f);
    Test_np_atof("20.27839283929", 20.27839283929f);
    speed_test_atof();
  }
  
  printf("%s\n", np_ftoa(12));
  printf("%s\n", np_ftoa(1.342342));
  printf("%s\n", np_ftoa(1.12));
  printf("%s\n", np_ftoa(0.3 + 0.3 + 0.3));
  printf("=============================\n");
  printf("%.8f\n", (double)(12.1111112222222222222222222222222222222222222));
  printf("%.8f\n", (float)(12.11111122222222222222222222222222222222222222));
  printf("%.8f\n", (1.1));
  printf("%.8f\n", (1.12));
  printf("%.8f\n", (0.3 + 0.3 + 0.3));
  printf("OK: %i%%\n", (count - err) * 100 * 1/count);
  printf("ERR: %i%%\n", (err) * 100 * 1/count);
  return (0);
}
