#include <stdio.h>
#include <stdlib.h>
#include "NeuralNetwork.h"
#include "neuron.h"
//#define MAX(x, y) (((x) > (y)) ? (x) : (y))

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

double output_last(struct Neuron N)
{
  double somme = 0;
  for (long i = 0; i < N.size; i++)
    somme += N.input[i] * N.weight[i];
  somme  += *N.biasWeight;
  return somme;
}

double delta_last(struct Neuron *N, double derivate_loss)
{
  return derivate_loss;
}

double delta(struct Network *network, struct Neuron *N, double *next_delta, int size_next_layer, int nb_neuron_prev, int nb)
{
  double somme = 0;
  for (long i = 0; i < N->size; i++)
  {
    somme += N->input[i] * N->weight[i];
  }
  somme  += *N->biasWeight;
  double weight_activation = 0;
  if(somme > 0)
    weight_activation = 1;
  somme = 0;
  for (long i = 0; i < size_next_layer; i++)
  {
    somme += network->neuron_list[nb_neuron_prev+i].weight[nb] * next_delta[i];
  }
  return weight_activation * somme;
}

void update(struct Neuron *N, double deltat, double learning_rate)
{
  for(int i = 0; i < N->size; i++)
  {
    N->weight[i] -= deltat*N->input[i]*learning_rate;
  }
  *N->biasWeight -= deltat*learning_rate;
}
