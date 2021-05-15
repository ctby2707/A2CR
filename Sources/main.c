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
#include "play.h"

Game *game;

Game *get_game()
{
  return game;
}
int main(int argc, char **argv)
{
  if(argc != 2)
  {
    printf("Please type a second argument :\n -train: training the artificial intelligence\n -play: play with the artificial intelligence\n");
  }
  else
  {
    game = init_game();
    srand(time(NULL));
    if(strcmp(argv[1], "train") == 0)
    {
      deep_init();
      train();
    }
    else if(strcmp(argv[1], "play") == 0)
    {
      play_init();
      launchgtk();
    }
    else
    {
      printf("Your argument is a bullshit\n");
    }
  }
}
