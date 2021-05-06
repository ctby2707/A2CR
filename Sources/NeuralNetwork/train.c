#include "game_init.h"
#include "Batch.h"
#include "NeuralNetwork.h"
#include "Inputs.h"
#include "pac-man.h"
#include "loop.h"

#define NB_BATCHS 10000

struct Network network;
queue_b *batchs;
int epsilon = 1;

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
    return execute_network(&network, inputs, NULL, game);
  }
  return 'E';
}

void train (Game *game)
{
  Batch batch;
  int *inputs = init_inputs(game);
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
  request_move(game, action);
  loop();

  batch.cur_state = inputs;
  batch.actions = actions;
  batch.reward = game->reward;
  inputs = init_inputs(game);
  batch.next_state = inputs;
  if (Batch_len(batchs) == NB_BATCHS)
    Batch_pop(batchs, NULL);
  batchs = Batch_push(batchs, batch);
}

int execute_game(Game *game)
{
  int X = 0;
  int Y = 0;
  pixel_to_mat(game->pac_man.x, game->pac_man.y, &X, &Y);
  int X_cur = 0;
  int Y_cur = 0;
  do
  {
    loop();
    pixel_to_mat(game->pac_man.x, game->pac_man.y, &X_cur, &Y_cur);
  }while(X == X_cur && Y == Y_cur);
  if (game->map[X_cur * 28 + Y_cur] != 0 || game->map[X_cur * 28 + Y_cur] != 4)
    game->reward ++;
  
}
