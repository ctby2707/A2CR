#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "pac-man.h"
#include "GTK.h"
#include "ghost.h"

const int pac_man_speed = 6;
const int ghost_speed = 5;

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

/*
int pixel_art_pac_man[7][6]={
  {1,1,0,0,0,1},
  {1,0,0,0,0,0},
  {0,0,0,0,0,1},
  {0,0,0,0,1,1},
  {0,0,0,0,0,1},
  {1,0,0,0,0,0},
  {1,1,0,0,0,1}};
*/

Game game =
{
  .map = (int*)map,
  .score = 0,
  .pac_man =
          {
            .x = 307,
            .y = 377,
            .dir = 'N',
          },
  .blinky =
          {
            .x = 318, //13
            .y = 311, //14
            .dir = 'N',
          },
  .inky =
          {
            .x = 318, //13
            .y = 311, //14
            .dir = 'N',
          },
  .clyde =
          {
            .x = 318, //14
            .y = 311, //13
            .dir = 'N',
          },
  .pinky =
          {
            .x = 318, //13
            .y = 311, //14
            .dir = 'N',
          },
};

//-----------------------FUNCTIONS---------------------------------------------
void* get_game()
{
  return &game;
}

void request_move(char dir)
{
  int X,Y;
  pixel_To_MatCoord(game.pac_man.x,game.pac_man.y,&X,&Y);
  if((dir == 'N' && map[X-1][Y] != 0) ||
     (dir == 'S' && map[X+1][Y] != 0) ||
     (dir == 'G' && map[X][Y-1] != 0) ||
     (dir == 'D' && map[X][Y+1] != 0))
  {
    game.pac_man.dir = dir;
  }
}

//modify the coords of each entity
void move_entity(int* x,int* y, char dir, int speed)
{
  int X_mat,Y_mat;
  pixel_To_MatCoord(*x,*y,&X_mat,&Y_mat);
  if(dir == 'N')
  {
    if(map[X_mat-1][Y_mat] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X_mat-1,Y_mat,&x1,&y1);
      *y = CLAMP(*y - speed, y1 + 22, 800);
    }
    else
    {
      *y = *y - speed;
    }
  }
  if(dir == 'S')
  {
    if(map[X_mat+1][Y_mat] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X_mat+1,Y_mat,&x1,&y1);
      *y = CLAMP(*y + speed, 0, y1 - 22);
    }
    else
    {
      *y = *y + speed;
    }
  }
  if(dir == 'G')
  {
    if(map[X_mat][Y_mat-1] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X_mat,Y_mat-1,&x1,&y1);
      *x = CLAMP(*x - speed, x1 + 22, 800);
    }
    else
    {
      *x = *x - speed;
    }
  }
  if(dir == 'D')
  {
    if(map[X_mat][Y_mat+1] == 0)
    {
      int x1,y1;
      matCoord_To_Pixel(X_mat,Y_mat+1,&x1,&y1);
      *x = CLAMP(*x + speed,0,x1 - 22);
    }
    else
    {
      *x = *x + speed;
    }
  }
}

