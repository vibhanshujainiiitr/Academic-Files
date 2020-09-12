/* Header file that implements structures needed for  list data type*/

/* Basic node is added for doublt linked list */
typedef struct node
    {
        int data;
        struct node* next;
        struct node* prev;
    } node;

// Queue representation of duobly-linked list
typedef struct Queue
     {
        struct node* front ;
        struct node* rear ;
      } Queue;


