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

struct Queue* create_queue()
{
    struct
}
