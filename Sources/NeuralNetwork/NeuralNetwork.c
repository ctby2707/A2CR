#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "neuron.h"
#include "saverfile.h"
#include "NeuralNetwork.h"
#include "GTK.h"
#include "loop.h"
#include "random.h"

struct Network init(int nb_layer, int *nb_neuron)
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
      network->nb_weights[i-1] = (nb_neuron[i-1] * nb_neuron[i]);
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
  return *network;
}
<<<<<<< HEAD

char execute_network(struct Network *network, int *inputs,int index_val, double *value, Game *game)
{

  //enter the input
  for(int i = 0; i < network->nb_neuron_layer[0]; i++)
  {
    network->input[i] = (double) inputs[i];
=======
char execute_network(struct Network *network, double *inputs)
{
  //enter the input
  for(int i = 0; i < network->nb_neuron_layer[0]; i++)
  {
    network->input[i] = inputs[i];
>>>>>>> remi
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
<<<<<<< HEAD
    nb_total_neuron += network->nb_neuron_layer[i];
=======
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
>>>>>>> remi
  }
  int index = 0;
  if(network->input[nb_total_neuron+index] < network->input[nb_total_neuron+1])
    index = 1;
  if(network->input[nb_total_neuron+index] < network->input[nb_total_neuron+2])
    index = 2;
  if(network->input[nb_total_neuron+index] < network->input[nb_total_neuron+3])
    index = 3;
<<<<<<< HEAD
  *value = network->input[nb_total_neuron+index_val];
=======
  //----------DEBUGGING FUNCTION---------------
  /*printf("index = %d\n",index);
    printf("N : %f\n",network->input[nb_total_neuron]);
    printf("S : %f\n",network->input[nb_total_neuron+1]);
    printf("G : %f\n",network->input[nb_total_neuron+2]);
    printf("D : %f\n",network->input[nb_total_neuron+3]);
    printf("______________________________________________\n");*/
>>>>>>> remi
  if(index == 0)
    return 'N';
  if(index == 1)
    return 'S';
  if(index == 2)
<<<<<<< HEAD
    return 'W';
  return 'E';
=======
    return 'G';
  return 'D';
>>>>>>> remi
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
<<<<<<< HEAD
    double div = 123456789 / range;
    network->weights[i] = -1 + (random_int(123456789) / div);
=======
    double div = RAND_MAX / range;
    network->weights[i] = -1 + (rand() / div);
>>>>>>> remi
  }
  int nb_total_neuron = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }//calculate the size of the biasWeight list

  for(size_t i = 0; i < nb_total_neuron; i++)
  {
    double range = 2;
<<<<<<< HEAD
    double div = 123456789 / range;
    network->biasWeights[i] = -1 + (random_int(123456789) / div);
  }
}

void save_Network(struct Network *network)
=======
    double div = RAND_MAX / range;
    network->biasWeights[i] = -1 + (rand() / div);
  }
}

void save_Network(struct Network *network, int child)
>>>>>>> remi
{
  int nb_total_neuron = 0;
  for(size_t i = 0; i < network->nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }
  int size_weight_list = 0;

  for(size_t i = 1; i < network->nb_layer; i++)
  {
    size_weight_list = size_weight_list + (network->nb_neuron_layer[i-1] *
        network->nb_neuron_layer[i]);
  }//calculate the size of the weight list
<<<<<<< HEAD
  char string1[] = "Data/NeuralData/weights.txt";
  char string2[] = "Data/NeuralData/biasWeights.txt";
=======
  char string1[] = "Data/NeuralData/weights0.txt";
  char string2[] = "Data/NeuralData/biasWeights0.txt";
  char nb[] = "0";
  sprintf(nb, "%d", child);
  string1[23] = nb[0];
  string2[27] = nb[0];
>>>>>>> remi

  savefile(string1, network->weights, size_weight_list);
  savefile(string2, network->biasWeights,
      nb_total_neuron-network->nb_neuron_layer[0]);
}

<<<<<<< HEAD
void load_Newtwork(struct Network *network)
=======
void load_Newtwork(struct Network *network, int child)
>>>>>>> remi
{
  int nb_total_neuron = 0;
  for(size_t i = 0; i < network->nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }
  int size_weight_list = 0;

  for(size_t i = 1; i < network->nb_layer; i++)
  {
    size_weight_list = size_weight_list + (network->nb_neuron_layer[i-1] *
        network->nb_neuron_layer[i]);
  }//calculate the size of the weight list
<<<<<<< HEAD
  char string1[] = "Data/NeuralData/weights.txt";
  char string2[] = "Data/NeuralData/biasWeights.txt";
=======
  char string1[] = "Data/NeuralData/weights0.txt";
  char string2[] = "Data/NeuralData/biasWeights0.txt";
  char nb[] = "0";
  sprintf(nb, "%d", child);
  string1[23] = nb[0];
  string2[27] = nb[0];
>>>>>>> remi

  loadfile(string1, network->weights, size_weight_list);
  loadfile(string2, network->biasWeights,
      nb_total_neuron-network->nb_neuron_layer[0]);
}

<<<<<<< HEAD
=======
void adjust_Network(struct Network *network)
{
  int size_weight_list = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    size_weight_list = size_weight_list + (network->nb_neuron_layer[i-1] * network->nb_neuron_layer[i]);
  }//calculate the size of the weight list
  int nb_total_neuron = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    nb_total_neuron = nb_total_neuron + network->nb_neuron_layer[i];
  }//calculate the size of the biasWeight list

  weight_set(network->weights, INTERVALLE, size_weight_list);
  weight_set(network->biasWeights, INTERVALLE, nb_total_neuron);
}

void weight_set(double *weight, double x, size_t size_tab)
{
  for(size_t i = 0; i < size_tab; i++)
  {
    if(weight[i] == -0)
      weight[i] = 0.000001;
    double min = weight[i] - x;
    double max = weight[i] + x;
    if (min < -1)
      min = -1;
    if (max > 1)
      max = 1;
    double range = (max - min);
    double div = RAND_MAX / range;
    weight[i] = min + (rand() / div);
  }
}
>>>>>>> remi
