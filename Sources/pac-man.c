#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "pac-man.h"
#include "GTK.h"

const int pac_man_speed = 6;

//-------------------------INITIALISATION-------------------------------------
int map[31][28] ={
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
  {0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0}, //1
  {0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //2
  {0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //3
  {0,2,2,2,2,3,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,3,2,2,2,2,0}, //4
  {0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //5
  {0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //6
  {0,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,0}, //7
  {0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //8
  {0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //9
  {5,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,5}, //10
  {0,2,0,0,0,0,2,0,0,1,0,0,0,4,4,0,0,0,1,0,0,2,0,0,0,0,2,0}, //11
  {0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //12
  {0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //13
  {0,2,2,2,2,2,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,2,2,2,2,2,0}, //14
  {0,1,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,1,0}, //15
  {0,1,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,1,0}, //16
  {0,1,1,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,1,1,0}, //17
  {0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,0,0,0}, //18
  {0,0,0,1,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,1,0,0,0}, //19
  {5,1,1,1,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,1,1,1,5}, //20
  {0,1,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,1,0}, //21
  {0,1,0,0,0,0,2,0,0,2,2,2,2,1,1,2,2,2,2,0,0,2,0,0,0,0,1,0}, //22
  {0,2,2,2,2,2,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,2,2,2,2,2,0}, //23
  {0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //24
  {0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //25
  {0,2,0,0,2,3,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,3,2,0,0,2,0}, //26
  {0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //27
  {0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //28
  {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0}, //29
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; //30


int pixel_art_pac_man[7][6]={
  {1,1,0,0,0,1},
  {1,0,0,0,0,0},
  {0,0,0,0,0,1},
  {0,0,0,0,1,1},
  {0,0,0,0,0,1},
  {1,0,0,0,0,0},
  {1,1,0,0,0,1}};


Game game =
{
  .map = (int*)map,
  .score = 0,
  .pac_man =
          {
            .x = 32,
            .y = 47,
          },
    .ghost_red =
          {
            .x = 0,
            .y = 0,
          },
  .ghost_blue =
          {
            .x = 0,
            .y = 0,
          },
  .ghost_orange =
          {
            .x = 0,
            .y = 0,
          },
  .ghost_rose =
          {
            .x = 0,
            .y = 0,
          },
};

//-----------------------FUNCTIONS---------------------------------------------
void* get_game()
{
  return &game;
}
char dir = 'D';
void request_move(char dire)
{
  int X,Y;
  pixel_To_MatCoord(game.pac_man.x,game.pac_man.y,&X,&Y);
  if((dire == 'N' && map[X-1][Y] != 0) ||
     (dire == 'S' && map[X+1][Y] != 0) ||
     (dire == 'G' && map[X][Y-1] != 0) ||
     (dire == 'D' && map[X][Y+1] != 0))
  {
    dir = dire;
  }
}
gboolean loop()
{
//------------Pac-man moves with collisions
  int X,Y;
  pixel_To_MatCoord(game.pac_man.x,game.pac_man.y,&X,&Y);
  if(dir == 'N')
  {
    if(map[X-1][Y] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X-1,Y,&x1,&y1);
      game.pac_man.y = CLAMP(game.pac_man.y - pac_man_speed, y1 + 22, 800);
    }
    else
    {
      game.pac_man.y =  game.pac_man.y - pac_man_speed;
    }
  }
  if(dir == 'S')
  {
    if(map[X+1][Y] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X+1,Y,&x1,&y1);
      game.pac_man.y =  CLAMP(game.pac_man.y + pac_man_speed, 0, y1 - 22);
    }
    else
    {
      game.pac_man.y =  game.pac_man.y + pac_man_speed;
    }
  }
  if(dir == 'G')
  {
    if(map[X][Y-1] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X,Y-1,&x1,&y1);
      game.pac_man.x = CLAMP(game.pac_man.x - pac_man_speed, x1 + 22, 800);
    }
    else
    {
      game.pac_man.x = game.pac_man.x - pac_man_speed;
    }
  }
  if(dir == 'D')
  {
    if(map[X][Y+1] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X,Y+1,&x1,&y1);
      game.pac_man.x = CLAMP(game.pac_man.x + pac_man_speed,0,x1 - 22);
    }
    else
    {
      game.pac_man.x = game.pac_man.x + pac_man_speed;
    }
  }
//---------------SCORE
  if(map[X][Y] == 2)
  {
    map[X][Y] = 1;
    game.score = game.score + 10;
  }
  if(map[X][Y] == 3)
  {
    map[X][Y] = 1;
  }
  draw(game.pac_man.x - pac_man_speed, game.pac_man.y - pac_man_speed, 22 +
      pac_man_speed*2, 22 +pac_man_speed*2);
//------------------------
  return TRUE;
}
