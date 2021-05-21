#ifndef TRAIN_H
#define TRAIN_H
#include "Batch.h"

void deep_init();
double derivate_loss(Batch batch);
double get_loss(Batch batch);
void train();
int execute_game(Game *game, int action);

#endif