// execute the pathfinding function for each ghost with parameters
void define_direction(Player *pl, char type)
{
  int X_mat, Y_mat;
  pixel_To_MatCoord(pl->x,pl->y,&X_mat,&Y_mat);
  int X_pm, Y_pm;
  pixel_To_MatCoord(game.pac_man.x,game.pac_man.y,&X_pm,&Y_pm);

  if(pl->dir == 'N')
  {
    if(type == 'b')
    {
      pl->dir = blinky(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat+28);
    }
    else if(type == 'p')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat+28);

      if(game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat+28);

      if(game.pac_man.dir == 'D')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat+28);

      if(game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat+28);
    }
    else if(type == 'i')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat+28);

      if(game.pac_man.dir == 'N')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat+28);

      if(game.pac_man.dir == 'D')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat+28);

      if(game.pac_man.dir == 'G')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat+28);
    }
    if(type == 'c')
    {
      pl->dir = clyde(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat+28);
    }
  }
  else if(pl->dir == 'S')
  {
  if(type == 'b')
    {
      pl->dir = blinky(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat-28);
    }
    else if(type == 'p')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat-28);

      if(game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat-28);

      if(game.pac_man.dir == 'D')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat-28);

      if(game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat-28);
    }
    else if(type == 'i')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat-28);

      if(game.pac_man.dir == 'N')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat-28);

      if(game.pac_man.dir == 'D')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat-28);

      if(game.pac_man.dir == 'G')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat-28);
    }
    if(type == 'c')
    {
      pl->dir = clyde(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat-28);
    }

  }
  else if(pl->dir == 'G')
  {
  if(type == 'b')
    {
      pl->dir = blinky(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat+1);
    }
    else if(type == 'p')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat+1);

      if(game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat+1);

      if(game.pac_man.dir == 'D')

        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat+1);

      if(game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat+1);
    }
    else if(type == 'i')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat+1);

      if(game.pac_man.dir == 'N')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat+1);

      if(game.pac_man.dir == 'D')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat+1);

      if(game.pac_man.dir == 'G')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat+1);
    }
    if(type == 'c')
    {
      pl->dir = clyde(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat+1);
    }
  }
  else if(pl->dir == 'D') {
  if(type == 'b')
    {
      pl->dir = blinky(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat-1);
    }
    else if(type == 'p')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat-1);

      if(game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat-1);

      if(game.pac_man.dir == 'D')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat-1);

      if(game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat-1);
    }
    else if(type == 'i')
    {
      if(game.pac_man.dir == 'S')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+28,
                 map, X_mat*28+Y_mat-1);

      if(game.pac_man.dir == 'N')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-28,
                 map, X_mat*28+Y_mat-1);

      if(game.pac_man.dir == 'D')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm+1,
                 map, X_mat*28+Y_mat-1);

      if(game.pac_man.dir == 'G')
        pl->dir = inky(X_mat*28+Y_mat,X_pm*28+Y_pm,X_pm*28+Y_pm-1,
                 map, X_mat*28+Y_mat-1);
    }
    if(type == 'c')
    {
      pl->dir = clyde(X_mat*28+Y_mat,X_pm*28+Y_pm,map,X_mat*28+Y_mat-1);
    }
  }
}

gboolean loop()
{
  move_entity(&game.pac_man.x,&game.pac_man.y,game.pac_man.dir,pac_man_speed);//pac-man 
//---------------------------------GIVE INFOS----------------------------------
  int X,Y;
  pixel_To_MatCoord(game.pac_man.x, game.pac_man.y, &X, &Y);
  /*printf("\n---------------------NEW LOOP------------------------------\n");
  int X_mat_blinky;
  int Y_mat_blinky;
  pixel_To_MatCoord(game.blinky.x, game.blinky.y, &X_mat_blinky, &Y_mat_blinky);

  //print current coords
  printf("blinky coord:\n  x :%i(%i);\n  y:%i(%i);\npac man coord\n  x:%i(%i);\n  y:%i(%i);\n",
        X_mat_blinky,game.blinky.x, Y_mat_blinky, game.blinky.y,
        X,game.pac_man.x,Y,game.pac_man.y);
  printf("previous_dir: %c\n",game.blinky.dir);*/
//----------------------------BLINKY DIRECTION---------------------------------
  //define_direction(&game.blinky, 'b');
  //move_entity(&game.blinky.x, &game.blinky.y, game.blinky.dir, ghost_speed);
//---------------------------CLYDE DIRECTION-----------------------------------
  //define_direction(&game.clyde, 'c');
  //move_entity(&game.clyde.x, &game.clyde.y, game.clyde.dir, ghost_speed);
//---------------------------INKY DIRECTION------------------------------------
  move_entity(&game.inky.x, &game.inky.y, game.inky.dir, ghost_speed);
  define_direction(&game.inky, 'i');/*
//---------------------------PINKY DIRECTION-----------------------------------
  move_entity(&game.pinky.x, &game.pinky.y, game.pinky.dir, ghost_speed);
  define_direction(&game.inky, 'p');*/
//-----------------------------END-------------------------------------------
  draw(0,0,637,760);
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
  //draw(game.pac_man.x - pac_man_speed, game.pac_man.y - pac_man_speed, 22 +
  //    pac_man_speed*2, 22 +pac_man_speed*2);
//------------------------
  return TRUE;
}
