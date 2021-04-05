#ifndef PACMAN_H
#define PACMAN_H

#include <gtk/gtk.h>
#include "GTK.h"
typedef struct Player
{
  int x;
  int y;
  char dir;
}Player;

typedef struct Pac_Man
{
  int x;
  int y;
  char dir;
  char reqdir;
  char color;
  
}Pac_Man;

typedef struct Game
{
  int status;
  int *map;
  int *pac_man_open;
  int *pac_man_closed;
  int *ghost_pixel_art;
  int score;
  int live;
  int level;
  int pacgum;
  int chase;
  int open;
  int combo;
  Pac_Man pac_man;
  Player blinky;
  Player inky;
  Player clyde;
  Player pinky;
}Game;

void* get_game();
void change_game_status(int status);
void randome_dir(Player *pl);
void request_move(char dire);
gboolean loop();
#endif
