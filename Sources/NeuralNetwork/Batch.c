#include <err.h>
#include <stdlib.h>
#include "Batch.h"

queue_b *Batch_push(queue_b *start, struct Batch val)
{
  queue_b *q = malloc(sizeof(struct queue_b));

  Batch *batch = malloc(sizeof(Batch));

  batch->cur_state = val.cur_state;
  batch->actions = val.actions;
  batch->q_target = val.q_target;
  batch->q = val.q;


  if (q == NULL)
    errx(3, "Error with malloc()");
  q->val = batch;
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
  *pval = *q->val;
  free(q->val);
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
    free(vald.cur_state);
  }
}

int Batch_len(queue_b *start)
{
  if(start == NULL)
    return 0;
  queue_b *q = start;
  int len = 0;
  do
  {
    len++;
    q = q->next;
  }while(q != start);

  return len;
}
