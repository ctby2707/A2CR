#include <stdio.h>
#include <stdlib.h>
#include "saverfile.h"
#include <err.h>

void savefile (char* path, double* list, int size)
{
  FILE* file = NULL;
  file = fopen(path, "w");
  for (int i = 0; i < size; i++)
  {
    char character[50];
    sprintf(character, "%lf", list[i]);
    fprintf(file, "%s\n", character);
  }
  fclose(file);
}

void loadfile(char* path, double* list, int size)
{
  FILE* file = NULL;
  file = fopen(path, "r");
  for (int i = 0; i < size; i++)
  {
    int e = fscanf(file, "%lf\n", &list[i]);
    if(e == 0)
    {
      perror("Error in loadfile(): ");
    }
  }
  fclose(file);
}
