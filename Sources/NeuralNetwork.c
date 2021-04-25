#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include "sigmoid.h"
#include "neuron.h"
#include "saverfile.h"
#include "NeuralNetwork.h"
#include "pac-man.h"
#include "NeuralNetworks_Detections.h"

#define NB_INPUT 17
#define NB_NEURON_LAYER_1 6
#define NB_NEURON_LAYER_2 6
#define NB_NEURON_LAYER_3 4

#define INTERVALLE 0.1
#define DIST 5

char Call_Neural_Network(Game *game)
{
  double input[17];
  //potential direction of pac-man
  int X, Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int Xb, Yb; //ghostpos
  pixel_To_MatCoord(game->blinky.x, game->blinky.y, &Xb, &Yb);
  int Xi, Yi;
  pixel_To_MatCoord(game->inky.x, game->inky.y, &Xi, &Yi);
  int Xc, Yc;
  pixel_To_MatCoord(game->clyde.x, game->clyde.y, &Xc, &Yc);
  int Xp, Yp;
  pixel_To_MatCoord(game->pinky.x, game->pinky.y, &Xp, &Yp);

  if(X*28+Y-28 > 0 && game->map[X*28+Y-28] != 0)
  {
    input[0] = 1; //north is not a wall
    input[4] = find_pac_gum(game->map, X*28+Y, X*28+Y-28, DIST, 2);//search pac-gum
    input[8] = find_pac_gum(game->map, X*28+Y, X*28+Y-28, DIST, 3);//super pac-gum
    input[12] = find_ghost(game->map, X*28+Y, X*28+Y-28, DIST, Xb*28+Yb,
                          Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  }
  else
  {
    input[0] = 0;
    input[4] = 0;
    input[8] = 0;
    input[12] = 0;
  }
  if(X*28+Y+28 < 868 && game->map[X*28+Y+28] != 0)
  {
    input[1] = 1; //south is not a wall
    input[5] = find_pac_gum(game->map, X*28+Y, X*28+Y+28, DIST, 2);
    input[9] = find_pac_gum(game->map, X*28+Y, X*28+Y+28, DIST, 3);
    input[13] = find_ghost(game->map, X*28+Y, X*28+Y+28, DIST, Xb*28+Yb,
                          Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  }
  else
  {
    input[1] = 0;
    input[5] = 0;
    input[9] = 0;
    input[13] = 0;
  }
  if(X*28+Y-1 > 0 && game->map[X*28+Y-1] != 0)
  {
    input[2] = 1; //west is not a wall
    input[6] = find_pac_gum(game->map, X*28+Y, X*28+Y-1, DIST, 2);
    input[10] = find_pac_gum(game->map, X*28+Y, X*28+Y-1, DIST, 3);
    input[14] = find_ghost(game->map, X*28+Y, X*28+Y-1, DIST, Xb*28+Yb,
                          Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  }
  else
  {
    input[2] = 0;
    input[6] = 0;
    input[10] = 0;
    input[14] = 0;
  }
  if(X*28+Y+1 < 868 && game->map[X*28+Y+1] != 0)
  {
    input[3] = 1; //est is not a wall
    input[7] = find_pac_gum(game->map, X*28+Y, X*28+Y+1, DIST, 2);
    input[11] = find_pac_gum(game->map, X*28+Y, X*28+Y+1, DIST, 3);
    input[15] = find_ghost(game->map, X*28+Y, X*28+Y+1, DIST, Xb*28+Yb,
                          Xi*28+Yi, Xc*28+Yc, Xp*28+Yp);
  }
  else
  {
    input[3] = 0;
    input[7] = 0;
    input[11] = 0;
    input[15] = 0;
  }
  input[16] = game->chase /170;
  return execute_network(&game->AI[game->index], input);
}

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
  return *network;
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

void save_Network(struct Network *network, int child)
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
  char string1[] = "NeuralData/weights0.txt";
  char string2[] = "NeuralData/biasWeights0.txt";
  char nb[] = "0";
  sprintf(nb, "%d", child);
  string1[18] = nb[0];
  string2[22] = nb[0];

  savefile(string1, network->weights, size_weight_list);
  savefile(string2, network->biasWeights,
          nb_total_neuron-network->nb_neuron_layer[0]);
}

void load_Newtwork(struct Network *network, int child)
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
  char string1[] = "NeuralData/weights0.txt";
  char string2[] = "NeuralData/biasWeights0.txt";
  char nb[] = "0";
  sprintf(nb, "%d", child);
  string1[18] = nb[0];
  string2[22] = nb[0];

  loadfile(string1, network->weights, size_weight_list);
  loadfile(string2, network->biasWeights,
          nb_total_neuron-network->nb_neuron_layer[0]);
}

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

  weight_set(network->biasWeights, INTERVALLE, nb_total_neuron);
  weight_set(network->weights, INTERVALLE, size_weight_list);
}

void weight_set(double *weight, double x, size_t size_tab)
{
  for(size_t i = 0; i < size_tab; i++)
  {
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
