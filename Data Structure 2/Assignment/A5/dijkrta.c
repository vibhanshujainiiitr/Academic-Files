/*
Assignment 5
Roll Number: CS19B1027
Name: Vibhanshu Jain
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int weight;
    // To store the weight


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



/* ========---- The min heap -----===============*/
struct heap{
};
struct heap* createHeap(int size);
// Creating a new heap
void insertHeap(int vertex, int weight , struct heap* temp);
// Inserting into the heap
int isEmptyHeap(struct heap* temp);
// To check wether the heap is empty or not
int peekMinimum(struct heap* temp);
/*===========----- Dijkstaras Algorithm ------===================*/
int popMinimum (struct heap* temp);
// We will min heaps in the implementation
int isPresent(int vertex, struct heap* temp);
// Will return true if the vertex is already present in the heap

void dijkrata( int start, int end, struct *graph Gph)
{
    // Checking whether the inputed endpoints are correct or not.
    if(start < 0 || start > Gph->num_vertex)
        return;
    if(end < 0 || end  > Gph->num_vertex )
        return;

    // Total number of verticess
    int  n = Gph->num_vertex;

    // Creating the heap of size of vertiecs
    struct heap alpha = createheap(n);

    // Insert the first vertex
    insertHeap(start , 0);

    // The array to store the minimun distance distance
    // The array to store wether it's visited or not :visit
    // The array to store the path : prevoius
    int distance[n], visit[n], previous[n];

    for( int i = 0; i < n; i++)
    {
        visit[i] = notvisited ;
        distance[i] = INT_MAX;
        previous[i] = -1;
    }

    // The distance of first element is 0
    distance[start] = 0;

    while( !isEmptyHeap())
    {
        // Run this while loop until the heaps is empty

        int nodeID = peekMinimum(alpha);
        visit[nodeID] = 1;
        // Marking the node as visited

        int minValue = popMinimum(alpha);


        if(minValue > distance[nodeID])
            continue;
        // The distance already founded is minimum , then we don't needed to go inside the loop

        struct node* temp = Gph->array[nodeID];
        while( temp->next != NULL)
        {
            // If the node is already visited then continue the loop without going into the loop;
            if(visit[nodeID])
                continue;

            // The new weight
            int newWeight = distance[nodeID] + temp->weight;

            if( newWeight < distance[temp->next->data])
            {
                previous[temp->next->data] = nodeID;
                // Storing to print the path
                distance[temp->next->data] = newWeight;
                // Changing the weight

                if(!isPresent(temp->next->data), alpha)
                    insertHeap(temp->next->data, newWeight, alpha );
                // Adding the vertex to the heap if it's not present here

                else
                    decreaseHeap(temp->next->data, newWeight, alpha);

                // If the vertex is not present previously in the heap
            }

            // Checking for the next node in the adj list
            temp = temp->next;

        }


        // The condition to breake the loop once we find the path between the two vertices
        if( nodeID == end )
        {
            // Printing the minimun distance
            printf("%d", distance[end]);

            // Printing the path
            for( int count = end ; count >= 0 ; count --)
            {
                printf("%d ", previous[count]);
            }
            return;
        }
    }

    // The node is not reachable
    return -1;
}


/*=========----- The min heap implementation started ---============*/
struct heap{
    int size;
    // To store the total number of elements in the heap
    int* value[];
    // To store the values
    int* positionMap[];
    // The position map of the elements
    int* inverseMap[];
    // The inverse map of the elements
};

struct heap* createHeap(int size)
{
    struct heap* Heap = (struct heap*)malloc(sizeof(struct heap));
    Heap->value = (int)malloc(sizeof(int)*size);
    Heap->positionMap = (int)malloc(sizeof(int)*size);
    Heap->inverseMap = (int)malloc(sizeof(int)*size);
    Heap->size = size;
    return Heap;
}

void insertHeap(int vertex, int weight, struct heap* temp)
{
    temp->value[vertex] = weight;
    temp->positionMap[vertex] = temp->size;
    temp->inverseMap[temp->size] = vertex;

    swim(temp->size, temp);

    temp->size++;
    return;
}

void swim(int i, struct heap* temp)
{
    int p = (i-1)/2;
    while(i>0 && less(i,p))
    {
        swap(i,p, temp);
        i = p;
        p = (i-1)/2;
    }
}

void swap( int i, int j, struct heap* temp )
{
    temp->positionMap[temp->inverseMap[j]] = i;
    temp->positionMap[temp->inverseMap[i]] = j;

    int key = temp->inverseMap[i];
    temp->inverseMap[i] = temp->inverseMap[j];
    temp->inverseMap[j] = key;
}

void less(int i , int j , struct heap* temp)
{
    return temp->value[temp->inverseMap[i]] < temp->value[temp->inverseMap[j]];
}

void removeHeap( int vertex, struct heap* temp)
{
    int i = temp->positionMap[vertex];
    temp->size =  temp->size - 1;

    swap(i, temp->size, temp);
    sink(i, temp);
    swim(i, temp);

    temp->value[vertex] = NULL;
    temp->positionMap[vertex] = -1;
    temp->inverseMap[temp->size] = -1;
}

void sink(int i , struct heap* temp)
{
    while(true)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;

        int smallest = left;

        if( right < temp->size && less(right, left, temp))
            smallest = right;

        if(left >= temp->size || less(i, smallest, temp))
            break;

        swap(smallest, i , temp);
        i = smallest;
    }
}

void updateHeap(int vertex, int value, struct heap* temp)
{
    int i = temp->positionMap[vertex];
    temp->value[vertex] = value;

    sink(i, temp);
    swim(i, temp);
}

void decreaseKey(int vertex, int value, struct heap* temp)
{
    if(less(value, temp->value[vertex]))
    {
        temp->value[vertex] = value;
        swim(temp->positionMap[vertex], temp);
    }
}

void increaseKey(int vertex, int value, struct heap* temp)
{
    if(less(temp->value[vertex], value))
    {
        temp->value[vertex] = value;
        sink(temp->positionMap[vertex], temp);
    }
}

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
