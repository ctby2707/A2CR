#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include <glib-object.h>
#include <gobject/gvaluecollector.h>
#include "GTK.h"
#include "game_init.h"
#include <math.h>
#include "Q.h"
#include "train.h"
Game *game;

Game *get_game()
{
  return game;
}
int main()
{
  game = init_game();
  srand(time(NULL));
  deep_init();
  train();
}
