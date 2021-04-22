#include <stdio.h>
#include "sigmoid.h"
#include "neuron.h"


int main()
{
  double* input1 = malloc(12 * sizeof(double));
  double* input2 = malloc(6 * sizeof(double));
  double* input3 = malloc(4 * sizeof(double));
  double* error = malloc(100 * sizeof(double));
  double* weight1 = malloc(72 * sizeof(double));
  double* weight2 = malloc(24 * sizeof(double));
  double* biasweight = malloc(10 * sizeof(double));
  struct Neuron *neuronlist1 = malloc(6 * sizeof(struct neuron));
  struct Neuron *neuronlist2 = malloc(4 * sizeof(struct Neuron));


  for (int i = 0; i < 6; i++){
		struct Neuron trans = neuronlist1[i];
		trans.size = 12;
		trans.input = input1;
		trans.weight = weights1 + i*12;
		trans.error = errors + i+12;
		trans.biasWeight = biasWeights + i;
 		randomizeWeights(trans);
		neuronlist1[i] = trans;}

  for (int i = 0; i < 4; i++){
		struct Neuron trans = neuronlist2[i];
		trans.size = 6;
		trans.input = input2;
		trans.weight = weights2 + i*6;
		trans.error = errors + i+6;
		trans.biasWeight = biasWeights + i+6;
 		randomizeWeights(trans);
		neuronlist2[i] = trans;}

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
  }
  free(input1);
  free(input2);
  free(input3);
  free(error);
  free(weight1);
  free(weight2);
  free(biasweight);
  free(neuronlist1);
  free(neuronlist2); 

}
