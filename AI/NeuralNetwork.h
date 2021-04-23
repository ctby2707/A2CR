#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <stddef.h>
#include "neuron.h"

struct Network {
  int nb_layer;
  int *nb_neuron_layer; //contains the numbers of neurons per layer
  struct Neuron *neuron_list;
  double *input;
  int *nb_weights; //contains the numbers of weights per layer
  double *weights;
  double *biasWeights;
};

struct Network *init(int nb_layer, int *nb_neuron);
char execute_network(struct Network *network, double *inputs);
void destroy_network(struct Network *network);
void randomizeNetwork(struct Network *network);
void save_Network(struct Network *network);

#endif

