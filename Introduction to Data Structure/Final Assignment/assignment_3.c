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

void function_1(int* a, int n)

{
    int    odd_index = 1, even_index = 0;
    while(1)
    {
        while(even_index < n && a[even_index]%2 == 0)
            even_index += 2;
        while(odd_index < n && a[odd_index]%2 == 1)
            odd_index += 2;
        if( even_index <n && odd_index < n)
            { int temp = a[even_index]; a[even_index] = a[ odd_index]; a[odd_index] = temp;}
        else
            break;
    }
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
