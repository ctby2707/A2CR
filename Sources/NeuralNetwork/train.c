#include <math.h>
#include "game_init.h"
#include "game_events.h"
#include "Batch.h"
#include "NeuralNetwork.h"
#include "Inputs.h"
#include "pac-man.h"
#include "loop.h"
#include "GTK.h"
#include "random.h"
#include "train.h"
#include "main.h"

#define NB_BATCHS 10000

struct Network network;
queue_b *batchs;
int epsilon = 1;

int layer[] = {121, 60, 20, 4};

void deep_init()
{
  network = init(4, layer);
  randomizeNetwork(&network);
  save_Network(&network);
}

char pick_action(Game *game, int *inputs)
{
  int random =  random_int(100);
  if(random < epsilon) //exploration
  {
    int rest = random_int(4);
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
    double val;
    return execute_network(&network, inputs, 1, &val, game);
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
  return pow(value - q_cur, 2);

}
void print_matrix(int *M);

void train()
{
  Game *game = get_game();
  int len_batch = Batch_len(batchs);
  Batch batch;
  for(int i = 0; i<150; i++)
  {
    int *inputs = init_inputs();
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

    execute_game(game, action);

    batch.cur_state = inputs;
    batch.actions = ind_action;
    batch.reward = game->reward;
    inputs = init_inputs(game);
    batch.next_state = inputs;

    if (Batch_len(batchs) == NB_BATCHS)
      Batch_pop(batchs, NULL);
    batchs = Batch_push(batchs, batch);
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
  printf("loss = %lf\n",loss);
}


int execute_game(Game *game, char action)
{
  game->reward = 0;
  request_move(game, action);
  int X = 0;
  int Y = 0;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int X_cur = 0;
  int Y_cur = 0;
  do
  {
    loop();
    pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_cur, &Y_cur);
    if(X_cur < 0 || Y_cur < 0 || X_cur > 31 || Y_cur > 28)
    {
      game->pac_man.x = 307;
      game->pac_man.y = 377;
      game->reward = -1;
    }
    pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_cur, &Y_cur);
  }while(X == X_cur && Y == Y_cur);
  if (game->map[X_cur * 28 + Y_cur] != 0 && game->map[X_cur * 28 + Y_cur] != 4)
    game->reward ++;
  if(game->map[X_cur * 28 + Y_cur] == 0 || game->map[X_cur * 28 + Y_cur] == 4)
    game->reward += -50;

}




void print_matrix(int *M) //!!!debbuging function!!!
{
  //int *k=M;
  for (int i = 0; i < 11; i++)
  {
    for (int j = 0; j < 11; j++)
    {
      int val = M[i*11+j];
      if(val >=0)
        printf(" ");
      if((val >= 0 &&val < 10) || (val < 0 && val > -10))
        printf(" ");
      printf("%i, ",val);
    }
    printf("\n");
  }
  printf("\n\n\n");
}
