#ifndef TRAIN_H
#define TRAIN_H
#include "Batch.h"

void deep_init();
void train();
int execute_game(Game *game, int action);
void print_matrix(double *M);

#endif
