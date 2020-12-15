/*
Assignment 4
Roll Number: CS19B1027
Name: Vibhanshu Jain
*/



#include <stdio.h>
#include <stdlib.h>

#define notvisited 0
#define visited 1

/* =================  Queue Implementation ==================== */

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
        return 0;

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

    return 0;
}


/*================================ Queue list implementation ended ===================*/



/*===============------------- Graph Implementation started ------------=========*/
// The node of graph
struct node
{
    int data;
    int state;                  // To store the current state of the node
    struct node* next;
};


// To represent adjacency list
struct adj_list
{
    struct node* head;
    // The only pointer to the head node
};


struct graph
{
    int num_vertex;
    // Integer to store the number of vertices

    struct adj_list* array;
    // array to store the head pointers
    // Array of pointer
};


// New adjacency list node
struct node* new_node ( int data)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    // Setting the intitial state as notvisited
    newNode->state = notvisited;
    return newNode;
}

// Creating a graph
struct graph* createGraph( int vertices )
{
    // Memory allocation for the graph
    struct graph* Graph = (struct graph*)malloc(sizeof(struct graph));
    Graph->num_vertex = vertices;

    // Creating a adjacency list
    Graph->array = (struct adj_list*)malloc(vertices* sizeof(struct adj_list));

    // making all the heads as null
    for(int i = 0; i <vertices ; i++)
    {
        // Making the head of all adjacency list as null
        Graph->array[i].head = NULL;
    }

    return Graph;
}

void new_edge( struct graph* Graph, int a, int b)
{
    // We need to sort the elements in the queue in ascending order
    // Adding a edge from a to b
    struct node* X = new_node(a);
    struct node* Y = new_node(b);

    // Insert the element at correct position

    //If both the elements inputed are equal, then we cannot create any edge here, but we may input them as the head of their adjacency list
    if( a == b)
    {
        if(Graph->array[a].head == NULL)
            Graph->array[a].head = X;

        return;
    }


    if( Graph->array[a].head == NULL)
    {
        // If this is the first element in the complete list, then made this as head
        Graph->array[a].head = X;
    }

    // If this is not the head then insert it at the correct position
    else
    {
        struct node* temp = Graph->array[a].head;
        // Case 1
        // The first element is greater than this element, than replace the head
        if(temp->data > b)
        {
            Y->next = temp;
            Graph->array[a].head = temp;
        }

        // Traverse the complete list to find the position where it can be inserted
        else
        {
            // A new varible so that we can traverse the complete list which must be equal to head at initial
            struct node* test = temp;

            // Now traverse the complete list until you found the appropriate position

            // The element to be added is in the second position
            if(test->data < b && test->next == NULL)
            {
                test->next = Y;
                Y->next = NULL;
            }

            // The element to be added is not in the first two
            while(test->next != NULL)
            {
                if(test->data < b && test->next->data >b)
                {
                    //Input the element in the middle of both of them
                    Y->next = test->next->next;
                    test->next = Y;
                }
                test = test->next;
            }

            // The element to be inserted is in the last
            if(test->data < b && test->next == NULL)
            {
                test->next = Y;
                Y->next = NULL;
            }
        }
    }


    // Inputing into the second element adjacency list


    if( Graph->array[b].head == NULL)
    {
        // If this is the first element in the complete list, then made this as head
        Graph->array[b].head = Y;
    }

    // If this is not the head then insert it at the correct position
    else
    {
        struct node* temp = Graph->array[b].head;
        // Case 1
        // The first element is greater than this element, than replace the head
        if(temp->data > a)
        {
            X->next = temp;
            Graph->array[b].head = temp;
        }

        // Traverse the complete list to find the position where it can be inserted
        else
        {
            // A new varible so that we can traverse the complete list which must be equal to head at initial
            struct node* test = temp;

            // Now traverse the complete list until you found the appropriate position

            // The element to be added is in the second position
            if(test->data < a && test->next == NULL)
            {
                test->next = X;
                X->next = NULL;
            }

            // The element to be added is not in the first two
            while(test->next != NULL)
            {
                if(test->data < a && test->next->data >a)
                {
                    //Input the element in the middle of both of them
                    X->next = test->next->next;
                    test->next = X;
                }
                test = test->next;
            }

            // The element to be inserted is in the last
            if(test->data < a && test->next == NULL)
            {
                test->next = X;
                X->next = NULL;
            }
        }
    }
}

// Function to print the graph
void print_graph ( struct graph* Graph)
{
    for( int i = 0 ; i < Graph->num_vertex; i++)
    {
        struct node* temp = Graph->array[i].head;
        printf("%d ", i);
        while(temp)
        {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
/*==========---- Graph Implementation ended -----------=============*/


/*===========---- BFS algorithm implementation ---------===========*/

void BFS( struct graph* Graph, int key)
{
    struct queue* New = create_queue();
    // Making the head node as visited
    Graph->array[key].head->state = visited;

    // Enqueueing the current vertex in the queue
    enqueue(New, key);

    while(!isEmpty(New))
    {
        // Removing the curr vertex from the queue and also printing it out
        int curr = dequeue(New);
        printf("%d ",curr );

        // Temp node store the head pointer of the current adjacency matrix element
        struct node* temp = Graph->array[key].head;

        while(temp)
        {
            // To store the value of the current vertex
            int vertex = temp->data;

            // If the node is unvisited then only go inside the loop
            if (temp->state == notvisited)
            {
                // Mark the node as visited
                temp->state = visited;
                // Enqueue the current element into the queue

                /* Note that, as of now we are not enqueuing the element according to the sorted order. */
                enqueue( New ,temp->data);
            }

            // Making the temp pointer to point to next element in the list
            temp = temp->next;
        }
    }

    return;
}

/*===========---- BFS algorithm implementation Ended ------========*/
int main(){
  char choice;
  int numberOfVertices, startVertex, endVertex;

  // Fetching number of vertices
  scanf("%d",&numberOfVertices);
  // Create your adjacency list's array of head vertices here.
    struct graph* New = createGraph(numberOfVertices);

  while(scanf(" %c",&choice)!=-1){
     if(choice == 'N'){
       char delimiter;
       scanf("%d", &startVertex);
       while(scanf("%d%c", &endVertex, &delimiter)){

	 // Add the edge (startVertex, endVertex) to your graph here.
       new_edge(New, endVertex,startVertex);
	 if(delimiter == '\n') break; // Detecting end of line.
       }
     }
     else if(choice == 'B'){
       scanf("%d",&startVertex);
       // Call BFS on your graph starting from startVertex here.
       BFS(New, startVertex);
     }
   }
   return(0);
}
