#ifndef NEURON_H
#define NEURON_H

struct Neuron
{
  long size;
  double *input;
  double *weight;
  double *biasWeight;
};

double output(struct Neuron N);

#endif
