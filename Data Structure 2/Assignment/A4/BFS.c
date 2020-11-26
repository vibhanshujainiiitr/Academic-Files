#include <stdio.h>
#include <stdlib.h>

#define visited 1
#define notvisited 0



/* Queue Implementation */

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

void dequeue(struct queue* Queue)
{
    if(Queue->front == NULL)
        return;

    struct Q_node* temp = Queue->front;

    Queue->front = Queue->front->next;

    if(Queue->front == NULL)
        Queue->rear = NULL;
    else
        Queue->front->prev = NULL;

    free(temp);
    return;
}

int isEmpty(struct queue* Queue)
{
    return(Queue->front == Queue->rear);
}


/* Queue list implementation ended */



/* Implementing the graph data structure using adjacency list */

// The node to store the values
    struct node
    {
        int vertex;
        struct node* next;
    };
    // Creating a new node by allocating memory using malloc
    struct node* createnode (int k )
    {
        struct node* temp = (struct node*)malloc(sizeof( struct node));
        temp->vertex = k;
        temp->next = NULL;
        return temp;
    }
    // The graph data type
    struct graph
    {
        int num_vertex;
        struct node** adj_list;
        int* state;
    };

    // Creating a graph
    struct graph* create_graph( int vertices )
    {
        struct graph* new_graph = (struct graph*)malloc(sizeof(struct graph));
        //struct graph* new_graph = malloc(sizeof(struct graph));
        new_graph->num_vertex = vertices;
        new_graph->adj_list = malloc(vertices * sizeof(struct node*));

        // Storing a new integer to store wether is visited or not
        new_graph->state = malloc(vertices * sizeof(int));



        for( int i=0; i<vertices; i++)
        {
            new_graph->adj_list[i] = NULL;
        }

        return new_graph;
    }
    // Adding a new edge
    void new_edge(struct graph* graph, int k, int i )
    {
        // Adding a edge from k -> i ;
        struct node* temp = createnode(i);
        temp->next = graph->adj_list[k];
        graph->adj_list[k] = temp;
        // Adding edge from i->k
        // This part is being removed

        struct node* test = createnode(k);
        test->next = graph->adj_list[i];
        graph->adj_list[i] = test;
    }


    // Printing the graph
    void print(struct graph* graph)
    {
        for( int i = 0; i < graph->num_vertex; i++)
        {
            struct node* temp = graph->adj_list[i];
            printf("\n Vertex %d\n", i);
            while(temp)
            {
                printf("%d-> ", temp->vertex);
                temp = temp->next;
            }
        }
        printf("\n");
    }
/* Graph Data Structure implementation ended */


/* DFS Algorithm starts */

void DFS( struct graph* G, int key )
{
    struct node* AdjList = G->adj_list[key];
    struct node* temp = AdjList;

    G->state[key] = visited;
    printf("Visited %d \n", key);

    while(temp != NULL)
    {
        int count = temp->vertex;

        if(G->state[count] == notvisited )
            DFS(G, count);

        temp = temp->next;
    }
}


/* BFS Algorithm Starts */
void BFS (struct graph* Graph, int key )
{
    struct queue* Queue = create_queue();

    Graph->state[key] = visited;
    enqueue(Queue,key);

    while(!isEmpty(Queue))
    {
        int curr = Queue->front;
        dequeue(Queue);

        printf("Visited Vertex : %d", curr);

        struct node* temp = Graph->adj_list[curr];

        while(temp)
        {
            int vertex = temp->vertex;

            if(Graph->state[vertex] == 0)
            {
                Graph->state[vertex] = visited;
                enqueue(Queue,vertex);
            }

            temp = temp->next;
        }
    }
}

/* BFS Ended */


int main()
{
    struct graph* New = create_graph(4);
    new_edge(New, 0, 1);
    new_edge(New, 0, 2 );
    new_edge(New, 0, 3);
    new_edge(New, 1 , 2);

    print(New);

    BFS(New, 2);

    printf("\n\n");

    DFS(New, 2);
    return 0;
}

