#ifndef QUEUE
#define QUEUE

typedef struct Batch
{
  int *cur_state;
  int *actions;
  int reward;
  int *next_state;
}Batch;

typedef struct queue_b
{
    // Value of an element.
    struct Batch val;

    // Pointer to the next element.
    struct queue_b *next;
} queue_b;

// Pushes a new value onto a queue.
// start = Starting address of the queue.
// val = Value to push.
// Returns the new starting address of the queue.
queue_b *Batch_push(queue_b *start, struct Batch val);

// Pops a value off a queue.
// start = Starting address of the queue.
// pval = Pointer used to return the value.
// Returns the new starting address of the queue.
queue_b *Batch_pop(queue_b *start, struct Batch *pval);

// Removes all the elements of a queue.
// pstart = Address that contains the starting address of the queue.
// Must set the starting address to NULL.
void Batch_empty(queue_b **pstart);

#endif
