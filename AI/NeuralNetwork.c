#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "sigmoid.h"
#include "neuron.h"
#include "saverfile.h"
#include "NeuralNetwork.h"

#define NB_INPUT 12
#define NB_NEURON_LAYER_1 6
#define NB_NEURON_LAYER_2 4

int main()
{
  double* input1 = malloc(NB_INPUT * sizeof(double));
  double* input2 = malloc(NB_NEURON_LAYER_1 * sizeof(double));
  double* input3 = malloc(NB_NEURON_LAYER_2 * sizeof(double));

  double* weights1 = malloc(NB_INPUT * NB_NEURON_LAYER_1 * sizeof(double));
  double* weights2 = malloc(NB_NEURON_LAYER_1 * NB_NEURON_LAYER_2 * sizeof(double));
  double* biasWeights = malloc((NB_NEURON_LAYER_1 + NB_NEURON_LAYER_2) * sizeof(double));

  struct Neuron *neuronlist1 = malloc(NB_NEURON_LAYER_1 * sizeof(struct Neuron));
  struct Neuron *neuronlist2 = malloc(NB_NEURON_LAYER_2 * sizeof(struct Neuron));

  randomizeNetwork(weights1, NB_INPUT * NB_NEURON_LAYER_1);
  randomizeNetwork(weights2, NB_NEURON_LAYER_1 * NB_NEURON_LAYER_2);
  randomizeNetwork(biasWeights, NB_NEURON_LAYER_1 + NB_NEURON_LAYER_2);

  //initialize hidden layer
  for (int i = 0; i < NB_NEURON_LAYER_1; i++)
  {
    struct Neuron trans = neuronlist1[i];
    trans.size = NB_INPUT;
    trans.input = input1;
    trans.weight = weights1 + i*NB_INPUT;
    trans.biasWeight = biasWeights + i;
    neuronlist1[i] = trans;
  }

  //initialize output layer
  for (int i = 0; i < NB_NEURON_LAYER_2; i++)
  {
    struct Neuron trans = neuronlist2[i];
    trans.size = NB_NEURON_LAYER_1;
    trans.input = input2;
    trans.weight = weights2 + i*NB_NEURON_LAYER_1;
    trans.biasWeight = biasWeights + i+NB_NEURON_LAYER_1;
    neuronlist2[i] = trans;
  }

  /* training function
  int epoc = 0
  while(epoc < 800)
  {
    for (int i = 0; i < 6; i++)
    {
      input2[i] = output(neuronlist1[i]);
      adjust10Weight(neuronlist1[i]);
    }
    for (int i = 0; i < 4; i++)
    {
      input3[i] = output(neuronlist2[i]);
      adjust10Weight(neuronlist2[i]);
    }

    epoc++;
  }*/

  savefile("NeuralData/save_biaisweight.txt", biasWeights, NB_NEURON_LAYER_1 + NB_NEURON_LAYER_2);
  savefile("NeuralData/save_weight1.txt", weights1, NB_INPUT * NB_NEURON_LAYER_1);
  savefile("NeuralData/save_weight2.txt", weights2, NB_NEURON_LAYER_1 * NB_NEURON_LAYER_2);

  free(input1);
  free(input2);
  free(input3);
  free(weights1);
  free(weights2);
  free(biasWeights);
  free(neuronlist1);
  free(neuronlist2);
}

//define random valuer between -1 and 1 on tab
void randomizeNetwork(double *tab, size_t size)
{
  for(size_t i = 0; i < size; i++)
  {
    double range = (2);
    double div = RAND_MAX / range;
    tab[i] = -1 + (rand() / div);
  }
}
