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
    struct node* X = new_node(a);
    struct node* Y = new_node(b);

    // If both the input are same
    if( a == b)
    {
        // If it was not present previously
        if(Graph->array[a].head == NULL)
        {
            Graph->array[a].head = X;
            return;
        }
    }

    // If the there is no element in adjacency list of a

    if( Graph->array[a].head == NULL)
    {
        // Adding the element to the adjacency list
        Graph->array[a].head = X;
    }
    else
    {
        // Inputing the value in the adjacency list of a

        struct node* temp = Graph->array[a].head;

        // If the data to be added is greater than the first element
        if(temp->data > b)
        {
            Y->next = temp;
            Graph->array[a].head = temp;
        }

        // Traverse the complete list to find the position where it can be inserted
        else
        {
            struct node* test = temp;

            while(temp != NULL)
            {
                if(temp->data < b)
                {
                    test = temp;
                }

                else
                {
                    Y->next = test->next;
                    break;
                }

                temp = temp->next;
            }

            test->next = Y;
        }
    }



    // If the there is no element in adjacency list of b
    if( Graph->array[b].head == NULL)
    {
        // Adding the element to the adjacency list
        Graph->array[b].head = Y;
    }

    else
    {
        // Inputing the value in the adjacency list of b
        struct node* alpha = Graph->array[b].head;

        // If the data to be added is greater than the first element
        if( alpha->data > a)
        {
            X->next = alpha;
            Graph->array[b].head = X;
        }
        // Traverse the list and find the position where it can be inserted
        else
        {
            struct node* beta = Graph->array[b].head;

            while( alpha != NULL)
            {

                if(alpha->data < a)
                {
                    beta = alpha;
                }

                else
                {
                    X->next = beta->next;
                }

                beta = beta->next;
            }

            beta->next = X;
        }
    }

}

// Function to print the graph
void print_graph ( struct graph* Graph)
{
    for( int i = 0 ; i < Graph->num_vertex; i++)
    {
        struct node* temp = Graph->array[i].head;
        printf("Adjacency list of the vertex %d ", i);
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
