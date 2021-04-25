#include "NeuralNetwork.h"
#include <stdlib.h>
#include "pac-man.h"
#include "NeuralNetworks_manager.h"
#include <math.h>

#define NB_INPUT 17
#define NB_NEURON_LAYER_1 6
#define NB_NEURON_LAYER_2 6
#define NB_NEURON_LAYER_3 4

void generate_random_generation(int nb_child, Game *game, int type)
{
  game->AI = malloc(nb_child*sizeof(struct Network));
  game->scoreAI = calloc(nb_child,sizeof(int));
  for(size_t i = 0; i < nb_child; i++)
  {
    int nb_layer = 4;
    int *nb_neuron = malloc(nb_layer*sizeof(int));
    nb_neuron[0] = NB_INPUT;
    nb_neuron[1] = NB_NEURON_LAYER_1;
    nb_neuron[2] = NB_NEURON_LAYER_2;
    nb_neuron[3] = NB_NEURON_LAYER_3;
    game->AI[i] = init(nb_layer, nb_neuron);
    randomizeNetwork(&game->AI[i]);
  }
  if(type == 0)
    generate_generation(nb_child, game);
}

void new_generation(int nb_child, Game *game)
{
  save_generation(nb_child, game);
  generate_generation(nb_child, game);
}

void save_generation(int nb_child, Game *game)
{
  int tab[nb_child];
  for(size_t i = 0; i < nb_child; i++)
  {
    tab[i] =  game->scoreAI[i];
  }
  bubbleSort(tab, nb_child, &game->AI);
  int index = nb_child-1;
  int nb_choosen = 0;

  for(size_t i = 0; i < nb_child; i++)
  {
    if(nb_choosen == nb_child/2)
      break;
    for(size_t j = 0; j < nb_child; j++)
    {
      if(game->scoreAI[j] == tab[index])
      {
        save_Network(&game->AI[i], nb_choosen);
        nb_choosen++;
        index--;
        break;
      }
    }
  }
}

void generate_generation(int nb_child, Game *game)
{
  int file = -1;
  for(size_t i = 0; i < nb_child; i++)
  {
    if(i/2 != file)
    {
      file = i/2;
      load_Newtwork(&game->AI[i], file);
    }
    else
    {
      load_Newtwork(&game->AI[i], file);
      adjust_Network(&game->AI[i]);
    }
  }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swap2(struct Network **xp, struct Network **yp)
{
  struct Network *temp = *xp;
  *xp = *yp;
  *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n, struct Network **net)
{
  int i, j;
  for (i = 0; i < n-1; i++)
    // Last i elements are already in place   
    for (j = 0; j < n-i-1; j++)
      if (arr[j] > arr[j+1])
      {
        swap(&arr[j], &arr[j+1]);
      }
}
