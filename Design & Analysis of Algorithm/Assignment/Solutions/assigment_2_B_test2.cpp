#include <stdio.h>

void maxpath(int m, int n, int A[][])
{
    int temp[m][n];
    int result[m+n-1];
    int track = 0; result[track] = A[1][1];
    temp[1][1] = A[1][1];

    for(int i =0; i<n; i++)
    {   for(int j=0; j<m; j++)
        {
            if(temp[i][j-1] > temp[i-1][j])
            {
                temp[i][j] = A[i][j-1] + A[i][j];
                result[track] = A[i][j];
                track++;
            }

            else if (tem[i-1][j] == temp[i][j-1])
            {
                temp[i][j] = A[i-1][j] + A[i][j];
                result[track] = A[i][j];
                track++;
            }

            else
            {
                temp[i][j] = A[i-1][j] + A[i][j];
                result[track] = A[i][j];
                track++;
            }
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
    maxpath(m,n, A);

    return 0;
}
