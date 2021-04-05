#ifndef GHOST_H
#define GHOST_H

char blinky(int me, int pacman, int map[][28], int prev);
char pinky(int me, int pacman, int dir_pacman, int map[][28], int prev);
char inky(int me, int blinky, int dir_pacman, int map[][28], int prev);
char clyde(int me, int pacman, int map[][28], int prev);

#endif
