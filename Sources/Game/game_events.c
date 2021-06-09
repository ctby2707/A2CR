#include "game_init.h"
#include "game_events.h"

void restart(Game *game, int interface_on)
{
  //----------------------------------------
  //game.status = 0;
  printf("final score = %i",game->score);
  game->chase = 0;
  game->hunt = 0;
  game->scater = 168;
  game->pacgum = 0;
  respawn(game);
  game->live = 3;
  char tmp[42];
  sprintf(tmp, "Lives : %i \n", game->live);
  if(interface_on == 1)
    set_live_label(tmp);
  game->level = 1;
  char lev[42];
  sprintf(lev, "Level : %i \n", game->level);
  if(interface_on == 1)
    set_level_label(lev);
  game->score = 0;
  char str[42];
  sprintf(str, "Score : %i \n", game->score);
  if(interface_on == 1)
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
  if(interface_on == 1)
    draw(0, 0, 637, 760);
  //on_Pause_clicked();
}


void respawn(Game *game)
{
  game->respawn = 1;

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
 //printf("nb pacgum = %d\n",game->pacgum);
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
