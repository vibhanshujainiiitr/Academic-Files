#include <stdio.h>
#include <stdlib.h>

struct Q_node
{
    int data;
    struct Q_node* next;
    struct Q_node* prev;
};

struct queue
{
    struct Q_node *front, *rear;
};

struct Q_node* new_node_queue( int k )
{
    struct Q_node* temp = (struct Q_node*)malloc(sizeof(struct Q_node));
    temp->data = k;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

struct queue* create_queue()
{
    struct queue* temp = (struct queue*)malloc(sizeof(struct queue));
    temp->front = NULL;
    temp->rear = NULL;
    return temp;
}

void enqueue( struct queue* Queue, int k )
{
    struct Q_node* temp = new_node_queue(k);

    if(Queue->rear == NULL)
    {
        Queue->front = Queue->rear = temp;
        return;
    }

    Queue->rear->next = temp;
    temp->prev = Queue->rear;
    Queue->rear = temp;
    return;
}

int dequeue(struct queue* Queue)
{
    if(Queue->front == NULL)
        return;

    struct Q_node* temp = Queue->front;

    Queue->front = Queue->front->next;

    if(Queue->front == NULL)
        Queue->rear = NULL;
    else
        Queue->front->prev = NULL;

    int data = temp->data;
    free(temp);
    return data;
}

int isEmpty(struct queue* Queue)
{
    if(Queue->front == NULL)
        return 1;

    return(0);
}

int main()
{
    struct queue* q = create_queue();
    enqueue(q, 10);
    enqueue(q, 20);
    printf("        %d \n",dequeue(q));
  //  printf("%d\n", isEmpty(q));
    enqueue(q, 30);
    printf("        %d \n",dequeue(q));
    enqueue(q, 40);
   // printf("%d\n", isEmpty(q));
    enqueue(q, 50);
    printf("        %d \n",dequeue(q));
    printf("        %d \n",dequeue(q));
    printf("        %d \n",dequeue(q));
    printf("        %d \n",dequeue(q));
    printf("        %d \n",dequeue(q));
    printf("%d", isEmpty(q));
   // printf("Queue Front : %d \n", q->front->data);
   // printf("Queue Rear : %d", q->rear->data);

    return 0;
}
