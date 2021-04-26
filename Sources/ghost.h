#ifndef GHOST_H
#define GHOST_H

#include "pac-man.h"

void define_direction(Player *pl, char type, Game *game);
char NSGD(int res);
char blinky(int me, int pacman, int *map, int prev);
char pinky(int me, int pacman, int dir_pacman, int *map, int prev);
char inky(int me, int blinky, int dir_pacman, int *map, int prev);
char clyde(int me, int pacman, int *map, int prev);

#endif
