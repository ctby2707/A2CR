#include <gtk/gtk.h>
#include "game_init.h"
#include "main.h"
#include "Inputs.h"
#include "NeuralNetwork.h"
#include "loop.h"
#include "pac-man.h"

struct Network network;
int layers[] = {121, 60, 20, 4};

void play_init()
{
  network = init(4, layers);
  load_Network(&network);
}

gboolean play()
{
  Game *game = get_game();
  if (game->status == 0)
    return TRUE;

  game->reward = 0;


  int *inputs = init_inputs();
  double val;
  char action = execute_network(&network, inputs, 1, &val, game);
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
