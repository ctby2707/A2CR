#include <stdio.h>
#include <stdlib.h>
#include "neuron.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

double output(struct Neuron N)
{
  double somme = 0;
  for (long i = 0; i < N.size; i++)
  {
    somme += N.input[i] * N.weight[i];
  }
  somme  += *N.biasWeight;
  return MAX(0,somme);
}

