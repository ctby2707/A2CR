#ifndef PACMAN_H
#define PACMAN_H

#include <gtk/gtk.h>
typedef struct Player
{
  int x;
  int y;
  char dir;
}Player;

typedef struct Game
{
  int *map;
  int score;
  Player pac_man;
  Player blinky;
  Player inky;
  Player clyde;
  Player pinky;
}Game;

void* get_game();
void request_move(char dire);
gboolean loop();
#endif
