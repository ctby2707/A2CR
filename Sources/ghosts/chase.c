#include "game_init.h"
#include "chase.h"
#include "random.h"
void chase(Game *game)
{
  randome_dir(game, &game->blinky);
  randome_dir(game, &game->clyde);
  randome_dir(game, &game->inky);
  randome_dir(game, &game->pinky);
}

void ghost_kill(Game *game, int n, int interface_on)
{
  if (n == 1)
  {
    game->blinky.x = 318;
    game->blinky.y = 311;
    game->blinky.eat = 1;
  }
  if (n == 2)
  {
    game->inky.x = 318;
    game->inky.y = 311;
    game->inky.eat = 1;
  }
  if (n == 4)
  {
    game->clyde.x = 318;
    game->clyde.y = 311;
    game->clyde.eat = 1;
  }
  if (n == 3)
  {
    game->pinky.x = 318;
    game->pinky.y = 311;
    game->pinky.eat = 1;
  }
  game->score += game->combo;
  if(game->combo == 200)
    game->reward += 20;
  if(game->combo == 400)
    game->reward += 40;
  if(game->combo == 800)
    game->reward += 80;
  if(game->combo == 1600)
    game->reward += 160;
  char str[42];
  sprintf(str, "Score : %i \n", game->score);
  if(interface_on == 1)
    set_score_label(str);
  game->combo = game->combo * 2;
}

void randome_dir(Game *game, Ghost *pl)
{
  int boo = 0;
  int X, Y;
  pixel_To_MatCoord(pl->x, pl->y, &X, &Y);
  if (pl->dir == 'N' && game->map[(X - 1)*28+Y] == 0)
    boo = 1;
  if (pl->dir == 'S' && game->map[(X + 1)*28+Y] == 0)
    boo = 1;
  if (pl->dir == 'W' && game->map[X*28+(Y- 1)] == 0)
    boo = 1;
  if (pl->dir == 'E' && game->map[(X + 1)*28+(Y + 1)] == 0)
    boo = 1;

  if (boo == 1) //change of direction
  {
    int ran = random_int(3);
    char newdir = pl->dir;
    if (pl->dir == 'N')
    {

      if (ran == 0)
        newdir = 'W';
      if (ran == 1)
        newdir = 'E';
      if (ran == 2)
        newdir = 'S';
    }
    if (pl->dir == 'S')
    {

      if (ran == 0)
        newdir = 'W';
      if (ran == 1)
        newdir = 'E';
      if (ran == 2)
        newdir = 'N';
    }
    if (pl->dir == 'W')
    {

      if (ran == 0)
        newdir = 'N';
      if (ran == 1)
        newdir = 'E';
      if (ran == 2)
        newdir = 'S';
    }
    if (pl->dir == 'E')
    {

      if (ran == 0)
        newdir = 'W';
      if (ran == 1)
        newdir = 'N';
      if (ran == 2)
        newdir = 'S';
    }
    pl->dir = newdir;
  }
}
