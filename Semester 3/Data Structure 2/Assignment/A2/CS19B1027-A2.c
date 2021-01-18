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


void delete_bst(node* root )
{
    if(root == NULL)
        return;
    delete_bst(root->right);
    delete_bst(root->left);
    free(root);
}


node* search_location ( node* root, char key[7])
{
    if(root == NULL)
        return NULL;
    if(compare_plate(root->data, key) == -1)
        return root;
    if(compare_plate( key, root->data))
       return search_location( root->left, key);
    return search_location( root->right, key );
}


node* minvalue_successor( node* node)
{
    struct node* current = node;
    while( current->left != NULL)
        current = current->left;
    return current;
}


node* minvalue_predecessor( node* node)
{
    struct node* current = node;
    while( current->right != NULL)
        current = current->right;
    return current;
}


node* succ_node_not_in_tree(node* root, char key[7])
{
    if(compare_plate(root->left,key))
        return(succ_node_not_in_tree(root->left,key));

    else if(compare_plate(key, root->left) && compare_plate(root->right, key))
        return(root->right);

    else
        return(succ_node_not_in_tree(root->right, key));
}


node* successor(node* root, char key[7])
{
    node* temp = search_location(root, key);
    if( temp == NULL)
        return succ_node_not_in_tree(root, key);
    if(temp->right != NULL)
        return minvalue_successor(temp->right);
    while( temp->parent != NULL)
    {
        if (compare_plate(temp->data, key) == 0)
            break;
        temp = temp->parent;
    }
    return temp;
}


node* pred_node_not_in_tree(node* root, char key[7])
{
    if(root->left == NULL && root->right == NULL)
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
}


node* predecessor(node* root, char key[7])
{
    node* temp = search_location(root, key);
    if( temp == NULL)
        return pred_node_not_in_tree(root, key);
    if(temp->left != NULL)
        return minvalue_predecessor(temp->left);
    while(temp->parent != NULL)
    {
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
