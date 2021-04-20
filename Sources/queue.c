#include <err.h>
#include <stdlib.h>
#include "queue.h"

queue *queue_push(queue *start, node val)
{
  queue *q = malloc(sizeof(struct queue));
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

queue *queue_pop(queue *start, node *pval)
{
  struct queue *q = start->next;
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

void queue_empty(queue **pstart)
{
  queue *q = *pstart;
  while (q != NULL)
  {
    int vald = 0;
    q = queue_pop(q, &vald);
  }
}
