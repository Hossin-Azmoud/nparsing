#include <nparsing.h>
#include <stdio.h>
static char *safe_strdup(char *s)
{
  return (s == NULL) ? NULL : strdup(s);
}

float_parts_t *parse_f(char *f)
{
  float_parts_t *parts = malloc(sizeof(*parts)); 
  char *int_, *dec_;
  memset(parts, 0, sizeof(*parts));
  char *copy = safe_strdup(f);
  int_ = strtok(copy, ".");
  (parts->integer).data = safe_strdup(int_);
  if ((parts->integer).data == NULL || *((parts->integer).data) == 0)
  {
    free(parts);
    free(copy);
    return (NULL);
  }
  (parts->integer).size = strlen(parts->integer.data);

  dec_ = strtok(NULL, ".");
  (parts->decimal).data = safe_strdup(dec_);
  free(copy);
  if ((parts->decimal).data == NULL || *((parts->decimal).data) == 0)
    return (parts);
  (parts->decimal).size = strlen(parts->decimal.data);
  return (parts);
}

void free_float_parts_t(float_parts_t *fl)
{
  if (fl) {
    if (fl->decimal.data)
      free(fl->decimal.data);
    if (fl->integer.data)
      free(fl->integer.data);
    free(fl);
  }
}

float np_atof(char *f)
{

  float_parts_t *fl;
  long int_ = 0.0f;
  int i = 0;
  float exp_pos = -1;
  float final = 0.0f;
  if (f == NULL)
    return (final);
  fl = parse_f(f);
  if (fl != NULL)
  {
    int_ = np_atoi_base(fl->integer.data, NULL);
    if (fl->decimal.data) {
      while (i < fl->decimal.size) {
        // printf("Dig: %f ascii: %c\n", (fl->decimal.data[i] - '0') * powf(10.0f, exp_pos), fl->decimal.data[i]);
        final += (fl->decimal.data[i] - '0') * powf(10.0f, exp_pos);
        i++;
        exp_pos--;
      }
    }
  }
  // TODO: free the thingy and return 0.0f
  free_float_parts_t(fl);
  final += int_;
  return (final);
}


char  *np_ftoa(float f)
{
  assert(0 && "Function np_ftoa is not impl yet.");
}

