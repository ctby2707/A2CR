#include <stdio.h>
#include <stdlib.h>

int random_int(int max)
{
  int randval;

  FILE *f;
  f = fopen("/dev/random","r");
  fread(&randval, sizeof(randval), 1, f);
  fclose(f);

  //printf("%i\n",randval);

  randval = randval % max;



  if(randval < 0)
    randval = -randval;

  //printf("%i\n",randval);

  return randval;
}
