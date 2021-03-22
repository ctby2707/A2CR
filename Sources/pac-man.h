#ifndef PACMAN_H
#define PACMAN_H

#include <gtk/gtk.h>
typedef struct Player
{
  int x;
  int y;
}Player;

typedef struct Game
{
  int *map;
  int score;
  Player pac_man;
  Player ghost_red;
  Player ghost_blue;
  Player ghost_orange;
  Player ghost_rose;
}Game;

void* get_game();
void request_move(char dire);
gboolean loop();
#endif
