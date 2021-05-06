#include "game_init.h"
#include "Batch.h"
#include "NeuralNetwork.h"
#include "Inputs.h"
#include "pac-man.h"
#include "loop.h"
#include "GTK.h"
#include "random.h"

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
    return execute_network(&network, inputs, 1, NULL, game);
  }
  return 'E';
}

double get_loss(Game *game, int *next_state, int rewards, int index, int *state)
{
  double value = 0;
  execute_network(&network, next_state, index, &value, game);//get the value of the next state
  value = value * 0.99 +(double) rewards; //we assume that gamma is 0.99
  double q_cur;
  execute_network(&network, state, index, &q_cur, game);
  return q_cur - value;

}

void train (Game *game)
{
  int len_batch = Batch_len(batchs);
  Batch batch;
  int i = 0;
  while (i<150)
  {
  int *inputs = init_inputs(game);
  char action = pick_action(game, inputs);
  int ind_action = 0;
  if (action == 'N')
    ind_action = 0;
  if (action == 'S')
    ind_action = 1;
  if (action == 'W')
    ind_action = 2;
  if (action == 'E')
    ind_action = 3;
  request_move(game, action);
  loop();

  batch.cur_state = inputs;
  batch.actions = ind_action;
  batch.reward = game->reward;
  inputs = init_inputs(game);
  batch.next_state = inputs;
  if (Batch_len(batchs) == NB_BATCHS)
    Batch_pop(batchs, NULL);
  batchs = Batch_push(batchs, batch);
  i++;
  }
  double loss = 0;
  int max_len = Batch_len(batchs);
  for (int j=0; j < 32; j++)
  {
    Batch choosen_b;
    int random_number = random_int(max_len);
    for(int h = 0; h < random_number; h++)
    {
      batchs = Batch_pop(batchs, &choosen_b);
      batchs = Batch_push(batchs, choosen_b);
    }
    loss += get_loss(game, choosen_b.next_state, choosen_b.reward, choosen_b.actions, choosen_b.cur_state);
  }
  loss = loss/32;
  printf("loss = %lf",loss);
}

int execute_game(Game *game)
{
  int X = 0;
  int Y = 0;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int X_cur = 0;
  int Y_cur = 0;
  do
  {
    loop();
    pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_cur, &Y_cur);
  }while(X == X_cur && Y == Y_cur);
  if (game->map[X_cur * 28 + Y_cur] != 0 || game->map[X_cur * 28 + Y_cur] != 4)
    game->reward ++;

}
