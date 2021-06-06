#include <gtk/gtk.h>
#include "game_init.h"
#include "main.h"
#include "Inputs.h"
#include "genann.h"
#include "loop.h"
#include "pac-man.h"
#include "train.h"

genann *networks;

void play_init()
{
  FILE *in = fopen("Network.txt", "r");
  networks = genann_read(in);
  fclose(in);
}

gboolean play()
{
  Game *game = get_game();
  if (game->status == 0)
    return TRUE;

  game->reward = 0;


  double *inputs = init_inputs();
  double val;
  double const *output = genann_run(networks, (double const *)inputs);
  printf("output[0] = %lf\n",output[0]);
  printf("output[1] = %lf\n",output[1]);
  printf("output[2] = %lf\n",output[2]);
  printf("output[3] = %lf\n\n",output[3]);
  char action = 'N';
  int index = 0;
  double max = -1000;
  for(size_t i = 0; i < 4; i++)
  {
    if(output[i] > max)
    {
      index = i;
      max = output[i];
    }
  }
  //index = rand() % 4;
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

  game->respawn = 0;
  do
  {
    loop(1);
    if(game->pac_man.x < 0 || game->pac_man.y < 0 ||
       game->pac_man.x > 626 ||  game->pac_man.y > 707)
    {
      game->respawn = 1;
      game->pac_man.x = 307;
      game->pac_man.y = 377;
      game->reward = -1;
    }
  }while(game->respawn == 0 && !(game->pac_man.x >= pix_x - 3 && game->pac_man.x <= pix_x + 3 &&
         game->pac_man.y >= pix_y - 3 && game->pac_man.y <= pix_y + 3) &&
         game->pac_man.x != 307 && game->pac_man.y != 377);
  if(game->respawn == 0)
  {
    game->pac_man.x = pix_x;
    game->pac_man.y = pix_y;
  }

  if (game->map[X * 28 + Y] != 0 && game->map[X * 28 + Y] != 4)
    game->reward ++;
  if(game->map[X * 28 + Y] == 0 || game->map[X * 28 + Y] == 4)
    game->reward = 0.005;

}
