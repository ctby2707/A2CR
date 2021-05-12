#include "NeuralNetwork.h"
#include "neuron.h"
#include "saverfile.h"
#include <stddef.h>
#include <stdio.h>

double learning_rate = 0.003;



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
  double last_delta[network->nb_neuron_layer[network->nb_layer-1]];
  for(int i = 0; i < network->nb_neuron_layer[network->nb_layer-1]; i++)
  {
    last_delta[i] = 0;
  }

  int nb_total_neuron = 0;
  for(size_t i = 1; i < network->nb_layer-1; i++)
  {
    nb_total_neuron += network->nb_neuron_layer[i];
  }
  last_delta[out] = delta_last(&network->neuron_list[nb_total_neuron+out], derivate_loss);
  for(size_t i = 0; i < 4; i++)
  {
    update(&network->neuron_list[60 +20 + i], last_delta[i], learning_rate);
  }

  /*printf("output layer : [");
    for(int i = 0; i < network->nb_neuron_layer[network->nb_layer-1]; i++)
    printf("%lf, ",last_delta[i]);
    printf("]\n");*/

  double delta_layer_3[20];
  for(size_t i = 0; i < 20; i++)
  {
    delta_layer_3[i] = delta(network, &network->neuron_list[60 + i], last_delta, 4, 60+20, i);
    update(&network->neuron_list[60 + i], delta_layer_3[i], learning_rate);
  }

  /*printf("layer 3: [");
    for(int i = 0; i < 20; i++)
    printf("%lf, ",delta_layer_3[i]);
    printf("]\n");
    return;*/

  double delta_layer_2[60];
  for(size_t i = 0; i < 60; i++)
  {
    delta_layer_2[i] = delta(network, &network->neuron_list[i], delta_layer_3, 20, 60, i);
    update(&network->neuron_list[i], delta_layer_2[i], learning_rate);
  }

  /*printf("layer 2: [");
    for(int i = 0; i < 60; i++)
    printf("%lf, ",delta_layer_2[i]);
    printf("]\n");*/

}
