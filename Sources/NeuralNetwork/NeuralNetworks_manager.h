#ifndef NEURALNETWORKS_MANAGER_H
#define NEURALNETWORKS_MANAGER_H

void generate_random_generation(int nb_child, Game *game, int type);
void new_generation(int nb_child, Game *game);
void save_generation(int nb_child, Game *game);
void generate_generation(int nb_child, Game *game);
void swap(int *xp, int *yp);
void bubbleSort(int arr[], int n, struct Network **net);

#endif
