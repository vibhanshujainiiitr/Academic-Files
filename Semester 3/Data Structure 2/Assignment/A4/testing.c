#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node* next;
};

struct queue 
{
	struct node* head;
	struct node* tail;
};

struct node* createnode(int v)
{
	struct node* temp = (struct node *)malloc(sizeof(struct node));
	temp->next = NULL;
	temp->data = v;
	return temp;
}

struct queue* queue()
{
	struct queue* Queue = (struct queue*)malloc(sizeof(struct queue));
	Queue->head = NULL;
	Queue->tail = NULL;
	
	return Queue;
}

void enqueue(struct queue* q,int value)
{
	struct node* temp = createnode(value);
	if(q->head == NULL && q->tail == NULL)
	{
		q->head = q->tail = temp;
	}
	else
	{
		q->tail->next = temp;
		q->tail = temp;
	}
}

int dequeue(struct queue* q)
{
	int val = q->head->data;
	struct node* del = q->head;
	if(del == NULL )
     return -1;
    else if (q->head == q->tail)
     {
		q->head = q->tail = NULL;
    	return val;
	 }
    else
    {
    	q->head = q->head->next;
    	return val;
	}
	free(del);
}

void BFS(struct node** A,int v,int n)
{
	struct queue* Q = queue();
	int V[n],P[n],i,u;
	for(i=0;i<n;i++)
		{
			V[i] = -1;
			P[i] = -1;
		}
	V[v] = 0;
	enqueue(Q,v);
	while(Q->head != NULL )
	{
		u = dequeue(Q);
		printf("%d ",u);
		if(A[u] == NULL)
			break;
		else
		 {
		 	struct node* t = A[u];
		 	while(t != NULL)
		 	{
		 		if(V[t->data] == -1)
		 		{
		 			V[t->data] = V[u]+1;
		 			P[t->data] = u ;
		 			enqueue(Q,t->data);
				 }
				t = t->next;
			 }
		 }
	}

	printf("\n");
}

void addEdge(struct node** A,int u,int v)
{
   struct node* temp = createnode(v);
   struct node* temp1 = createnode(u);
   if(u == v)
   {
   	 if(A[v] == NULL)
   	 {
   	 
   	 	A[v] = temp;
		}
	 
   	  return ;
   }
   
   	if( A[u] == NULL)
	   	 A[u] = temp;
	else
	 {
	 	struct node* t = A[u];
	 	if(t->data > v)
	 	{
	 		temp->next = t;
			 A[u] = temp; 
		 }
		else 
		{  
		   struct node* prev = t;
			 while(t != NULL)
			 {
			 	
			 	if(t->data < v)
			 	 prev = t;
			 	else 
			 	{
			 		temp->next = prev->next;
			 		break;
				 }
				t= t->next;
			 }
	   prev->next = temp;
        
		}
	 }	
	 if( A[v] == NULL)
	   A[v] = temp1;
	else
	 {
	 	
	    struct node* t1 = A[v];
	 	if(t1->data > u)
	 	{
	 		temp1->next = t1;
			 A[v] = temp1; 
		 }
		else {
			 struct node* pre = t1;
			 while(t1 != NULL)
			 {
			 	
			 	if(t1->data < u)
			 	 pre = t1;
			 	else 
			 	{
			 		temp1->next = pre->next;
			 		break;
				 }
				t1= t1->next;
			 }
	   pre->next = temp1;
	  
		}
	 }		
}

int main(){
  char choice;
  int numberOfVertices, startVertex, endVertex,i;
  
  // Fetching number of vertices
  scanf("%d",&numberOfVertices);
  // Create your adjacency list's array of head vertices here.
  struct node *A[numberOfVertices];
  for(i=0;i<numberOfVertices;i++)
	 A[i] = NULL;
	 	
  while(scanf(" %c",&choice)!=-1){
     if(choice == 'N'){
       char delimiter;
       scanf("%d", &startVertex);     
       while(scanf("%d%c", &endVertex, &delimiter)){
			
			
	 // Add the edge (startVertex, endVertex) to your graph here.
	     addEdge(A,startVertex,endVertex);  
	 if(delimiter == '\n') 
	   break; // Detecting end of line.
       
     }
 }
     else if(choice == 'B'){
       scanf("%d",&startVertex);
       
       // Call BFS on your graph starting from startVertex here.
       BFS(A,startVertex,numberOfVertices);
     }
   }
   return(0);  
}
