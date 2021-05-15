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
#include "backpropagation.h"

#define NB_BATCHS 10000

struct Network network;
queue_b *batchs;
double epsilon = 100;

int layer[] = {121, 60, 20, 4};


//initialize the network
void deep_init()
{
  network = init(4, layer);
  load_Network(&network);
}


//Choose a random action or execute the network
//It return the direction choosen (N, S, W, E)
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


// return the value of the derivate of the cost function
double derivate_cost(Batch batch)
{
  if((batch.q - batch.q_target) < 1 && (batch.q - batch.q_target) > -1)
    return (batch.q - batch.q_target);
  else
    if((batch.q - batch.q_target) < 0)
      return -1;
    else
      return 1;
}


// return the value of the cost function (MSE)
double cost(Batch batch)
{
  if((batch.q - batch.q_target) < 1 && (batch.q - batch.q_target) > -1)
    return 0.5*pow((batch.q - batch.q_target), 2);
  else
    return abs(batch.q - batch.q_target) - 0.5;
}


//Update the queue by adding new batchs
void update_batch(Game *game)
{
  for(size_t i = 0; i < 100; i++)
  {
    Batch batch;
    char cardinals[] = {'N','S','W','E'};
    int *inputs = init_inputs();
    char action = pick_action(game, inputs);
    int ind_action = 0;
    for (size_t j = 0; j < 4; j++)
    {
      //get the index of the choosen action
      if (action = cardinals[j])
        ind_action = j;
    }

    execute_game(game, action);
    batch.cur_state = inputs;
    execute_network(&network, batch.cur_state, ind_action, &batch.q, game);

    batch.actions = ind_action;
    batch.reward = game->reward;

    inputs = init_inputs(game);
    batch.next_state = inputs;
    execute_network(&network, batch.next_state, ind_action, &batch.q_target, game);
    batch.q_target *= 0.99;
    batch.q_target = batch.reward; //!!! Debbuging : juste give the reward

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
  for(int episode = 0; episode < 10000; episode++)
  {
    loss = 3;
    double derivate_loss = 0;

    update_batch(game);

    //get a random batch to do the training
    Batch choosen_b;
    int random_number = random_int(Batch_len(batchs));
    for(int h = 0; h < random_number; h++)
    {
      batchs = Batch_pop(batchs, &choosen_b);
      batchs = Batch_push(batchs, choosen_b);
    }

    average_loss += loss;

    do //reajust weights until the result is good
    {
      execute_network(&network, choosen_b.cur_state, choosen_b.actions, &choosen_b.q, game);
      printf("%d = %lf\n", choosen_b.reward, choosen_b.q);
      loss = cost(choosen_b);
      derivate_loss = derivate_cost(choosen_b);

      backpropagation(&network, choosen_b.cur_state, choosen_b.actions, derivate_loss);
    }while(loss > 0.5);

     printf("%d = %lf\n", choosen_b.reward, choosen_b.q);

    //diplay average reward and average loss every 5 episodes
    average_reward += choosen_b.reward;
    if(episode % 5 == 0 && episode != 0)
    {
      //printf("moyenne des récompenses : %i\n", average_reward/5);
      printf("moyenne des pertes : %lf\n", average_loss/5);
      printf("__________________________________\n");
      average_reward = 0;
      average_loss = 0;
      epsilon -= 0.0001;
      save_Network(&network);
    }
  }
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
    game->reward += -50;

}
