#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

#include "game_init.h"

void change_game_status(Game *game, int status);
void restart(Game *game, int nb_child);
void respawn(Game *game);
void levelup(Game *game);

#endif
