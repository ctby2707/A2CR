#ifndef PACMAN_H
#define PACMAN_H

#include <gtk/gtk.h>
#include "GTK.h"
typedef struct Player
{
  int x;
  int y;
  char dir;
  int *list;
  int n;
  int eat;
} Player;

typedef struct Pac_Man
{
  int x;
  int y;
  int X;
  int Y;
  char dir;
  char reqdir;
  char color;

} Pac_Man;

typedef struct Game
{
  int status;
  int *map;
  int *pac_man_open;
  int *pac_man_closed;
  int *ghost_pixel_art;
  int score;
  int prevScore;
  int live;
  int level;
  int pacgum;
  int hunt;
  int chase;
  int scater;
  int open;
  int combo;
  int isFirstGame;
  struct Network *AI;
  int generation;
  int index;
  int *scoreAI;
  Pac_Man pac_man;
  Player blinky;
  Player inky;
  Player clyde;
  Player pinky;
} Game;

void init_game();
Game *get_game();
void change_game_status(int status);
void randome_dir(Player *pl);
void request_move(char dire);
gboolean loop();
#endif
