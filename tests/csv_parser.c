#include <nparsing.h>
#include <stdio.h>
#define NOT_IMPL() fprintf(stderr, "%s: Not implemented yet at line %i\n", __func__, __LINE__)
#define SPACES "\n\t ,"
#define FRAMES_MAX 4096

typedef struct DataFrame {
  char *name;
  size_t size;
  size_t cap;
  float *values;
} DataFrame;

typedef struct Frames {
  char **fields;
  size_t field_count;
  DataFrame Deck[FRAMES_MAX];
  size_t count;
} Frames;

typedef struct s_line {
  char    *data;
  size_t  size;
  size_t  cap;
} line_t;

char **clone(char **memseg)
{
  char **cloned;
  size_t size;

  if (!memseg)
    return (NULL);

  size = 0;
  while (memseg[size] != NULL)
    size++;
  cloned = malloc(sizeof(char *) * size);
  memset(cloned, 0, sizeof(char *) * size);
  if (cloned == NULL)
    return (NULL);
  while (size >= 1)
  {
    cloned[size - 1] = strdup(memseg[size - 1]);
    size--;
  }
  return (cloned);
}

int main(int ac, char **av) {
  Frames frames = {0};
  char **data = NULL;
  DataFrame *datafr = NULL;
  int idx = 0;
  line_t line;

  for (int i = 0; i < FRAMES_MAX; ++i) {
    datafr = frames.Deck + i;
    memset(datafr, 0, sizeof(*datafr));
  }

  if (ac >= 2) {
    printf("Parsing: %s\n", av[1]);
    {
      int fd = open(av[1], O_RDONLY);
      if (fd == -1)
        return (1);
      do {
        line.data = read_next_line(fd);
        if (line.data == NULL)
          break;
        line.size = strlen(line.data);
        data = split(line.data, SPACES);
        if (frames.fields == NULL) {
          frames.fields = clone(data);
          frames.field_count = 0;
          while (frames.fields[frames.field_count] != NULL)
            frames.field_count++;
          printf("Fields parsed %li\n", frames.field_count);
        } else {
          idx = 0;
          datafr = frames.Deck + frames.count;
          datafr->name = strdup(data[idx]);
          while (data[idx]) idx++;
          datafr->values = malloc((frames.field_count + 1) * sizeof(float));
          if (!datafr->values)
          {
            fprintf(stderr, "COULD NOT ALLOCATE MEMORY FOR ITERATION NUMBER: %li\n", frames.count);
            exit(1);
          }
          datafr->cap = frames.field_count;
          idx = 1;
          while (data[idx] && datafr->size < datafr->cap)
            datafr->values[datafr->size++] = atof(data[idx++]);
          frames.count++;
        }
        idx = 0;
        while (data[idx] != NULL)
          free(data[idx++]);
        free(data);
        // free(line.data);
        memset(&line, 0, sizeof(line));
        data = NULL;
      } while (1);
      for (size_t field = 0; field < frames.field_count; field++)
        printf("%s ", frames.fields[field]);
      printf("\n");
      for (size_t i = 0; i < frames.count; i++)
      {
        printf("%s ", frames.Deck[i].name);
        for (size_t j = 0; j < frames.Deck[i].size; j++)
          printf("%f ", frames.Deck[i].values[j]);
        
        printf("\n");
      }
      printf("\n");
    }
    return (0);
  }
  printf("There was not file specified to parse.\n");
  return (1);
}
