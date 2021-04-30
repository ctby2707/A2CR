#include "game_init.h"
#include "NeuralNetworks_manager.h"
#include "game_events.h"

void restart(Game *game, int nb_child, int Q_activated)
{
  printf("Score : %i\n",game->score);
  if(Q_activated == 0)
  {
    //-------------AI part--------------------
    game->scoreAI[game->index] = game->score;
   printf("Score : %i\n",game->scoreAI[game->index]);
    printf("--------------------\n");
    game->index++;
    if(game->index == nb_child)
    {
      new_generation(nb_child,game);
      game->index = 0;
      game->generation++;
    }
    printf("--------------------\n");
    printf("Generation : %i\n",game->generation);
    printf("Child : %i\n",game->index);
  }
  //----------------------------------------
  //game.status = 0;
  game->chase = 0;
  game->hunt = 0;
  game->scater = 168;
  game->pacgum = 0;
  respawn(game);
  game->live = 3;
  char tmp[42];
  sprintf(tmp, "Lives : %i \n", game->live);
  set_live_label(tmp);
  game->level = 1;
  char lev[42];
  sprintf(lev, "Level : %i \n", game->level);
  set_level_label(lev);
  game->score = 0;
  char str[42];
  sprintf(str, "Score : %i \n", game->score);
  set_score_label(str);
  for (int x = 0; x < 31; x++)
  {
    for (int y = 0; y < 28; y++)
    {
      if (game->map[x*28+y] == 6)
      {
        game->map[x*28+y] = 2;
        //cairo_rectangle(cr,X+9,Y+9,5,5);
      }
      if (game->map[x*28+y] == 7)
      {
        game->map[x*28+y] = 3;
        //cairo_rectangle(cr,X+4,Y+4,10,10);
      }
    }
  }
  draw(0, 0, 637, 760);
  //on_Pause_clicked();
}


void respawn(Game *game)
{
  game->pac_man.color = 'y';
  game->pac_man.x = 307;
  game->pac_man.y = 377;
  game->pac_man.dir = 'N';
  game->pac_man.reqdir = 'N';

  game->blinky.x = 318;
  game->blinky.y = 311;

  game->inky.x = 318;
  game->inky.y = 311;

  game->clyde.x = 318;
  game->clyde.y = 311;

  game->pinky.x = 318;
  game->pinky.y = 311;

  //sleep(2);
}

void levelup(Game *game)
{
  game->chase = 0;
  game->hunt = 0;
  game->scater = 168;
  game->pacgum = 0;
  game->level = game->level + 1;
  char str[42];
  sprintf(str, "level : %i \n", game->level);
  set_level_label(str);
  for (int x = 0; x < 31; x++)
  {
    for (int y = 0; y < 28; y++)
    {
      if (game->map[x*28+y] == 6)
      {
        game->map[x*28+y] = 2;
        //cairo_rectangle(cr,X+9,Y+9,5,5);
      }
      if (game->map[x*28+y] == 7)
      {
        game->map[x*28+y] = 3;
        //cairo_rectangle(cr,X+4,Y+4,10,10);
      }
    }
  }
  respawn(game);
  draw(0, 0, 637, 760);
}

void change_game_status(Game *game,int status)
{
  game->status = status;
}
