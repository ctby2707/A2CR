#include <stdlib.h>
#include <math.h>
#include "saverfile.h"
#include "game_init.h"

int action_choosen = -1;
int state = 0;
double *Q_tab;
double vitesse_apprentissage;
double facteur_actualisation;
int exploration;
int time_s = 0;

void init_Qlearning()
{
  Q_tab = calloc(4*868,sizeof(double));
  loadfile("Data/Q_tab.txt", Q_tab, 868*4);
  vitesse_apprentissage = 0.85;
  facteur_actualisation = 0.99;
  exploration = 80; // pourcentage de chance qu'il fasse une direction random
}

char execute_Qlearning(Game *game, int cur_state)
{
  int random = rand() % 100;
  state = cur_state;
  if(random < exploration)
  {
    char dir = game->pac_man.dir;
    char rest = game->pac_man.dir;
    if (dir == 'N')
      dir = 'S';
    else if (dir == 'G')
      dir = 'D';
    else if (dir == 'S')
      dir = 'N';
    else if(dir =='D')
      dir='G';
    do{
      action_choosen = rand() % 4;
      if(action_choosen == 0)
        rest = 'N';
      if(action_choosen == 1)
        rest = 'S';
      if(action_choosen == 2)
        rest = 'G';
      if(action_choosen == 3)
        rest = 'D';
    }while(rest == dir);
    return rest;
  }
  else
  {
    int index = 0;
    int max = 0;
    for(int i = 0; i < 4; i++)
    {
      if(Q_tab[cur_state*4+i] > max)
      {
        index = i;
        max = Q_tab[cur_state*4+i];
      }
    }
    action_choosen = -1;
    if(index == 0)
      return 'N';
    if(index == 1)
      return 'S';
    if(index == 2)
      return 'G';
    if(index == 3)
      return 'D';
  }
  return 'D';
}

void adjust_Q_tab(int reward)
{
  if(action_choosen == -1)
    return;
  int new_state =0;
  if (action_choosen == 0)
    new_state = state - 28;
  if (action_choosen == 1)
    new_state = state + 28;
  if (action_choosen == 2)
    new_state = state - 1;
  if (action_choosen == 3)
    new_state = state + 1;
  int max = 0;
  for(int i = 0; i < 4; i++)
  {
    if(Q_tab[new_state*4+i] > max)
    {
      max = Q_tab[new_state*4+i];
    }
    time_s++;
  }
  Q_tab[state*4+action_choosen] = Q_tab[state*4+action_choosen] + vitesse_apprentissage * (reward +  facteur_actualisation * max - Q_tab[state*4+action_choosen]);
  if(time_s == 1000)
  {
    savefile ("Data/Q_tab.txt", Q_tab, 868*4);
    time_s = 0;
  }
}
