#include "GTK.h"
#include "game_init.h"
#include "main.h"
#include "NeuralNetworks_manager.h"
#include "NeuralNetwork.h"
#include "pac-man.h"
#include "game_events.h"
#include "Q.h"
#include "chase.h"
#include "ghost_parser.h"
#include "scatter.h"

#define NB_CHILD 10
#define RANDOM_GEN 1
#define GHOSTS_ACTIVATED 1

const int pac_man_speed = 6;
const int ghost_speed = 4;

gboolean loop()
{
  Game *game = get_game();
  if(game->isFirstGame == 1)
  {
    generate_random_generation(NB_CHILD, game, RANDOM_GEN);
    game->isFirstGame = 0;
    printf("--------------------\n");
    printf("Generation : %i\n",game->generation);
    printf("Child : %i\n",game->index);
    request_move(game, Call_Neural_Network(game));
  }
  if (game->status == 0) //break loop if game is in pause status
    return TRUE;
  if (game->pacgum >= 258) //258 = max pac gum
    levelup(game);
  if (game->chase > 0)
  {
    game->chase = game->chase - 1;
    if (game->chase == 0 || (game->chase < 30 && game->chase % 2 == 0))
    {
      game->pac_man.color = 'y';

    }
    else
      game->pac_man.color = 'b';

    if(game->chase == 0)
    {
      game->combo = 200;
      game->blinky.eat = 0;
      game->inky.eat = 0;
      game->pinky.eat = 0;
      game->clyde.eat = 0;
    }
  }
  if(game->chase == 0)
  {
    if(game->hunt>0)
    {
      game->hunt = game->hunt - 1;
      if(game->hunt == 0)
      {
        game->scater = 168;
      }
    }
    if(game->scater>0)
    {
      game->scater = game->scater - 1;
      if(game->scater == 0)
      {
        game->hunt = 480;//set time to 480 for 2
      }
    }
  }
  request_move(game, Call_Neural_Network(game));

  /*Q learning
  if(IS_Q_ACTIVATED == 1)
  {
    adjust_Q_tab(game->score-game->prevScore);
    game->prevScore = game->score;
    int X_pc, Y_pc;
    pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_pc, &Y_pc);
    char dir = execute_Qlearning(X_pc*28+Y_pc);
    //printf("%c\n",dir);
    request_move(dir);
  }*/



  request_move(game, game->pac_man.reqdir);
  move_entity(game, &game->pac_man.x, &game->pac_man.y, game->pac_man.dir, pac_man_speed); //pac-man
  //---------------------------------GIVE INFOS----------------------------------
  int X, Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  /*
     printf("\n---------------------NEW LOOP------------------------------\n");
     int X_mat_blinky;
     int Y_mat_blinky;
     pixel_To_MatCoord(game.blinky.x, game.blinky.y, &X_mat_blinky, &Y_mat_blinky);

  //print current coords

  printf("blinky coord:\n  x :%i(%i);\n  y:%i(%i);\npac man coord\n  x:%i(%i);\n  y:%i(%i);\n",
  X_mat_blinky,game.blinky.x, Y_mat_blinky, game.blinky.y,
  X,game.pac_man.x,Y,game.pac_man.y);
  printf("previous_dir: %c\n",game.blinky.dir);
   */
  if(game->chase>0)
  {
    //chase mode 
    randome_dir(game, &game->blinky);
    randome_dir(game, &game->clyde);
    randome_dir(game, &game->inky);
    randome_dir(game, &game->pinky);
  }
  if (game->hunt > 0 && game->chase ==0 && GHOSTS_ACTIVATED == 1) //hunt mode
  {
    //----------------------------BLINKY DIRECTION---------------------------------
    define_direction(&game->blinky, 'b', game);

    //---------------------------CLYDE DIRECTION-----------------------------------
    define_direction(&game->clyde, 'c', game);

    //---------------------------INKY DIRECTION------------------------------------

    define_direction(&game->inky, 'i', game);
    //---------------------------PINKY DIRECTION-----------------------------------

    define_direction(&game->pinky, 'p', game);
    //-----------------------------END-------------------------------------------
  }
  if(game->scater > 0 && game->chase == 0)
  {

    define_scater_mode(game, &game->blinky);

    define_scater_mode(game, &game->clyde);

    define_scater_mode(game, &game->inky);

    define_scater_mode(game, &game->pinky);


  }
  if(GHOSTS_ACTIVATED == 1)
  {
    move_entity(game, &game->blinky.x, &game->blinky.y, game->blinky.dir, ghost_speed);
    if(game->pacgum / game->level > 5)
      move_entity(game, &game->clyde.x, &game->clyde.y, game->clyde.dir, ghost_speed);
    if(game->pacgum / game->level > 15)
      move_entity(game, &game->inky.x, &game->inky.y, game->inky.dir, ghost_speed);
    if(game->pacgum / game->level > 30)
      move_entity(game, &game->pinky.x, &game->pinky.y, game->pinky.dir, ghost_speed);
  }

  draw(0, 0, 637, 760);
  //---------------SCORE
  if (game->map[X*28+Y] == 2)
  {
    game->pacgum = game->pacgum + 1;
    game->map[X*28+Y] = 6;
    game->score = game->score + 10;
    char str[42];
    sprintf(str, "Score : %i \n", game->score);

    set_score_label(str);
  }
  if (game->map[X*28+Y] == 3)
  {
    game->pacgum = game->pacgum + 1;
    game->pac_man.color = 'b';
    game->chase = 170;
    game->map[X*28+Y] = 7;
  }

  //----------DEAD or ALIVE
  is_pac_man_dead(game);
  if (game->live == 0)
    restart(game, NB_CHILD);

  //draw(game.pac_man.x - pac_man_speed, game.pac_man.y - pac_man_speed, 22 +
  //    pac_man_speed*2, 22 +pac_man_speed*2);
  //------------------------
  return TRUE;
}
