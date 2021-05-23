#include <math.h>
#include "game_init.h"
#include "game_events.h"
#include "Batch.h"
#include "Inputs.h"
#include "pac-man.h"
#include "loop.h"
#include "GTK.h"
#include "random.h"
#include "train.h"
#include "main.h"
#include "genann.h"

#define NB_BATCHS 10000

genann *network;
queue_b *batchs;
double epsilon = 100;

//initialize the network
void deep_init()
{
  network = genann_init(121, 2, 10, 4);
}


//Choose a random action or execute the network
//It return the direction choosen (N, S, W, E)
int pick_action(Game *game, double *inputs)
{
  int random =  random_int(100);
  int res = 0;
  if(random < epsilon) //exploration
  {
    res = random_int(4);
  }
  else
  {
    const double *output =  genann_run(network, (double const *)inputs);
    double out = -1000;
    for(size_t i = 0; i < 4; i++)
    {
      if(output[i] >out)
      {
        res = i;
        out = output[i];
      }
    }
  }/*
      if(res == 0)
      return 'N';
      if(res == 1)
      return 'S';
      if(res == 3)
      return 'E';
      return 'W';*/
  return res;
}

void print_batch(Batch *batch);
//Update the queue by adding new batchs
void update_batch(Game *game)
{
  for(size_t i = 0; i < 100; i++)
  {
    Batch batch;
    //char cardinals[] = {'N','S','W','E'};
    double *inputs = init_inputs();
    int action = pick_action(game, inputs);
    //int ind_action = 0;
    /*for (size_t j = 0; j < 4; j++)
      {
    //get the index of the choosen action
    if (action = cardinals[j])
    ind_action = j;
    }*/

    execute_game(game, action);
    batch.cur_state = inputs;

    batch.actions = action;
    batch.reward = game->reward;
    inputs = init_inputs(game);
    batch.next_state = inputs;
    batch.desired_output = (double *)genann_run(network, (double const *)batch.cur_state);
    batch.q = batch.desired_output[batch.actions];
    batch.desired_output[batch.actions] = batch.reward;

    //stop the number of batch to 10000
    if (Batch_len(batchs) == NB_BATCHS)
    {
      struct Batch tmp;
      Batch_pop(batchs, &tmp);
    }
    batchs = Batch_push(batchs, batch);
  }
}

void train()
{
  Game *game = get_game();
  int len_batch = Batch_len(batchs);
  Batch batch;
  double loss = 0;
  int average_reward = 0;
  double average_loss = 0;
  for(int episode = 0; episode < 100000; episode++)
  {

    update_batch(game);

    //get a random batch to do the training
    Batch choosen_b;
    double average = 0;
    int random_number = random_int(Batch_len(batchs));
    for(size_t selection = 0; selection < 32; selection++)
    {
      for(int h = 0; h < random_number; h++)
      {
        batchs = Batch_pop(batchs, &choosen_b);
        batchs = Batch_push(batchs, choosen_b);
      }
      genann_train(network, (double const *) choosen_b.cur_state, choosen_b.reward, choosen_b.actions, 0.3);
    }
    average += choosen_b.q - choosen_b.reward;
    if (episode%100 == 0)
      printf("perte = %lf\n", average/100);
  }
  FILE *out = fopen("Network.txt", "w");
  genann_write(network, out);

  fclose(out);
  genann_free(network);
}

int execute_game(Game *game, int action)
{
  char dir = 'N';
  if(action == 0)
    dir = 'N';
  if(action == 1)
    dir = 'S';
  if(action == 2)
    dir = 'W';
  if(action == 3)
    dir = 'E';
  game->reward = 0;
  //request_move(game, dir);
  game->pac_man.dir = dir;
  int X = 0;
  int Y = 0;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int X_cur = 0;
  int Y_cur = 0;
  do
  {
    loop(0);
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
   game->reward += 0.005;

}

void print_matrix(double *M)
{
  //double *k=M;
  for (int i =0;i<121;i++)
  {
    printf("%f, ",*(M+i));
    if ((int)M[i]%10 == (int)M[i])
    printf(" ");
    if ((i+1)%11==0 && i>0)
      printf("\n");
  }
  printf("\n\n\n");
}

void print_batch(Batch *batch)
{
  print_matrix(batch->cur_state);
  printf("Action = %d\n",batch->actions);
  printf("Reward = %lf\n",batch->reward);
}
