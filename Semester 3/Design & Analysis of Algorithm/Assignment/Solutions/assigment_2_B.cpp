#include <stdio.h>

void maxpath(int m, int n, int A[][])
{
    int temp[m][n];
    int result[m+n-1];
    int track = 0; result[track] = A[1][1];
    temp[1][1] = A[1][1];

    while(m>0 && n>0 )
    {
        if(temp[m][n-1] > temp[m-1][n])
        {
            temp[m][n] = A[m][n-1] + A[m][n];
            m++, n++;
            result[track] = A[m][n];
            track++;
        }
        else
        {
            temp[m][n] = A[m-1][n] + A[m][n];
            m++;n++;
            result[track] = A[m][n];
            track++;
        }
    }

    printf("The maximum sum possible is %d, the path choosen is \n",temp[m][n]);
    for(int i = 0; i<m+n-2; i++)
    {
        printf("%d  ",result[i]);
    }
}
int main()
{
    int m,n;
    printf("Please input the size of the array\n");
    scanf("%d",&m);
    scanf("%d",&n);
    int A[m][n];
    printf("Please input the array\n");
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d", &A[m][n]);
        }
    }

    printf("Hello World");
    maxpath(m,n,A[m][n]);

    return 0;
}
