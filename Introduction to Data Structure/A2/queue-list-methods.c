#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue-interface.h>
#include <queue-types.h>

struct Queue* createQueue()
    {
        struct Queue* a = (struct Queue*)malloc(sizeof(struct Queue));                      // 'a' new queue is formed
        a->front = NULL;                                                                    //Front of a is set to NULL
        a->rear = NULL;                                                                     //Rear of a is set to NULL
        return a;                                                                           //Returning the pointer to a
    };

void enqueue(int value, struct Queue* Q) {
	struct node* temp = (struct node*)malloc(sizeof(struct node));                          //Blocking the memoring of temp of size of node
	temp->data =value;                                                                      //Entering the data in the temp
	temp->next = NULL;
	if(Q->front == NULL && Q->rear == NULL){                                                //If temp is the first element then, both front and rear of Q will point to it
		Q->front = Q->rear = temp;
		return;
	}
	Q->rear->next = temp;                                                                   // Adding the temp to the queue
	temp->prev = Q->rear;
	Q->rear = temp;
}

int dequeue(struct Queue* Q)
    {
        // If queue is empty
            if(Q->front == NULL)                                                            //If queue is empty then, returning the INT_MIN value
                {
//                  printf("Error, the list is empty");                                     //If you want to print error if queue is empty then uncomment it
                    return INT_MIN;
                }
            node* temp = Q->front;
            Q->front = Q->front->next;

//            if(Q->front==NULL)
//                {
//                    Q->rear = NULL;
//               }
            int data = temp->data;                                                           //Storing the data of the queue which will be removed in data
            free(temp);                                                                      //Free the temp node
            return(data);                                                                    // Returning the data of the removed node
    }

int top(struct Queue* Q)
    {
        if(Q->front==NULL)                                                                   //If queue is empty return INT_MIN
        {return INT_MIN;
        }

        return(Q->front->data);                                                             //Returing the data stored in the front node
    }

int is_empty(struct Queue* Q)
    {
        if(Q->front==Q->rear)                                                               //If both front and rear are same then and list is empty and return '1'
            return 1;
        else
            return 0;                                                                        //If list is non empty then return '0'
    }

struct Queue* clone_queue(Queue* Q)
    {
         struct Queue* Q_new = createQueue()                                                // Making new queue
         struct node* temp = (struct node*)malloc(sizeof(struct node));                     // Allocating memory to new node
         temp = Q->front;

         while(temp!= NULL)
         {
            enqueue(temp->data,Q_new);                                                      // Adding the data of previous queue to the new queue
            temp = temp->next;                                                              // moving forward in the queue
         }
         if(temp == NULL)                                                                   // if list is completed then return the pointer to the new queue
             {return Q_new;
             }

         return Q_new;
    }

void swap(int *a, int *b)                                                                   //Function to swap the two int values
    {
        int temp = *a;
        *a = *b;
        *b =temp;
    }

int length(struct Queue* Q)                                                                 // Funtion to give the length of queue
    { int len;
      len = 0;
      node* temp = Q->front;

      while(temp!=NULL)
        {
            temp = temp->next;
            len ++;
        }

      return len;
    }

struct Queue* sort_queue(struct Queue* Q)
    {
        struct node *a, *b;                                                                 //Two new node pointer a and b
        a = Q->front;                                                                       //a pointed to front
        while( a->next != NULL)
        {
            b = a->next;                                                                    //b is the next pointer of a in starting
            while( b != NULL)
                {
                    if(a->data > b->data)                                                   //If data in a is greater then data in b then swap both
                    { swap(&a->data, &b->data); }

                    b = b->next;                                                            //Making the b to point next to move forward and check with all the members
                }
            a = a->next;                                                                    // Now the data in 'a' is at correct position and hence moving forward the 'a' to next element in the queue
        }
        return Q;
    }

struct Queue* remove_duplicates(Queue* Q)
    {
        struct node *a, *b;                                                                 // Two new node pointer a and b
        a = Q->front;                                                                       // a pointed to front of the queue

        while(a->next!= NULL)
            {
                b = a->next;                                                                //b is initialises to next of 'a'
                while(b->next!= NULL)
                {
                    if(a->data == b->data)                                                  // if data stored in a and b are same then remove 'b' from the complete Queue
                    {

                       node* store_next = b->next;
                       node* store_prev = b->prev;
                       store_next->prev = store_prev;
                       store_prev->next = store_next;
                       free(b);
                     }
                    b = b->next;                                                            //b is again pointed to next element so that it can traverse the remaininig list in recursion
                }

                if(b->next==NULL && a->data == b->data)
                     {
                        node* c = &b->prev;
                        c->next = NULL;                                                      // Making the node just before rear ie 'b' in this case to point to next as NULL , for example if c : is just before b, then make c->next  = NULL
                       free(b);
                     }

                a = a->next;                                                                 // a is pointed to next element so that we can check the condition with all the elements
            }
        return Q;

    }


int play_queue(Queue* q, int k)
    {
        struct Queue* Q= createQueue();                                                     // Creating new queue
        int n = length(q);                                                                  // Counting the number of students

        for( int i=0; i<n; i++)
            {
                enqueue(i+1,Q);                                                             //Storing the position of student in the new queue
            }

        Q->front->prev = Q->rear;                                                           //Making the queue circular
        Q->rear->next = Q->front;
        node* temp = Q->front;                                                              //temp will point the front and count will start from '1'
        int count = 1;
        while(temp->next != temp && temp->prev!= temp )                                     //Loop will run till there is only one element remaining
            {
                while(count != k)                                                           //loop will run till it reaches the kth term
                    {
                        temp = temp->next;
                        count = count+1;
                    }
                if(count==k)                                                                //If we reach the kth term
                    {
                       node* store_next = temp->next;
                       node* store_prev = temp->prev;
                       store_next->prev = store_prev;
                       store_prev->next = store_next;
                       count = 1;                                                           //Restart the count from 1
                       node* next = temp->next;                                             //next pointer will store pointer to next element in the queue
                       free(temp);                                                          //free the temp
                       temp = next;                                                         // pointing the temp to next element
                    }
            }
        if(temp->next==temp->prev)                                                          //If only one element is remaining
            {   int data = temp->data;                                                      //store its position in data
                free(temp);                                                                 //free temp and with this the complete queue 'Q' is free
                return (data);                                                              //return the position
            }
    }

void print(struct Queue* Q)                                                                    //Printing the queue
    {
        struct node* temp = Q->front;
        while(temp!=NULL)
            {
                printf("%d  ", temp->data);
                temp = temp->next;
            }
        printf("\n");
    }

