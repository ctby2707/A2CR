#ifndef QUEUE
#define QUEUE

typedef struct Batch
{
  double *cur_state;
  int actions;
  double q_target;
  double q;
}Batch;

typedef struct queue_b
{
    struct Batch *val;

    struct queue_b *next;
} queue_b;

queue_b *Batch_push(queue_b *start, struct Batch val);

queue_b *Batch_pop(queue_b *start, struct Batch *pval);

void Batch_empty(queue_b **pstart);

int Batch_len(queue_b *start);

#endif
