#include <stdio.h>
#include <stdlib.h>

#define visited 1
#define notvisited 0

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

/* Queue Implementation */
    typedef struct queue_node
    {
        int key;
        struct queue_node* next;
        struct queue_node* prev;
    } queue_node;

    struct Queue
    {
        struct queue_node *front, *end;
    } Queue;

    struct queue_node* Newnode(int key)
    {
        struct queue_node* temp = (struct queue_node*)malloc(sizeof(struct queue_node));
        temp->key = key;
        temp->prev = NULL;
        temp->next = NULL;
        return temp;
    }
    struct Queue* createQueue()
    {
        struct Queue* new_queue = (struct Queue*)malloc(sizeof(struct Queue));
        new_queue->front = NULL;
        new_queue->end = NULL;
        return new_queue;
    }

    void enQueue(struct Queue* q, int k )
    {
        struct queue_node*  temp = Newnode(k);

        if(q->front == NULL)
        {
            q->front = q->end = temp;
            return;
        }

        q->end->next = temp;
        temp->prev = q->end;
        q->end = temp;
        return;
    }

    void delete_queue(struct Queue* q)
    {
        if(q->front == NULL)
            return;

        struct queue_node* temp = q->front;
        q->front = q->front->next;
        q->front->prev = NULL;

        if(q->front == NULL)
            q->end = NULL;

        free(temp);
    }
/* Queue list implementation ended */

int main()
{
    struct graph* New = create_graph(4);
    new_edge(New, 0, 1);
    new_edge(New, 0, 2 );
    new_edge(New, 0, 3);
    new_edge(New, 1 , 2);

    print(New);

    DFS(New, 2);
    return 0;
}

