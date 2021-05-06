#include <stdlib.h>
#include <math.h>
#include "game_init.h"
#include "GTK.h"

#define REWARD_GHOST -9
#define REWARD_GHOST_CHASE 200
#define REWARD_PATH 1
#define REWARD_PACGUM 11
#define REWARD_WALL -50
#define REWARD_SUPERPACGUM 16
#define REWARD_FRUIT 100

int *init_inputs(Game *game)
{
  int x_blinky = 0;
  int y_blinky = 0;
  pixel_To_MatCoord(game->blinky.x, game->blinky.y, &x_blinky, &y_blinky);
  int x_inky = 0;
  int y_inky = 0;
  pixel_To_MatCoord(game->inky.x, game->inky.y, &x_inky, &y_inky);
  int x_pinky = 0;
  int y_pinky = 0;
  pixel_To_MatCoord(game->pinky.x, game->pinky.y, &x_pinky, &y_pinky);
  int x_clyde = 0;
  int y_clyde = 0;
  pixel_To_MatCoord(game->clyde.x, game->clyde.y, &x_clyde, &y_clyde);

  int pos_pacman = (game->pac_man.X) * 28 + game->pac_man.Y;
  int begin = pos_pacman - (28 * 5) - 5;
  int end = pos_pacman + (28 * 5) + 5;
  int lidar_point = pos_pacman - (28 * 5) - 5;
  int *lidar = calloc(11*11,sizeof(int));
  for (size_t i = 0; i < 11; i++)
  {
    for (size_t j = 0; j < 11; j++)
    {
      int y = lidar_point % 28;
      if (lidar_point >= 0 && lidar_point <= 868
          && pos_pacman - 5 - y > 0 && pos_pacman + 5 + y < 28)//check if the point is in the map
      {
        if (game->map[lidar_point] == 0)
          lidar[i*11+j] = REWARD_WALL;
        if (game->map[lidar_point] == 1 || game->map[lidar_point] == 42 ||
            game->map[lidar_point] == 43 || game->map[lidar_point] == 44 ||
            game->map[lidar_point] == 45)
          lidar[i*11+j] += REWARD_PATH;
        if (game->map[lidar_point] == 2)
          lidar[i*11+j] += REWARD_SUPERPACGUM;
        if (game->map[lidar_point] == 3)
        if (game->chase > 0)
        {
          int reward = REWARD_GHOST_CHASE;

          if (x_blinky * 28 + y_blinky == begin + lidar_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
          if (x_inky * 28 + y_inky == begin + lidar_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
          if (x_pinky * 28 + y_pinky == begin + lidar_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
          if (x_clyde * 28 + y_clyde == begin + lidar_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
        }
        else
        {
          if (x_blinky * 28 + y_blinky == begin + lidar_point)
            lidar[i*11+j] += REWARD_GHOST;
          if (x_inky * 28 + y_inky == begin + lidar_point)
            lidar[i*11+j] += REWARD_GHOST;
          if (x_pinky * 28 + y_pinky == begin + lidar_point)
            lidar[i*11+j] += REWARD_GHOST;
          if (x_clyde * 28 + y_clyde == begin + lidar_point)
            lidar[i*11+j] += REWARD_GHOST;
        }
        /*if (game->fruit == begin + lidar_point)
          lidar[i*11+j] += REWARD_FRUIT;
         */
      }
      lidar_point++;
    }
  }
  return lidar;
}

