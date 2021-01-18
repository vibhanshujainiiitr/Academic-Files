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



const char* scs( char a[], char b[], char sequence[])
{
    int n = strlen(a);
    int m = strlen(b);
    
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
    
    int i = m , j = n ;
    while ( i > 0 && j > 0)
    {
        
        if ( a[i-1] == b[j-1] )
        {
            sequence[count] = a[i-1];
            count++;
            i--, j--, index--; 
        }
        
        else if (key[i-1][j] > key[i][j-1])
        {
            sequence[count] = b[j-1];
            count++;
            j--; index--;
        }
        
        else
        {
            sequence[count] = a[i-1];
            count++;
            i--; index--;
        }
    }
    
    while ( i>0)
    {
        sequence[count] = a[i-1];
        count++;
        i--, index--;
    }
    
    while(j>0)
    {
        sequence[count] = b[j-1];
        count++;
        j--; index--;
    }
    
    return sequence;
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
    scanf("%s %s", a, b);
    
    char sequence[len1+len2];
  //  printf("The SCS of the given two strings are %s", scs(a,b,sequence));
    
    printf("The strings entered by you are: %s %s", a,b);
    return 0;
}
