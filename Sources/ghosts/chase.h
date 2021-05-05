#ifndef CHASE_H
#define CHASE_H

#include "game_init.h"

void chase(Game *game);
void ghost_kill(Game *game, int n);
void randome_dir(Game *game,Ghost *pl);

#endif
