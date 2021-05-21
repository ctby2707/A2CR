#include "NeuralNetwork.h"
#include "neuron.h"
#include "saverfile.h"
#include <stddef.h>
#include <stdio.h>

double learning_rate = 0.003;

void control_network(struct Network *network);

void backpropagation(struct Network *network, int *inputs, int out, double derivate_loss)
{
  //------------------------PROPAGATION----------------------------------------
  for(int i = 0; i < network->nb_neuron_layer[0]; i++)
  {
    network->input[i] = (double) inputs[i];
  }
  int bias = 0;
  for(size_t i = 1; i < network->nb_layer; i++)
  {
    for(size_t j = 0; j < network->nb_neuron_layer[i]; j++)
    {
      if(i != network->nb_layer - 1)
      {
        network->input[j+bias+network->nb_neuron_layer[0]] = relu_activation(network->neuron_list[j+bias]);
      }
      else
      {
        network->input[j+bias+network->nb_neuron_layer[0]] = linear_activation(network->neuron_list[j+bias]);
      }
    }
    bias = bias + network->nb_neuron_layer[i];
  }
  //--------------------------BACKPROPAGATION--------------------------------------
  double derivate_cost[] = {0, 0, 0, 0};
  derivate_cost[out] = derivate_loss;

  double delta_last[] = {0, 0, 0, 0};
  for(size_t i = 0; i < 4; i++)
    delta_last[i] = derivate_linear()*derivate_cost[i];

    /*printf("output layer : [");
    for(int i = 0; i < network->nb_neuron_layer[network->nb_layer-1]; i++)
      printf("%lf, ",delta_last[i]);
    printf("]\n");*/

  //control_network(network);
  double delta_layer_3[20];
  for(size_t i = 0; i < 20; i++)
    delta_layer_3[i] = delta(network, &network->neuron_list[60 + i], delta_last, 4, 60+20, i);

    /*printf("layer 3: [");
    for(int i = 0; i < 20; i++)
      printf("%lf, ",delta_layer_3[i]);
    printf("]\n");*/

  double delta_layer_2[60];
  for(size_t i = 0; i < 60; i++)
    delta_layer_2[i] = delta(network, &network->neuron_list[i], delta_layer_3, 20, 60, i);

    /*printf("layer 2: [");
    for(int i = 0; i < 60; i++)
    printf("%lf, ",delta_layer_2[i]);
    printf("]\n");*/
  //-----------------UPDATE WEIGHTS--------------------------------------------
  for(size_t i = 0; i < 4; i++)
    update(&network->neuron_list[60 +20 + i], delta_last[i], learning_rate);

  for(size_t i = 0; i < 20; i++)
    update(&network->neuron_list[60 + i], delta_layer_3[i], learning_rate);

  for(size_t i = 0; i < 60; i++)
    update(&network->neuron_list[i], delta_layer_2[i], learning_rate);
}

void control_network(struct Network *network)
{
  save_Network(network);
  for(size_t i = 0; i < 60 + 20 + 4; i++)
  {
    printf("Layer: %i, Neuron: %i\n",network->neuron_list[i].layer, network->neuron_list[i].nb);
    printf("size = %li\n\n", network->neuron_list[i].size);
  }
}
