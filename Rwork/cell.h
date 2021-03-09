#ifndef CELL_H
#define CELL_H

typedef int typage;

struct _cell {
   typage element;
   struct _cell *next;
};

typedef struct _cell* Cell;

#endif
