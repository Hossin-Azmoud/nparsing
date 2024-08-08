#include <nparsing.h>
#include <stdio.h>
float_parts_t *parse_f(char *f)
{
  float_parts_t *parts = malloc(sizeof(*parts)); 

  memset(parts, 0, sizeof(*parts));
  if (f == NULL)
  {
    free(parts);
    return (NULL);
  }
  char *fs = strdup(f);
  (parts->integer).data = (strtok(fs, "."));
  if ((parts->integer).data == NULL || *((parts->integer).data) == 0)
  {
    free(parts);
    return (NULL);
  }
  (parts->integer).size = strlen(parts->integer.data);
  
  (parts->decimal).data = strtok(NULL, ".");
  if ((parts->decimal).data == NULL || *((parts->decimal).data) == 0)
    return (parts);

  (parts->decimal).size = strlen(parts->decimal.data);
  return (parts);
}
float np_atof(char *f)
{

  float_parts_t *fl = parse_f(f);
  long int_ = 0.0f;
  int i = 0;
  float exp_pos = -1;
  float final = 0.0f;

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
  free(fl);
  final += int_;
  return (final);
}

char  *np_ftoa(float f)
{
  assert(0 && "Function np_ftoa is not impl yet.");
}

