#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *USAGE =
"usage: owl FILE ...\n";

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
  if (argc == 1)
    printf("%s", USAGE);
  else
    for (int i = 1; i < argc; ++i)
      preprocess_file(argv[i]);
}

