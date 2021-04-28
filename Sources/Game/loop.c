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
int Q_ACTIVATED =  1;

const int pac_man_speed = 6;
const int ghost_speed = 4;

int Score = 0; // Score of the Q-learning // debbuging
void set_score(Game *game);

gboolean loop()
{
  Game *game = get_game();
  if(game->isFirstGame == 1) // first start of the game
  {
    generate_random_generation(NB_CHILD, game, RANDOM_GEN);
    game->isFirstGame = 0;
    if(Q_ACTIVATED == 0)
    {
    printf("--------------------\n");
    printf("Generation : %i\n",game->generation);
    printf("Child : %i\n",game->index);
    request_move(game, Call_Neural_Network(game));
    }
  }

  if (game->status == 0) //break loop if game is in pause status
    return TRUE;

  if (game->pacgum >= 258) //258 = max pac gum
    levelup(game);// pac-man has finished the level

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
  int X = game->pac_man.X;
  int Y = game->pac_man.Y;
  if(Q_ACTIVATED == 1 && (game->pac_man.dir == game->pac_man.reqdir ||
                  (game->pac_man.reqdir == 'N' && game->map[(X - 1)*28+Y] == 0)||
                  (game->pac_man.reqdir == 'S' && game->map[(X + 1)*28+Y] == 0)||
                  (game->pac_man.reqdir == 'G' && game->map[X*28+(Y-1)] == 0)||
                  (game->pac_man.reqdir == 'D' && game->map[X*28+(Y+1)] == 0)))
  {//Q learning
    adjust_Q_tab(Score);
    int X_pc, Y_pc;
    pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X_pc, &Y_pc);
    if(game->pac_man.X != X_pc || game->pac_man.Y != Y_pc)
      Score = 1;
    else
      Score = 0;
    char dir = execute_Qlearning(X_pc*28+Y_pc);
    printf("%c\n",dir);
    request_move(game, dir);
  }
  if(Q_ACTIVATED == 0 &&  game->pac_man.dir == game->pac_man.reqdir)
    request_move(game, Call_Neural_Network(game)); // call the neural Network
  request_move(game, game->pac_man.reqdir);
  move_entity(game, &game->pac_man.x, &game->pac_man.y, game->pac_man.dir, pac_man_speed); //pac-man


  //----------------------------GHOSTS MANAGEMENT------------------------------
  if(game->chase>0)
  {
    //chase mode 
    randome_dir(game, &game->blinky);
    randome_dir(game, &game->clyde);
    randome_dir(game, &game->inky);
    randome_dir(game, &game->pinky);
  }

  if (game->hunt > 0 && game->chase ==0 && Q_ACTIVATED == 0) //hunt mode
  {
    define_direction(&game->blinky, 'b', game);
    define_direction(&game->clyde, 'c', game);
    define_direction(&game->inky, 'i', game);
    define_direction(&game->pinky, 'p', game);
  }

  if(game->scater > 0 && game->chase == 0)
  {

    define_scater_mode(game, &game->blinky);
    define_scater_mode(game, &game->clyde);
    define_scater_mode(game, &game->inky);
    define_scater_mode(game, &game->pinky);
  }
  if(Q_ACTIVATED == 0)
  {
    move_entity(game, &game->blinky.x, &game->blinky.y, game->blinky.dir, ghost_speed);
    if(game->pacgum / game->level > 5)
      move_entity(game, &game->clyde.x, &game->clyde.y, game->clyde.dir, ghost_speed);
    if(game->pacgum / game->level > 15)
      move_entity(game, &game->inky.x, &game->inky.y, game->inky.dir, ghost_speed);
    if(game->pacgum / game->level > 30)
      move_entity(game, &game->pinky.x, &game->pinky.y, game->pinky.dir, ghost_speed);
  }

  //Score management
  set_score(game);

  //Lives pac-man management
  is_pac_man_dead(game);
  if (game->live == 0)
    restart(game, NB_CHILD, Q_ACTIVATED);

  draw(0, 0, 637, 760);
  return TRUE;
}

void set_score(Game *game)
{
  int X, Y;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
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
}
