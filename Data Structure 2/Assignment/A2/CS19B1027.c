/* Assignment 2
   Roll No. CS19B1027
   Name: Vibhanshu Jain
*/   

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

 
typedef struct node
{
    char data[7];
    struct node* left;
    struct node* right;
    struct node* parent;
} node ;


node *head = NULL;
node *temproary = NULL;

node* newnode( char data[7] )
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    strcpy(temp->data, data);
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    return temp;
}


/* Comparision function to compare two number plate, it will return 1 if the A < B, 0 if A>B and -1 if both the strings are same for the given strings A and B */
int compare_plate(char Plate_1[7], char Plate_2[7] )
{
    for( int i=0; i<=7; i++ )
    {
        if(Plate_1[i] > Plate_2[i])
            return 0;
        if(Plate_1[i] < Plate_2[i])
            return 1;
    }
    return -1;
}


struct node* insert (node *node, char key[7] )
{
    if(node==NULL)
        return newnode(key);
    if(compare_plate( key, node->data))
    {
        struct node *test;
        test = insert(node->left, key);
        node->left = test;
        test->parent = node;
    }
    else if(!compare_plate( key, node->data))
    {
        struct node *test;
        test = insert(node->right, key);
        node->right = test;
        test->parent = node;
    }
    return node;
}

/* function to search a given plate in the BST */
int search( node* root, char key[7])
{
    int count = 0;
    if(root == NULL)
        return count;
    if(compare_plate(root->data, key) == -1)
    {   
        count = 1;
        return count;
    }
    if(compare_plate( key, root->data))
        return search( root->left, key);
    return search( root->right, key );
}

/* function to print the path taken to find the corresponding number plate */
void search_path( node* root, char key[7])
{   
    if( search(head, key)==0)
        return;
    if(root == NULL)
        return;   
    if(compare_plate(root->data, key) == -1)
        return;
    if(compare_plate( key, root->data))
    {
        printf("L");
        return search_path( root->left, key);
    }
    else
    {
        printf("R");
        return search_path( root->right, key );
    }
}

/* function to delete the complete BST */
void delete_bst(node* root )
{
    if(root == NULL)
        return;
    delete_bst(root->right);
    delete_bst(root->left);
    free(root);
}

/* To search the location or effectively the pointer the node in the given binary tree */
node* search_location ( node* root, char key[7])
{
    if(root == NULL)
        return NULL;
    /* The variable to store the address of this location if the key given is not in the BST so that we can find the successor and predecessor*/     
    temproary = root;
    
    if(compare_plate(root->data, key) == -1)
    {
        return root;
    }
    if(compare_plate( key, root->data))                         
    {  
        return search_location( root->left, key);
    }    
    temproary = root;
    return search_location( root->right, key );
}

/*  function to find the minimum value in the case of finding the successor, for case in which the right child exists */
node* minvalue_successor( node* node)
{
    struct node* current = node;
    while( current->left != NULL)
        current = current->left;                // traversing in the left half
    return current;
}

/*  function to find the maximum value in the case of finding the predecessor, for case in which the right child exists */
node* minvalue_predecessor( node* node)
{
    struct node* current = node;
    while( current->right != NULL)
        current = current->right;               //traversing in the right half
    return current;
}


node* succ_node_not_in_tree(node* root, char key[7])
{   
    return temproary;
/*    if(compare_plate(root->left,key))
        return(succ_node_not_in_tree(root->left,key));
    
    else if(compare_plate(key, root->left) && compare_plate(root->right, key))
        return(root->right);
    
    else
        return(succ_node_not_in_tree(root->right, key));
*/
}


node* successor(node* root, char key[7])
{
    node* temp = search_location(root, key);
    if( temp == NULL)
        return succ_node_not_in_tree(root, key);        // If the plate given doesn't exists in the BST
    if(temp->right != NULL)
        return minvalue_successor(temp->right);         // If it has a right child then the predecessor will be the minimun element in the right subtree
    while( temp->parent != NULL)        
    {                                                   // If it is not present in the subtree then we are searching in the parents
        if (compare_plate(temp->data, key) == 0)
            break;                                  
        temp = temp->parent;
    }
    return temp;
}


node* pred_node_not_in_tree(node* root, char key[7])
{   
    return temproary->parent;
    // Returning the parent of the temproary node
/*    if(root->left == NULL && root->right == NULL)
        return root;
    
    if(root->left == NULL)
        return pred_node_not_in_tree(root->right, key);
    if(root->right == NULL)
        return pred_node_not_in_tree(root->left, key);
        
    if(compare_plate(root->left, key))
        return pred_node_not_in_tree(root->left, key);
    else if(compare_plate(key, root->left) && compare_plate(root->right, key))
        return(root->left);
    else
        return pred_node_not_in_tree(root->right,key);
*/
}

/* Function to find the predecessor in the BST */
node* predecessor(node* root, char key[7])
{
    node* temp = search_location(root, key);
    if( temp == NULL)
        return pred_node_not_in_tree(root, key);            // If the plate given doesn't exists in the BST
    if(temp->left != NULL)
        return minvalue_predecessor(temp->left);            // If it has a left child then the predecessor will be the maximum element in the left subtree
    while(temp->parent != NULL)
    {                                                       // If it is not present in the subtree then we are searching in the parents 
        if (compare_plate(temp->data, key) == 1)
            break;
        temp = temp->parent;
    }
    return temp;
}


int main()
{
    char choice, numberPlate[7];
    _Bool requests = 0;
    while(scanf("%s",numberPlate)!=-1)
    {
        if(!requests)
        {
            if(strlen(numberPlate) == 1)
            { 
                choice = numberPlate[0];
                requests = 1;
            }
            else
                head = insert(head, numberPlate);
        }
        else
            break;
    }
    do
    {
        if (choice == 'S')
        {
            printf("%d ",search(head, numberPlate));
            search_path(head,numberPlate);
            printf("\n");
        }
        else if (choice == '<')
        {
            node* node = predecessor(head, numberPlate);
            if(node == NULL || compare_plate(node->data, numberPlate) != 1)
                printf("0\n");
            else
                printf("%s\n", predecessor(head,numberPlate)->data);
        }
        else if(choice == '>')
        {
            node* node = successor(head, numberPlate);
            if(node == NULL || compare_plate(node->data, numberPlate) != 0)
                printf("0\n");
            else
                printf("%s\n",successor(head, numberPlate)->data);
        }
    }   while(scanf("%*[\n]%c %6s",&choice, numberPlate)!=-1);
    delete_bst(head);
    return(0);
}