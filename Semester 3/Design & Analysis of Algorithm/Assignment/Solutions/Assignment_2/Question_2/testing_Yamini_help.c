#include <stdio.h>
#include<string.h>


// The funtion to return the minimum of two numbers
int min(int a, int b)
{   
    if(a>b)
    {
        return b;
    }
    
    else
    {
        return a;
    }
}


int main()
{
    // length of the two strings that will be given by the user as input.
    int len1, len2;
    printf("Please input the length of the strings\n");
    scanf("%d %d", &len1, &len2);
    
    char a[len1];
    char b[len2];
    
    // Inputing the two strings. 
    printf("Enter the strings\n");
    scanf("%s",b);
    scanf("%s",a);
    
    
    int n = len1;
    int m = len2;
    
    int key[n+1][m+1];
    // The 2D ay to store the length.
    
    
    for(int i = 0; i<=m; i++)
    {
        for(int j=0; j<=n; j++)
        {
            if(i==0)
                key[i][j] = j;
            else if(j==0)
                key[i][j] = i;
            else if(a[i-1] == b[j-1])
                key[i][j] = 1 + key[i-1][j-1];
            else
                key[i][j] = 1 + min(key[i-1][j], key[i][j-1]);
        }
    }
    
    int index = key[m][n], count = 0;
    char sequence[index]; 
    
    int i = m , j = n ;
    index--;
    while ( i > 0 && j > 0)
    {
        if ( a[i-1] == b[j-1] )
        {   
            sequence[index] = a[i-1];
            i--, j--, index--; 
            printf("Hello 1");
        }
        
        else if (key[i-1][j] > key[i][j-1])
        {
            sequence[index] = b[j-1];
            j--; index--;
            printf("Hello 2");
        }
        
        else
        {
            sequence[index] = a[i-1];
            i--; index--;
        }
    }
    
    while ( i>0)
    {
        sequence[index] = a[i-1];
        i--, index--;
    }
    
    while(j>0)
    {
        sequence[index] = b[j-1];
        j--; index--;
    }
    
    
    printf("The SCS of the given two strings are %s\n", sequence);
    
    printf("The strings entered by you are: %s %s",a,b);
    return 0;
}

