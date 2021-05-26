#include <gtk/gtk.h>
#include "game_init.h"
#include "main.h"
#include "Inputs.h"
#include "genann.h"
#include "loop.h"
#include "pac-man.h"

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
  if(index == 0)
    action = 'N';
  if(index == 1)
    action = 'S';
  if(index == 2)
    action = 'W';
  if(index == 3)
    action = 'E';
  request_move(game, action);
  int X = 0;
  int Y = 0;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int X_cur = 0;
  int Y_cur = 0;
  do
  {
    loop(1);
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
