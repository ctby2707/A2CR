#include "game_init.h"
#include "Batch.h"
#include "NeuralNetwork.h"
#include "Inputs.h"
#include "pac-man.h"
#include "loop.h"

struct Network network;
queue_b *batchs;
int epsilon = 0;

int layer[] = {121, 60, 20, 4};

void deep_init()
{
  network = init(4, layer);
}

char pick_action(Game *game, int *inputs)
{
  int random = rand() % 100;
  if(random < epsilon) //exploration
  {
    int rest = rand() % 4;
    char res = 'N';
      if(rest == 0)
        res = 'N';
      if(rest == 1)
        res = 'S';
      if(rest == 2)
        res = 'W';
      if(rest == 3)
        res = 'E';
    return res;
  }
  else
  {
    return execute_network(&network, inputs, NULL);
  }
  return 'E';
}

void train (Game *game)
{
  Batch batch;
  int *inputs = init_inputs(game);
  batch.cur_state = inputs;
  char action = pick_action(game, inputs);
  int *actions = calloc(4,sizeof(int));
  if (action == 'N')
    actions[0] = 1;
  if (action == 'S')
    actions[1] = 1;
  if (action == 'W')
    actions[2] = 1;
  if (action == 'E')
    actions[3] = 1;
  batch.actions = actions;
  request_move(game, action);
  loop();
  batch.reward = game->reward;
  inputs = init_inputs(game);
  batch.next_state = inputs;
  batchs = Batch_push(batchs, batch);
}
