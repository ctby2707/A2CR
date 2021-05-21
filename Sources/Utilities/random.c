#include <stdio.h>
#include <stdlib.h>

int random_int(int max)
{

  if ((max - 1) == RAND_MAX) {
    return rand();
  } else {
    // Supporting larger values for n would requires an even more
    // elaborate implementation that combines multiple calls to rand()

    // Chop off all of the values that would cause skew...
    int end = RAND_MAX / max; // truncate skew
    end *= max;

    // ... and ignore results from rand() that fall above that limit.
    // (Worst case the loop condition should succeed 50% of the time,
    // so we can expect to bail out of this loop pretty quickly.)
    int r;
    while ((r = rand()) >= end);

    return r % max;
  }
/*
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

  return randval;*/
}
