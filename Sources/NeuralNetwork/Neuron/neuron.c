#include <stdio.h>
#include <stdlib.h>
#include "NeuralNetwork.h"
#include "neuron.h"


//#define MAX(x, y) (((x) > (y)) ? (x) : (y))
double aggregation (struct Neuron N)
{
  double sum = 0;
  for (size_t i = 0; i < N.size; i++)
    sum += N.input[i] * N.weight[i];
  return sum;
}

double linear_activation (struct Neuron N)
{
  double x = aggregation(N);
  return x + *N.biasWeight;
}

double derivate_linear()
{
  return 1;
}

double relu_activation (struct Neuron N)
{
  double x = aggregation(N) + *N.biasWeight;
  if (x >= 0)
    return x;
  else
    return 0;
}

double derivate_relu(struct Neuron N)
{
  double x = aggregation(N) + *N.biasWeight;
  if (x >= 0)
    return 1;
  else
    return 0;
}

double delta_last(struct Neuron *N, double derivate_loss)
{
  return derivate_loss;
}

double delta(struct Network *network, struct Neuron *N, double *next_delta, int size_next_layer, int nb_neuron_prev, int nb)
{
  derivate_activation = derivate_relu(N);

  somme = 0;
  for (long i = 0; i < size_next_layer; i++)
  {
    somme += network->neuron_list[nb_neuron_prev+i].weight[nb] * next_delta[i];
  }
  return derivate_activation * somme;
}

void update(struct Neuron *N, double deltat, double learning_rate)
{
  for(int i = 0; i < N->size; i++)
  {
    N->weight[i] -= deltat*N->input[i]*learning_rate;
  }
  *N->biasWeight -= deltat*learning_rate;
}
