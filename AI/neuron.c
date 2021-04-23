#include <stdio.h>
#include <stdlib.h>
#include "sigmoid.h"
#include "neuron.h"

double output(struct Neuron N)
{
  double forsig = 0;
  double *in = N.input;
  double *we = N.weight;
  for (long i = 0; i < N.size; i++)
  {
    forsig += *in * *we;
    in++;
    we++;
  }
  forsig += *N.biasWeight;
  double out = sigmoid(forsig);
  return out;
}

