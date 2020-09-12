#include<stdio.h>
#include<limits.h>

// Vibhanshu Jain
// CS19B1027


//The function to print the values stored in the array
void print(int* a, int n)
{
    for(int i=0; i<n; i++){
        printf("%d   ", a[i]);
    }
    printf("\n");
    return;
}

//Function to arrange the elements at correct position
void function_1(int* a, int n)

{
    int    odd_index = 1, even_index = 0;                                                           //storing the values of the current index in two variables
    while(even_index<n && odd_index<n)                                                              //Running the loop till end of the array
    {
        while(even_index < n && a[even_index]%2 == 0)                                               //The loop will run until it finds one even element at incorrect position and store its index in even_index
            even_index += 2;
        while(odd_index < n && a[odd_index]%2 == 1)                                                 //The loop will run until it finds one odd element at incorrect position and store its index in odd_index
            odd_index += 2;
        if( even_index <n && odd_index < n)
            { int temp = a[even_index]; a[even_index] = a[ odd_index]; a[odd_index] = temp;}        //Swapping the values stored in even_index and odd_index
        else
            break;
    }
    return;
}

//Function to sort all the even elements
//This is based on the principal of Insertion Sort
void function_3(int* a, int n)
{
    for(int i = 0; i < n; i = i+2)                                                  // We are increasing the index by 2 each as we have even numbers at alternate positions only
    {
        int value = a[i];
        int hole = i;
        while(hole > 0 && a[hole-2] <= value)                                      //  We are decreasing the hole by 2 each as we have even numbers at alternate positions only
        {
            a[hole] = a[hole-2];
            hole = hole-2;
        }
        a[hole] = value;
    }
}

//Function to sort all the odd elements
//This is based on the principal of Insertion Sort
void function_4(int* a, int n)
{
    for(int i = 1; i < n; i = i+2)                                                   // We are increasing the index by 2 each as we have odd numbers at alternate positions only
    {
        int value = a[i];
        int hole = i;
        while(hole > 1 && a[hole-2] >= value)                                        // We are decreasing the hole by 2 each as we have odd numbers at alternate positions only
        {
            a[hole] = a[hole-2];
            hole = hole-2;
        }
        a[hole] = value;
    }
}

int main(){
    printf("The number of intergers which you wants to add:    ");
    int n;
    scanf("%d",&n);
    int a[n];
    printf("Enter the numbers: ");
    for(int i=0; i<n ; i++){
        scanf("%d", &a[i]);
    }
    printf("The number which you give: ");
    print(a,n);

    printf("The number after keeping all the values at correct position, according to the problem statement 1 & 2 : ");
    function_1(a,n);
    print(a,n);

    printf("The array after problem statement 3: ");
    function_3(a,n);
    print(a,n);

    printf("The array after problem statement 4: ");
    function_4(a,n);
    print(a,n);

    return 0;

}
