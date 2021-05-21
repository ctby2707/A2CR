#ifndef NEURON_H
#define NEURON_H


struct Neuron
{
  size_t size;
  double *input;
  double *weight;
  double *biasWeight;
  int layer;
  int nb;
};
double aggregation(struct Neuron N);
double linear_activation(struct Neuron N);
double derivate_linear();
double relu_activation(struct Neuron N);
double derivate_relu(struct Neuron N);
double output(struct Neuron N);
double output_last(struct Neuron N);
double delta_last(struct Neuron *N, double derivate_loss);
double delta(struct Network *network, struct Neuron *N, double *next_delta, int size_next_layer, int nb_neuron_prev, int nb);
void update(struct Neuron *N, double delta, double learning_rate);

#endif
