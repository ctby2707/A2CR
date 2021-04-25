#include <stdio.h>
#include <stdlib.h>
#include "saverfile.h"

void savefile (char* path, double* list, int size)
{
  FILE* file = NULL;
  file = fopen(path, "w");
  for (int i = 0; i < size; i++)
  {
    fprintf(file, "%lf\n", list[i]);
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
      break;
    }
  }
  fclose(file);
}
