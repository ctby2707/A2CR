#include <stdlib.h>
#include <math.h>
#include "game_init.h"
#include "GTK.h"
#include "main.h"

#define REWARD_GHOST -5
#define REWARD_GHOST_CHASE 10
#define REWARD_PATH 1
#define REWARD_PACGUM 2
#define REWARD_WALL -10
#define REWARD_SUPERPACGUM 3
#define REWARD_FRUIT 100

double *init_inputs()
{
  Game *game = get_game();
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

  int X_pc = 0;
  int Y_pc = 0;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_pc, &Y_pc);
  int pos_pacman = X_pc * 28 + Y_pc;
  int map_point = pos_pacman -5 - (5 * 28);

  double *lidar = calloc(11*11,sizeof(int));
  for (size_t i = 0; i < 11; i++)
  {
    for (size_t j = 0; j < 11; j++)
    {
      if(map_point < 0 || map_point > 868)
      {
        lidar[i*11+j] = -1;
      }
      else
      {
        if (game->map[map_point] == 0 || game->map[map_point] == 4)
          lidar[i*11+j] = REWARD_WALL;
        if (game->map[map_point] == 1 || game->map[map_point] == 42 ||
            game->map[map_point] == 43 || game->map[map_point] == 44 ||
            game->map[map_point] == 45 || game->map[map_point] == 7 ||
            game->map[map_point] == 6)
          lidar[i*11+j] += REWARD_PATH;
        if (game->map[map_point] == 2)
          lidar[i*11+j] += REWARD_PACGUM;
        if (game->map[map_point] == 3)
          lidar[i*11+j] += REWARD_SUPERPACGUM;
        if (game->chase > 0)
        {
          int reward = REWARD_GHOST_CHASE;

          if (x_blinky * 28 + y_blinky == map_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
          if (x_inky * 28 + y_inky == map_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
          if (x_pinky * 28 + y_pinky == map_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
          if (x_clyde * 28 + y_clyde == map_point)
          {
            lidar[i*11+j] += reward;
            reward *= 2;
          }
        }
        else
        {
          if (x_blinky * 28 + y_blinky == map_point)
            lidar[i*11+j] += REWARD_GHOST;
          if (x_inky * 28 + y_inky == map_point)
            lidar[i*11+j] += REWARD_GHOST;
          if (x_pinky * 28 + y_pinky == map_point)
            lidar[i*11+j] += REWARD_GHOST;
          if (x_clyde * 28 + y_clyde == map_point)
            lidar[i*11+j] += REWARD_GHOST;
        }
        /*if (game->fruit == begin + lidar_point)
          lidar[i*11+j] += REWARD_FRUIT;
         */
      }
      map_point++;
    }
    map_point += 28 - 11;
  }
  return lidar;
}

