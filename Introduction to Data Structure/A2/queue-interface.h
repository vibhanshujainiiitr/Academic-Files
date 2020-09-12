/* Interface files */
#include "queue-types.h"

Queue* create_Queue();
/* creates an empty queue that you can push values into. Returns
pointer to queue. */

void enqueue(int value; Queue* Q );
/* Adding an element to the queue */

int dequeue (Queue*);
/* Removing the element to the queue and returing the value stored in it, if queue is empty then it will return INT_MIN*/

int top(struct Queue* Q);
/* Returns the value stored at the top of the queue, without changing anything in the original queue */

int is_empty(struct Queue* Q);
/* Return '1' if the queue is empty, else return '0' */

struct Queue* clone_queue(Queue* Q);
/* Clone the complete queue into a new queue and returns its pointer */

struct Queue* sort_queue(struct Queue* Q);
/*Sort the queue in assending order ( minimum at front ), and return back the pointer to queue.
Note this didn't create a new queue, it modifies the original one */

int play_queue(Queue* q, int k);
/*Return the position of the person*/

struct Queue* remove_duplicates(Queue*);
/* Removes duplicates from the queue; i.e. removes integers that are repeated in the queue and return the pointer to the queue. Again there is no new queue formed, all the changes are done in original queue */






