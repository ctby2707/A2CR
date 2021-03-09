#ifndef FIFO_H
#define FIFO_H
#include "cell.h"

struct _file {
   int length;
   Cell head;
   Cell queue;
};

typedef struct _file* File;

#define fileIsEmpty (F) ((F) -> length == 0)

File Emptyfile ();
int Length(File F);
void Puton(File F, int element);
int Head(File F);
void Scroll(File F);
int Scrolling(File F);
void WriteFile(File F);

#endif
