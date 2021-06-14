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
      game->reward = -4;
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
    game->reward = -3;
    //reward if there is a ghost on the case
  int X_b, Y_b, X_i, Y_i, X_c, Y_c, X_p, Y_p;
  pixel_To_MatCoord(game->blinky.x, game->blinky.y, &X_b, &Y_b);
  pixel_To_MatCoord(game->inky.x, game->inky.y, &X_i, &Y_i);
  pixel_To_MatCoord(game->pinky.x, game->pinky.y, &X_p, &Y_p);
  pixel_To_MatCoord(game->clyde.x, game->clyde.y, &X_c, &Y_c);
  if ((X_b == X && Y_b == Y) || (X_c == X && Y_c == Y) || (X_p == X && Y_p == Y) || (X_i == X && Y_i == Y))
    game->reward = -2;
}
