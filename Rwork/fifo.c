#include <stdio.h>
#include "cell.h"
#include "fifo.h"


File Emptyfile() {
   File F;
   F = (File)malloc(sizeof(struct _file));
   if (F == NULL) printf("error allocation");
   F->length = 0;
   F->head = F->queue = NULL;
   return(F);
}

int Length(File F) {
   if (F == NULL)printf("file don't exist");
   return(F->length);
}

void Puton(File F, typof element) {
   Cell cell;
   if (F == NULL) printf ("file don't exist");

   cell = (Cell)malloc(sizeof(struct _cell));
   if (cell == NULL) printf("error allocation memory");
   cell->element = element;
   cell->next = NULL;
   if (Length(F) == 0){
      F->head = F->queue = cell;
   }
   else {
      cell->next=F->head;
      F->head = cell;
   }
   ++(F->length);
}

typage Head(File F) {
   if (F == NULL || Length(F) == 0) printf("file don't exist");
   return(F->head->element);
}

void Scroll(File F) {
   Cell cell;

   if (F == NULL || Length(F) == 0)printf("file don't exist");
   cell = F->head;
   if (Length(F) == 1){
      F->head = F->queue = NULL;
   }
   else{
      F->head = F->head->next;
   }
   --(F->length);
   free(cell);
}

typage Scrolling(File F) {
   Cell cell;
   typage element;
   if (F == NULL || Length(F) == 0) printf("file don't exist");
   cell = F->head;
   element = cell->element;
   if (Length(F) == 1){
      F->head = F->queue = NULL;
   }
   else{
      F->head = F->head->next;
   }
   free(cell);
   --(F->length);
   return(element);
}

void WriteFile(File F) {
   Cell cell;

   if (F == NULL) printf("error WriteFile");
   cell = F->head;
   while (cell != NULL) {
      printf("%d ", cell->element);
      cell = cell->next;
   }
   printf("\n");
}
