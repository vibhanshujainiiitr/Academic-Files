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
    for ( int i=0; i<n; i++)
    {
        if( i%2 == 0 && a[i]%2 !=0 )
        {
            for( int j = i+1; i<n ; i++)
            {
                if( j%2 != 0 && a[j]%2 == 0)
                {
                    int temp = a[i]; a[i] = a[j]; a[j] = temp;
                }
		else
		    break;
            }
	 break;
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
