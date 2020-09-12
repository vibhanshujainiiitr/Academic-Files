#include "list-types.h"
#include <stdio.h>
#include <stdlib.h>

/* Returns number of elements in the list, given pointer to head  */
int size(node* head) {
  int count=0;
  node* current = head;
  while(current!=NULL){
    count++;
    current = current->next;
  }
  return count;
}

/* Prints list data elements in order, separated by a single space */
void print_list(node* head) {
  node* curr = head;
  while(curr!=NULL) {
    printf("%d ",curr->data);
    curr=curr->next;
  }
  printf("\n");
}

/* Returns 1 if list is empty, 0 if not */
int is_empty(node* head) {
  if(head==NULL)
    return 1;
  else return 0;
}


/* Returns pointer to the last element in the list */
node* get_last(node* head){
  node* curr=head;
  if(curr==NULL) { //if empty list
    return NULL;
  }

  while(curr->next!=NULL) {
    curr= curr->next;
  }
  return curr;
}

/* Inserts a node with given value into the list before head.
Returns pointer to new head (which is the node inserted) */
node* insert_at_start(node* head, int value){
    node* new_node = (node*) malloc(sizeof(node));
    new_node->data = value;
    new_node->next = head;
    return new_node; // return pointer to newly inserted node.
}

/* Implement the other functions specified in list-interface below this line  */
node* search_list(node* head, int key){
    node* curr = head;                                      // Intialising the current pointer to head
    while( curr != NULL){                                   //Checking whether the curr is pointing to NULL, or the list is ended
        if( curr->data == key ){                          //Checking that value is their or not
            //Do the thing which you want to
            printf("Yes the node is present");
            return curr;
        }
        else {
        curr = curr->next;                                  //curr will be pointed to the next node
        }
      if(curr==NULL)
         { printf("Not found");
           return NULL;
         }
    }
}

/* insert a new node with data key to be at position place_num in the list .
If place_num is larger than listlength +1, print "Error" and return NULL
Else, return pointer to the newly inserted node.
 */
node* insert_kth(node* head, int key, int place_num){
    node* curr = head;
    int count = 0;                                                  // Initialise count to zero
    while(curr->next!= NULL){
        if( count == place_num-1 ){
            node* temp = curr->next;                                // Storing the pointer to next node in temp
            node* new_node = (node*) malloc(sizeof(node));          // Creating a new node new_node
            new_node->data = key;
            new_node->next = temp;                                  //Adding the pinter of next node in the newly formed node new_node
            curr->next = new_node;
            return new_node;                                  //Adding the pointer of new node to current node
            }
        count++;
        curr = curr->next;
        }

        if(place_num+1 > count)
            return NULL;                                            // Returning the new node pointer
}


/* Delete the node pointed to by position.
Return the NEXT node in the list (NULL if position is the last node)
*/
node* delete_node(node* head, node* position){
    node* curr= head;
    while(curr->next != NULL){
        if( curr->next == position)
             {  node* temp = curr->next;                            //Storing the loaction of node to be deleted in temp
                curr->next = curr->next->next;                      //Giving the location of the second node after the one to be deleted to the current one.
                free(temp);                                         //Removing the data in temp
                temp = NULL;
                return curr->next;                                        //temp as well the position is setted to be null for more usage
             }
         else
            curr = curr->next;
         if(curr->next== NULL)
            { return NULL;
            }
        }
    }


    /* Delete entire list */
void delete_list(node* head)
{   node* curr = head;
    node* temp;
    while(curr->next != NULL)
    {
        temp = curr->next;                      // Saving the pointer to next oin temp
        free(curr);                             // Free the curr node
        curr = temp;                            // Setting the current node to next node
    }

    head = NULL;                                //Making the head NULL
    temp = NULL;                                //Making the temp also NULL
}

/* Print the elements in the list in reverse order */
void print_reverse_order(node* head)
{
    if (head == NULL)
       return;

    print_reverse_order(head->next);               // Print the list after head node

    printf("%d  ", head->data);                    // After everything else is printed, print head


}

/* Rotate the list by a number k. E.g. list = 1,2,3,4,5. rotate_list(2) will make
the new list (4,5,1,2,3). Returns pointer to new head of list.
  */
void rotate_list(node* head, int k)
{
    if(k==0)
        return;                                             // k = 0 means no change so return same

    node* current = head;

    int count = 0;                                          //initiallizing count to 0
    while ( count < k && current != NULL)
    {
        current = current->next;
        count ++;
    }

    if (current==NULL)                                      //This means that the value of k is greater is than the total number  of list and we won't be doing anything at present
        return;


    node* k_node = current;                                  //Storing the details of kth node in k_node

    while( current->next != NULL)
    {
        current = current->next;                            //Now the current value is the last value of the list
    }

    current->next = head;                                   //The address of next node is changed to the head of the list
    head =  k_node->next;
    k_node->next = NULL;
}

