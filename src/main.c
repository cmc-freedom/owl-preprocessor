#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *USAGE =
"usage: owl FILE ...\n";

typedef char *String;

typedef struct
{
  String string;
  int line;
}
StackRecord;

struct
{
  StackRecord *data;
  size_t real_size, size;
} stack;

void
backtrace (void)
{
  printf("BACKTRACE:\n");
  for (size_t i = 0; i < stack.size; ++ i)
    printf("    %s (%d line)\n", stack.data[i].string, stack.data[i].line);
  printf("\n");
}

void
stop (const String string)
{
  backtrace();
  printf("%s\n", string);
  exit(1);
}

void
append (const String string, int line)
{
  size_t length = strlen(string);
  stack.data[stack.size].line = line;
  stack.data[stack.size].string = (String) malloc(length + 1);
  if (stack.data[stack.size].string == NULL)
    {
      backtrace();
      printf("Cannot realloc memory for append string \"%s\" "
             "to function stack.", string);
      exit(1);
    }
  else
    strcpy(stack.data[stack.size].string, string);

  ++ stack.size;
  if (stack.size == stack.real_size)
    {
      stack.real_size <<= 1;
      StackRecord *data = (StackRecord *)
                            realloc(stack.data,
                                    sizeof(StackRecord) * stack.real_size);
      if (data == NULL)
        {
          -- stack.size;
          stop("Cannot realloc memory for function stack.");
        }
      else
        stack.data = data;
    }
}

#define begin(string) append(string, __LINE__)

void
end (void)
{
  free(stack.data[stack.size].string);
  -- stack.size;
}

void
init (void)
{
  stack.data = (StackRecord *) malloc(sizeof(StackRecord) * 1);
  stack.real_size = 1;
  stack.size = 0;
}

void
preprocess_file (const char *filename)
{
  const char *suffix = ".output";
  const size_t suffix_length = strlen(suffix);

  FILE *fin = fopen(filename, "r");
  if (fin == NULL)
    printf("Cannot open file \"%s\"\n", filename);

  size_t length = strlen(filename);

  char *output_filename = (char *) malloc(length + suffix_length + 1);
  assert(output_filename != NULL);
  strcpy(output_filename, filename);

  for (size_t i = length; i > 0; -- i)
    if (filename[i - 1] == '.')
      {
        -- i;
        for (size_t j = length + suffix_length; j >= i + suffix_length; -- j)
          output_filename[j] = output_filename[j - suffix_length];

        for (size_t j = 0; j < suffix_length; ++ j)
          output_filename[i + j] = suffix[j];
      }
  if (strlen(output_filename) == length)
    strcat(output_filename, suffix);

  FILE *fout = fopen(output_filename, "w");
  if (fin == NULL)
    printf("Cannot open file \"%s\" for writting.", output_filename);

  fclose(fin);
  fclose(fout);
}

int
main(int argc, char **argv)
{
  init();
  begin("main");
  begin("Hello, World!");
  backtrace();
  end();
  backtrace();
  end();
}

