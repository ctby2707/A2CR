#ifndef GAME_INIT_H
#define GAME_INIT_H

#include <gtk/gtk.h>
#include "GTK.h"
typedef struct Ghost
{
  int x;
  int y;
  char dir;
  int *list;
  int n;
  int eat;
} Ghost;

typedef struct Pac_Man
{
  int x;
  int y;
  int X;
  int Y;
  char dir;
  char reqdir;
  char color;
  int lasttile;

} Pac_Man;

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
  int hunt;
  int chase;
  int scater;
  int open;
  int combo;
  int reward;
  Pac_Man pac_man;
  Ghost blinky;
  Ghost inky;
  Ghost clyde;
  Ghost pinky;
} Game;

Game *init_game();

#endif
