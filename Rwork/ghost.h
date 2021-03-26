#ifndef GHOST_H
#define GHOST_H

int blinky (int me, int pacman, int map[][28], int prev);
int pinky (int me, int pacman, int dir_pacman, int map[][28], int prev);
int inky (int me, int blinky, int dir_pacman, int map[][28], int prev);
int clyde (int me, int pacman, int map[][28], int prev);

#endif
