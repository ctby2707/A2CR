#include "game_init.h"

//-------------------------INITIALISATION-------------------------------------
int map[31][28] = {
// 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7 and don't touch this line :(
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //0
  {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},  //1
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //2
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //3
  {0, 2, 2, 2, 2, 3, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 3, 2, 2, 2, 2, 0},  //4
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //5
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //6
  {0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0},  //7
  {0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //8
  {0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //9
  {42, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 43},//10
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 4, 4, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //11
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //12
  {0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //13
  {0, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0},  //14
  {0, 1, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //15
  {0, 1, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //16
  {0, 1, 1, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 1, 1, 0},  //17
  {0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0},  //18
  {0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0},  //19
  {44, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 45},//20
  {0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //21
  {0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //22
  {0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0},  //23
  {0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //24
  {0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //25
  {0, 2, 0, 0, 2, 3, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 3, 2, 0, 0, 2, 0},  //26
  {0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0},  //27
  {0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0},  //28
  {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},  //29
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; //30

int pac_man_open[7][7] = {
  {1, 1, 0, 0, 0, 1, 1},
  {1, 0, 0, 1, 0, 0, 1},
  {0, 0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 1, 1}};

int pac_man_closed[7][7] = {
  {1, 1, 0, 0, 0, 1, 1},
  {1, 0, 0, 1, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 1, 1}};

int ghost_pixel_art[7][7] = {
  {0, 0, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 0},
  {1, 2, 2, 1, 2, 2, 1},
  {1, 2, 0, 1, 2, 0, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 0, 1, 0, 1}};

int list_clyde[5] = {648,645,813,821,737};

int list_inky[5] = {667,670,838,830,746};

int list_blinky[4] = {133,138,54,49};

int list_pinky[4] = {118,113,29,34};

Game *init_game(){
  Game *game = malloc(sizeof(Game));
  Ghost *blinky = malloc(sizeof(Ghost));
  Ghost *inky = malloc(sizeof(Ghost));
  Ghost *clyde = malloc(sizeof(Ghost));
  Ghost *pinky = malloc(sizeof(Ghost));
  Pac_Man *pac_man = malloc(sizeof(Pac_Man));
  game->pac_man = *pac_man;
  game->respawn = 0;
  game->pac_man.x = 307;
  game->pac_man.y = 377;
  game->pac_man.X = 16;
  game->pac_man.Y = 13;
  game->pac_man.dir = 'N';
  game->pac_man.reqdir = 'N';
  game->pac_man.color = 'y';
  game->pac_man.lasttile = 464;
  game->mode = 0; //mode 0 = the dumb AI, mode 1 = the even dumber agent, mode 3 = nothing just wanted to add a third mode 
  game->status = 0; //status 0 = stopped, status 1 = playing
  game->map = (int *)map;
  game->pac_man_open = (int *)pac_man_open;
  game->pac_man_closed = (int *)pac_man_closed;
  game->ghost_pixel_art = (int *)ghost_pixel_art;
  game->score = 0;
  game->live = 3;
  game->level = 1;
  game->pacgum = 0;
  game->reward = 0;
  game->hunt = 0;
  game->chase = 0;
  game->scater = 168;//set time 168 for 7 sec
  game->open = 0;
  game->combo = 200;
  game->blinky = *blinky;
  game->blinky.x = 318; //13
  game->blinky.y = 311; //14
  game->blinky.dir = 'N';
  game->blinky.list = (int *) list_blinky;
  game->blinky.n = 0;
  game->blinky.eat = 0;
  game->inky = *inky;
  game->inky.x = 318; //13
  game->inky.y = 311; //14
  game->inky.dir = 'N';
  game->inky.list = (int *) list_inky;
  game->inky.n = 0;
  game->inky.eat = 0;
  game->clyde = *clyde;
  game->clyde.x = 318; //14
  game->clyde.y = 311; //13
  game->clyde.dir = 'N';
  game->clyde.list = (int *) list_clyde;
  game->clyde.n = 0;
  game->clyde.eat = 0;
  game->pinky = *pinky;
  game->pinky.x = 318; //13
  game->pinky.y = 311; //14
  game->pinky.dir = 'N';
  game->pinky.list = (int *) list_pinky;
  game->pinky.n = 0;
  game->pinky.eat = 0;

  return game;
}
