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
  int nb_layer = 3;
  int *nb_neuron = malloc(nb_layer*sizeof(int));
  nb_neuron[0] = NB_INPUT;
  nb_neuron[1] = NB_NEURON_LAYER_1;
  nb_neuron[3] = NB_NEURON_LAYER_2;

  double input[] = {0.95678,
                    0.87654,
                    0.95678,
                    0.97654,
                    0.96543,
                    0.76546,
                    0.96543,
                    0.98765,
                    0.93456,
                    0.23456,
                    0.96543,
                    0.87654};
  struct Network *network = init(nb_layer, nb_neuron);
  randomizeNetwork(network);
  printf("%c\n",execute_network(network, input));
  save_Network(network);
  destroy_network(network);
}

struct Network *init(int nb_layer, int *nb_neuron)
{
  struct Network *network = malloc(sizeof(struct Network));
  network->nb_layer = nb_layer;
  network->nb_neuron_layer = nb_neuron;

  int nb_total_neuron = 0;
  int size_weight_list = 0;

  int *nb_weights = malloc((nb_layer-1)*sizeof(int));
  network->nb_weights = nb_weights; //list of nb weight for each layers

  for(size_t i = 0; i < nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + nb_neuron[i];
    if(i != 0)
    {
      size_weight_list = size_weight_list + (nb_neuron[i-1] * nb_neuron[i]);
      network->nb_weights[i] = (nb_neuron[i-1] * nb_neuron[i]);
    }
  }
  double *input = malloc(nb_total_neuron*sizeof(double));
  network->input = input;

  double *weights = malloc(size_weight_list*sizeof(double));
  network->weights = weights;

  double *biasWeights = malloc((nb_total_neuron - nb_neuron[0])*sizeof(double));
  network->biasWeights = biasWeights;

  struct Neuron *neuron_list = malloc((nb_total_neuron - nb_neuron[0])*sizeof(struct Neuron));
  network->neuron_list = neuron_list;

  int bias = 0;
  for(size_t i = 1; i < nb_layer; i++)
  {
    for(size_t j = 0; j < nb_neuron[i]; j++)
    {
      network->neuron_list[j+bias].size = nb_neuron[i-1];
      network->neuron_list[j+bias].input = network->input + bias;
      network->neuron_list[j+bias].weight = network->weights + j*nb_neuron[i-1] + bias;
      network->neuron_list[j+bias].biasWeight = network->biasWeights + j + bias;
    }
    bias = bias + nb_neuron[i];
  }
  return network;
}
char execute_network(struct Network *network, double *inputs)
{
  //enter the input
  for(int i = 0; i < network->nb_neuron_layer[0]; i++)
  {
    network->input[i] = inputs[i];
  }

  //execute the network
  int bias = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    for(size_t j = 0; j < network->nb_neuron_layer[i]; j++)
    {
      network->input[j+bias+network->nb_neuron_layer[0]] = output(network->neuron_list[j+bias]);
    }
    bias = bias + network->nb_neuron_layer[i];
  }

  int nb_total_neuron = 0;
  for(size_t i = 0; i < (network->nb_layer-1); i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }
  int index = 0;
  if(network->input[nb_total_neuron+index] < network->input[nb_total_neuron+1])
    index = 1;
  if(network->input[nb_total_neuron+index] < network->input[nb_total_neuron+2])
    index = 2;
  if(network->input[nb_total_neuron+index] < network->input[nb_total_neuron+3])
    index = 3;

  if(index == 0)
    return 'N';
  if(index == 1)
    return 'S';
  if(index == 2)
    return 'G';
  return 'D';
}
void destroy_network(struct Network *network)
{
  free(network->nb_neuron_layer);
  free(network->neuron_list);
  free(network->input);
  free(network->nb_weights);
  free(network->weights);
  free(network->biasWeights);
  free(network);
}

//define random valuer between -1 and 1 on Network
void randomizeNetwork(struct Network *network)
{
  int size_weight_list = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    size_weight_list = size_weight_list + (network->nb_neuron_layer[i-1] * network->nb_neuron_layer[i]);
  }//calculate the size of the weight list

  for(size_t i = 0; i < size_weight_list; i++)
  {
    double range = 2;
    double div = RAND_MAX / range;
    network->weights[i] = -1 + (rand() / div);
  }
  int nb_total_neuron = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }//calculate the size of the biasWeight list

  for(size_t i = 0; i < nb_total_neuron; i++)
  {
    double range = 2;
    double div = RAND_MAX / range;
    network->biasWeights[i] = -1 + (rand() / div);
  }
}

void save_Network(struct Network *network)
{
  int nb_total_neuron = 0;
  for(size_t i = 0; i < network->nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }
  savefile("NeuralData/input.txt", network->input, nb_total_neuron);
  int size_weight_list = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    size_weight_list = size_weight_list + (network->nb_neuron_layer[i-1] *
                                            network->nb_neuron_layer[i]);
  }//calculate the size of the weight list
  savefile("NeuralData/weights.txt", network->weights, size_weight_list);
  savefile("NeuralData/biasWeight.txt", network->biasWeights,
          nb_total_neuron-network->nb_neuron_layer[0]);
}
