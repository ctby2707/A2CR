#include "GTK.h"
#include <stdio.h>
#include "game_events.h"
#include "chase.h"

void is_pac_man_dead(Game *game, int interface_on)
{
  int boo = 0;
  int X, Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int XB;
  int YB;
  pixel_To_MatCoord(game->blinky.x, game->blinky.y, &XB, &YB);
  struct Ghost ghost;
  if (X == XB && Y == YB)
  {
    boo = 1;
    ghost = game->blinky;
  }
  else
  {
    int XI;
    int YI;
    pixel_To_MatCoord(game->inky.x, game->inky.y, &XI, &YI);
    if (X == XI && Y == YI)
    {
      boo = 2;
      ghost = game->inky;
    }
    else
    {
      int XP;
      int YP;
      pixel_To_MatCoord(game->pinky.x, game->pinky.y, &XP, &YP);
      if (X == XP && Y == YP)
      {
        boo = 3;
        ghost = game->pinky;
      }
      else
      {
        int XC;
        int YC;
        pixel_To_MatCoord(game->clyde.x, game->clyde.y, &XC, &YC);
        if (X == XC && Y == YC)
        {
          boo = 4;
          ghost = game->clyde;
        }
      }
    }
  }
  if (boo > 0)
  {
    if (game->chase == 0 || ghost.eat == 1)
    {
      game->live = game->live - 1;
      char str[42];
      sprintf(str, "Lives : %i \n", game->live);
      if(interface_on == 1)
       set_live_label(str);
      respawn(game);
    }
    else
    {
      ghost_kill(game,boo, interface_on);
    }
  }
}

void request_move(Game *game, char dir)
{
  int X, Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  int x;
  int y;
  matCoord_To_Pixel(X,Y,&x,&y);

  if ((dir == 'N' /*&& game->map[(X - 1)*28+Y] != 0 && game->map[(X - 1)*28+Y] != 4*/ && (x >= game->pac_man.x-6 && x<= game->pac_man.x+6 )) ||
      (dir == 'S' /*&& game->map[(X + 1)*28+Y] != 0 && game->map[(X + 1)*28+Y] != 4 */&& (x >= game->pac_man.x-6 && x<= game->pac_man.x+6 )) ||
      (dir == 'W' /*&& game->map[X*28+Y - 1] != 0 && game->map[X*28+Y - 1] != 4 */&& (y >= game->pac_man.y-6 && y<= game->pac_man.y+6 )) ||
      (dir == 'E' /*&& game->map[X*28+Y + 1] != 0 && game->map[X*28+Y + 1] != 4 */&& (y >= game->pac_man.y-6 && y<= game->pac_man.y+6 )))
  {
    game->pac_man.dir = dir;
    game->pac_man.reqdir = dir;
  }
  else
    game->pac_man.reqdir = dir;
}

void move_pac_man(Game *game, int *x, int *y, char dir, int speed)
{
  if (dir == 'N')
    *y = *y - speed;
  if (dir == 'S')
    *y = *y + speed;
  if (dir == 'W')
    *x = *x - speed;
  if(dir == 'E')
    *x = *x + speed;
}

//modify the coords of each entity
void move_entity(Game *game, int *x, int *y, char dir, int speed)
{
  int X_mat, Y_mat;
  pixel_To_MatCoord(*x, *y, &X_mat, &Y_mat);
  if (dir == 'N')
  {
    if (game->map[(X_mat - 1)*28+Y_mat] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat - 1, Y_mat, &x1, &y1);
      *y = CLAMP(*y - speed, y1 + 22, 800);
    }
    else
    {
      *y = *y - speed;
    }
  }
  if (dir == 'S')
  {
    if (game->map[(X_mat + 1)*28+Y_mat] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat + 1, Y_mat, &x1, &y1);
      *y = CLAMP(*y + speed, 0, y1 - 22);
    }
    else
    {
      *y = *y + speed;
    }
  }
  if (dir == 'W')
  {
    if (game->map[X_mat*28+Y_mat - 1] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat, Y_mat - 1, &x1, &y1);
      *x = CLAMP(*x - speed, x1 + 22, 800);
    }
    else
    {
      *x = *x - speed;
    }
  }
  if (dir == 'E')
  {
    if (game->map[X_mat*28+Y_mat + 1] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat, Y_mat + 1, &x1, &y1);
      *x = CLAMP(*x + speed, 0, x1 - 22);


    }
    else
    {
      *x = *x + speed;
    }
  }

  int X;
  int Y;
  int x1;
  int y1;
  pixel_To_MatCoord(*x, *y, &X, &Y);

  if((game->map[X*28+Y]==42 || game->map[X*28+Y]==44)&& dir == 'W')
  {
    //printf("tile value = %i in coord %i %i\n",map[X][Y],X,Y);
    matCoord_To_Pixel(X,27,&x1,&y1);
    *x = x1;
    *y = y1;
  }
  else
  {
    if((game->map[X*28+Y]==43 || game->map[X*28+Y]==45)&& dir == 'E')
    {
      //printf("tile value = %i in coord %i %i\n",map[X][Y],X,Y);
      matCoord_To_Pixel(X,0,&x1,&y1);
      *x = x1;
      *y = y1;
    }
  }
}
