#include "GTK.h"
#include "game_init.h"
#include "main.h"
#include "pac-man.h"
#include "game_events.h"
#include "chase.h"
#include "ghost_parser.h"
#include "scatter.h"

const int pac_man_speed = 6;
const int ghost_speed = 4;
void set_score(Game *game, int interface_on);

gboolean loop(int interface_on)
{
  Game *game = get_game();

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
  //game->pac_man.lasttile = X*28 + Y;
  int x = game->pac_man.x;
  int y = game->pac_man.y;

  move_pac_man(game, &game->pac_man.x, &game->pac_man.y, game->pac_man.dir, pac_man_speed); //pac-man

  //----------------------------GHOSTS MANAGEMENT------------------------------
  if(game->chase>0)
  {
    //chase mode

    randome_dir(game, &game->blinky);
    randome_dir(game, &game->clyde);
    randome_dir(game, &game->inky);
    randome_dir(game, &game->pinky);

    /*
       define_scater_mode(game, &game->blinky);
       define_scater_mode(game, &game->clyde);
       define_scater_mode(game, &game->inky);
       define_scater_mode(game, &game->pinky);
     */
  }

  if (game->hunt > 0 && game->chase ==0 ) //hunt mode
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

  //Score management
  set_score(game, interface_on);

  //Lives pac-man management
  is_pac_man_dead(game, interface_on);
  if (game->live == 0)
    restart(game, interface_on);

  if(interface_on == 1)
    draw(0, 0, 637, 760);
  return TRUE;
}

void set_score(Game *game, int interface_on)
{
  int X = 0;
  int Y = 0;
  pixel_To_MatCoord(game->pac_man.x, game->pac_man.y, &X, &Y);
  if (game->map[X*28+Y] == 2)
  {
    game->pacgum += 1;
    game->map[X*28+Y] = 6;
    game->score += 10;
    game->reward += 10;
    char str[42];
    sprintf(str, "Score : %i \n", game->score);

    if(interface_on == 1)
      set_score_label(str);
  }
  if (game->map[X*28+Y] == 3)
  {
    game->reward += 15;
    game->pacgum += 1;
    game->pac_man.color = 'b';
    game->chase = 170;
    game->map[X*28+Y] = 7;
  }
}
