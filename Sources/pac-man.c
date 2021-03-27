#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "pac-man.h"
#include "GTK.h"
#include "/home/epita/A2CR/Rwork/ghost.h"

const int pac_man_speed = 6;
const int ghost_speed = 5;
int dir_blinky = -28;
int dir_inky = -1;
int dir_clyde = -1;
int dir_pinky = -1;

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
          },
  .blinky =
          {
            .x = 208, //13 in mat
            .y = 223, //13 in mat
          },
  .inky =
          {
            .x = 0,
            .y = 0,
          },
  .clyde =
          {
            .x = 318, //14 in mat
            .y = 311, //13 in mat
          },
  .pinky =
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


int random_ghost()
{
  
  int num = rand() % 4;
  printf("num = %i \n",num);
  if(num == 0)
    return -1;
  if(num == 1)
    return 1;
  if(num == 2)
    return 28;
  if(num == 3)
    return -28;
  return -1;
}

void move_ghost(int ghostnum)
{
  
  int x;
  int y;
  int X=0;
  int Y=0;
  int dir = 0;
  if(ghostnum == 1)
    {
      X = game.blinky.x;
      Y = game.blinky.y;
      dir = dir_blinky;
    }
  if(ghostnum == 2)
    {
      X = game.inky.x;
      Y = game.inky.y;
      dir = dir_inky;
    }
  if(ghostnum == 3)
    {
      X = game.clyde.x;
      Y = game.clyde.y;
      dir = dir_clyde;
    }
  if(ghostnum == 4)
    {
      X = game.pinky.x;
      Y = game.pinky.y;
      dir = dir_pinky;
    }
  pixel_To_MatCoord(X,Y,&x,&y);
  
  if(dir == -28)//N
    {
      if(map[x-1][y]==1 || map[x-1][y]==2 || map[x-1][y]==3 || map[x-1][y]==4 )
	{
	  X= CLAMP(X - ghost_speed, 0, 635);
	  printf("up \n");
	}
    }
  if(dir == 28)//S
    {
      if(map[x+1][y]==1 || map[x+1][y]==2 || map[x+1][y]==3 || map[x+1][y]==4 )
	{
	  X= CLAMP(X + ghost_speed, 0, 635);
	  printf("down \n");
	}
    }
  if(dir == 1)//E
    {
      if(map[x][y+1]==1 || map[x][y+1]==2 || map[x][y+1]==3 || map[x][y+1]==4)
	{
	  Y= CLAMP(Y + ghost_speed, 0, 760);
	  printf("right \n");
	}
    }
  if(dir == -1)//W
    {
      if(map[x][y-1]==1 || map[x][y-1]==2 || map[x][y-1]==3 || map[x][y-1]==4)
	{
	  Y= CLAMP(Y - ghost_speed, 0, 760);
	  printf("left \n");
	}
    }
  if(ghostnum == 1)
    {
      game.blinky.x=X;
      game.blinky.y=Y;
    }
  if(ghostnum == 2)
    {
      game.inky.x=X;
      game.inky.y=Y;
    }
  if(ghostnum == 3)
    {
      game.clyde.x=X;
      game.clyde.y=Y;
    }
  if(ghostnum == 4)
    {
      game.pinky.x=X;
      game.pinky.y=Y;
    }
  
}

int choose_to_move_ghost(int ghostnum)
{
  int x;
  int y;
  int X=0;
  int Y=0;
  int dir = 0;
  if(ghostnum == 1)
    {
      X = game.blinky.x;
      Y = game.blinky.y;
      dir = dir_blinky;
    }
  pixel_To_MatCoord(X,Y,&x,&y);
  int XP,YP;
  pixel_To_MatCoord(game.pac_man.x,game.pac_man.y,&XP,&YP);
  if((x*28+y)==(XP*28+YP))
    return 1;
  else
    {
      if(dir == 28 || dir == -28)//N or S
	{
	  if(map[x][y]==0 && map[x][y+1]==0)
	    {
	      return 1;
	    }
	}
      
      if(dir == 1 || dir == -1)//E or W
	{
	  if(map[x+1][y]==0 && map[x-1][y]==0)
	    {
	      return 1;
	    }
	}
      
    }
  return 0;
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
  //-------------------ghost move---------------------------------------------
  //blinky
  pixel_To_MatCoord(game.pac_man.x,game.pac_man.y,&X,&Y);//update pac man coord
  printf("\n new loop \n ");
  int xb;
  int yb;
  pixel_To_MatCoord(game.blinky.x,game.blinky.y,&xb,&yb);
  printf("blinky coord mat:  %i ; pac mand coord  %i ; prev coord : %i \n",xb*28 + yb,X*28+Y,(xb*28)+yb-dir_blinky);
  printf("blinky coord x:  %i ; y  %i \n",xb,yb);

  srand(time(0));
  
  if(choose_to_move_ghost(1) == 0)
    {
      printf("lauched cancer blinky \n");
      dir_blinky = random_ghost();
      //dir_blinky = blinky(xb*28+yb ,X*28+Y ,map,(xb*28)+yb-dir_blinky);
    }
  printf("blinky coord pix : x %i ; y %i \n",game.blinky.x,game.blinky.y);
  printf("blinky dir : %i\n",dir_blinky);
  
  move_ghost(1);
  
  printf("ghost moved\n");
  printf("blinky coord pix : x %i ; y %i \n",game.blinky.x,game.blinky.y);
  
  draw(game.blinky.x - ghost_speed, game.blinky.y - ghost_speed, 22 +
      ghost_speed*2, 22 +ghost_speed*2);
  /*
  //inky
  int xi;
  int yi;
  pixel_To_MatCoord(game.inky.x,game.inky.y,&xi,&yi);
  if(choose_to_move_ghost(2) == 0)
    {
      //dir_inky = inky(xi*28+yi ,X*28+Y ,map,(xi*28)+yi-dir_inky);
    }
  move_ghost(2);
  draw(game.inky.x - ghost_speed, game.inky.y - ghost_speed, 22 +
      ghost_speed*2, 22 +ghost_speed*2);

  //clyde
  int xc;
  int yc;
  pixel_To_MatCoord(game.clyde.x,game.clyde.y,&xc,&yc);
  if(choose_to_move_ghost(3) == 0)
    {
      //dir_clyde = clyde(xc*28+yc ,X*28+Y ,map,(xc*28)+yc-dir_clyde);
    }
  move_ghost(3);
  draw(game.clyde.x - ghost_speed, game.clyde.y - ghost_speed, 22 +
      ghost_speed*2, 22 +ghost_speed*2);

  //pinky

  int xp;
  int yp;
  pixel_To_MatCoord(game.pinky.x,game.pinky.y,&xp,&yp);
  if(choose_to_move_ghost(4) == 0)
    {
      //dir_pinky = pinky(xp*28+yp ,X*28+Y ,map,(xp*28)+yp-dir_pinky);
    }
  move_ghost(3);
  draw(game.pinky.x - ghost_speed, game.pinky.y - ghost_speed, 22 +
      ghost_speed*2, 22 +ghost_speed*2);
  */

  printf("ghost drawn \n");
  
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
