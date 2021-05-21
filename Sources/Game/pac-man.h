#ifndef PAC_MAN_H
#define PAC_MAN_H

void is_pac_man_dead(Game *game, int interface_on);
void request_move(Game *game, char dir);
void move_pac_man(Game *game, int *x, int *y, char dir, int speed);
void move_entity(Game *game, int *x, int *y, char dir, int speed);

#endif
