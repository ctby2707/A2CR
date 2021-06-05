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
#define LEARNING_RATE 0.00000003

genann *network;
queue_b *batchs;
double epsilon = 70;

//initialize the network
void deep_init()
{
  /*FILE *in = fopen("Network.txt", "r");
  network = genann_read(in);
  fclose(in);*/
  network = genann_init(121, 2, 30, 4);
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
  }
  return res;
}

void print_batch(Batch *batch);

//Update the queue by adding new batchs
void update_batch(Game *game)
{
  for(size_t i = 0; i < 100; i++)
  {
    Batch batch;

    double *inputs = init_inputs();
    int action = pick_action(game, inputs);

    execute_game(game, action);
    batch.cur_state = inputs;
    batch.actions = action;
    const double *output =  genann_run(network, (double const *)inputs);
    batch.q = output[action];

    inputs = init_inputs(game);

    output =  genann_run(network, (double const *)inputs);


    double out = -1000;
    for(size_t i = 0; i < 4; i++)
    {
      if(output[i] > out)
      {
        out = output[i];
      }
    }
    if (game->reward == -1 || game->reward == -2 || game->reward == -3)
      batch.q_target = game->reward;
    else
      batch.q_target = game->reward + 0.99*out;
    //stop the number of batch to 10000
    if (Batch_len(batchs) == NB_BATCHS)
    {
      struct Batch tmp;
      batchs = Batch_pop(batchs, &tmp);
      free(tmp.cur_state);
    }
    batchs = Batch_push(batchs, batch);
    free(inputs);
  }
}

void train()
{
  Game *game = get_game();
  int len_batch = Batch_len(batchs);
  Batch batch;
  double average = 0;
  for(int episode = 0; episode < 100000000; episode++)
  {

    update_batch(game);
    //get a random batch to do the training
    Batch choosen_b;
    for(size_t selection = 0; selection < 32; selection++)
    {
      int random_number = 1 + random_int(Batch_len(batchs));
      for(int h = 0; h < random_number; h++)
      {
        batchs = Batch_pop(batchs, &choosen_b);
        batchs = Batch_push(batchs, choosen_b);
      }
      //print_batch(&choosen_b);
      genann_train(network, (double const *) choosen_b.cur_state, choosen_b.q_target, choosen_b.actions, LEARNING_RATE);
    }
    double temp = choosen_b.q - choosen_b.q_target;
    if(temp < 0)
      average -= temp;
    else
      average += temp;

    if (episode != 0 && episode % 1000 == 0)
    {
      if(average / 1000 < 0.5 && average / 1000 > -0.5)
      {
        CLAMP(epsilon ,20, epsilon -= 1);
        printf("epsilon = %f\n", epsilon);
      }
      printf("perte = %lf\n", average/1000);
      FILE *out = fopen("Network.txt", "w");
      genann_write(network, out);
      fclose(out);
      average = 0;

    }
  }
  genann_free(network);
  Batch_empty(&batchs);
}

int execute_game(Game *game, int index)
{
  game->reward = 0;
  char action = 'N';
  int X, Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int pix_x, pix_y;

  if(index == 0)
  {
    action = 'N';
    middle_of_case(X - 1, Y, &pix_x, &pix_y);
  }
  if(index == 1)
  {
    action = 'S';
    middle_of_case(X + 1, Y, &pix_x, &pix_y);
  }
  if(index == 2)
  {
    action = 'W';
    middle_of_case(X, Y - 1, &pix_x, &pix_y);
  }
  if(index == 3)
  {
    action = 'E';
    middle_of_case(X, Y + 1, &pix_x, &pix_y);
  }

  game->pac_man.dir = action; //define the new dir of pac-man

  int respawn = 0;
  do
  {
    loop(0);
    if(game->pac_man.x < 0 || game->pac_man.y < 0 || game->pac_man.x > 626 ||  game->pac_man.y > 707)
    {
      respawn = 1;
      game->pac_man.x = 307;
      game->pac_man.y = 377;
      game->reward = -1;
    }
  }while(respawn == 0 && !(game->pac_man.x >= pix_x - 3 && game->pac_man.x <= pix_x + 3 &&
        game->pac_man.y >= pix_y - 3 && game->pac_man.y <= pix_y + 3) &&
      game->pac_man.x != 307 && game->pac_man.y != 377);
  if(respawn == 0)
  {
    game->pac_man.x = pix_x;
    game->pac_man.y = pix_y;
  }

  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  if (X >= 0 && X < 31 && Y >= 0 && Y < 31)
  {
    if (game->map[X * 28 + Y] != 0 && game->map[X * 28 + Y] != 4)
      game->reward ++;
    if(game->map[X * 28 + Y] == 0 || game->map[X * 28 + Y] == 4)
      game->reward = -2;
  }
  //reward if there is a ghost on the case
  int X_b, Y_b, X_i, Y_i, X_c, Y_c, X_p, Y_p;
  pixel_To_MatCoord(game->blinky.x, game->blinky.y, &X_b, &Y_b);
  pixel_To_MatCoord(game->inky.x, game->inky.y, &X_i, &Y_i);
  pixel_To_MatCoord(game->pinky.x, game->pinky.y, &X_p, &Y_p);
  pixel_To_MatCoord(game->clyde.x, game->clyde.y, &X_c, &Y_c);
  if ((X_b == X && Y_b == Y) || (X_c == X && Y_c == Y) || (X_p == X && Y_p == Y) || (X_i == X && Y_i == Y))
    game->reward = -1;
}

void print_matrix(double *M)
{
  //double *k=M;
  for (int i =0;i<121;i++)
  {
    if(i == 60)
    {
      printf("PPPPPPPP, ");
    }
    else
    {
      printf("%f, ",*(M+i));
    }
    if ((int)M[i]%10 == (int)M[i])
      printf(" ");
    if ((i+1)%11==0 && i>0)
      printf("\n");
  }
}

void print_batch(Batch *batch)
{
  printf("Action = %d\n",batch->actions);
  printf("Qtarget = %f\n", batch->q_target);
  print_matrix(batch->cur_state);
  printf("\n\n");
}
