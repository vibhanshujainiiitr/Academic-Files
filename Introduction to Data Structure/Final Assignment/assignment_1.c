#include<stdio.h>
#include<limits.h>

void print(int* a, int n)
{
    for(int i=0; i<n; i++){
        printf("%d   ", a[i]);
    }
    printf("\n");
    return;
}

void swap(int* a, int* b)
{
    int* temp = a;
    a = b ;
    b = temp;
    return;
}

void function_1(int* a, int n)
{   int odd_index = -1, even_index = -1;
    for ( int i=0; i<n; i++)
    {
        if( i%2 == 0 && a[i]%2 !=0 )
        {
            odd_index = i;
        }

        if( i%2 != 0 && a[i]%2 == 0)
        {
            even_index = i;
        }

        if ( odd_index != -1 && even_index != -1)
        {
//            swap(&a[odd_index],&a[even_index]);

            int temp = a[odd_index]; a[odd_index] = a[even_index]; a[even_index] = temp;
            odd_index = -1; even_index = -1;
        }
    }
    return;
}

int main(){
    printf("The number of intergers which you wants to add.\n");
    int n;
    scanf("%d",&n);
    int a[n];

    for(int i=0; i<n ; i++){
        scanf("%d", &a[i]);
    }

    print(a,n);
    function_1(a,n);
    print(a,n);
    return 0;

}
