#include <err.h>
#include <stdlib.h>
#include "Batch.h"

queue_b *Batch_push(queue_b *start, struct Batch val)
{
  queue_b *q = malloc(sizeof(struct queue_b));
  if (q == NULL)
    errx(3, "Error with malloc()");
  q->val = val;
  if (start == NULL)
  {
    q->next = q;
  }
  else
  {
    q->next = start->next;
    start->next = q;
  }
  return q;
}

queue_b *Batch_pop(queue_b *start, struct Batch *pval)
{
  struct queue_b *q = start->next;
  *pval = q->val;
  if (start->next->next != start->next)
  {
    start->next = q->next;
    free(q);
    return start;
  }
  else
  {
    free(q);
    return NULL;
  }
}

void Batch_empty(queue_b **pstart)
{
  queue_b *q = *pstart;
  while (q != NULL)
  {
    Batch vald;
    q = Batch_pop(q, &vald);
  }
}

int Batch_len(queue_b *start)
{
  queue_b *q = start;
  int len;
  do
  {
    len++;
    q = q->next;
  }while(q != start);
  return len;
}
