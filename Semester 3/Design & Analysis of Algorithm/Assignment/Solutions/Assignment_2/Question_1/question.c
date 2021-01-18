#include <stdio.h>

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
            scanf("%d", &A[i][j]);
        }
    }
    
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%d	", A[i][j]);
        }
	printf("\n");
    }
    
    
    int temp[m][n];                                     // Temp stores the maximum sum of the element till this point
    int result[m][n];					// To store the best path that can be choosen to reach upto that element
							// If this value is '0' that means it comes from its bottom and if it is '1' then it means that it comes from left element.    
    result[0][0] = 0;
    
    temp[0][0] = A[0][0];                               // The temp value of the first element is the value itself as it doesn't have any previous element.
    


    for( int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {	
     	    if(i==0)					 // The temp value of the element in last column will be initialised seperately as they don't have left elements
     	    {
     	    	temp[i][j] = A[i][j] + temp[i][j-1];
     	    	result[i][j] = 1;
     	    } 
     	    
     	    if(j==0)                                    // The temp value of the element in last row will be initialised seperately as they don't have bottom elements
     	    {
     	    	temp[i][j] = A[i][j] + temp[i-1][j];
     	    	result[i][j] = 0;
     	    }  	
        
            if(temp[i][j-1] > temp[i-1][j])             // If bottom element is chosen then the sum will maximize
            {
                temp[i][j] = temp[i][j-1] + A[i][j];
                result[i][j] = 0;              // Storing the path in result
					       // The value will be 0 as the prevoius element is on the bottom.
            }
            else if(temp[i][j-1] == temp[i-1][j])       
            {
                temp[i][j] = temp[i][j-1] + A[i][j];    // If sum from chosing anyone from the left element or the bottom element will remain equal.
                result[i][j] = 1;			// Storing the path
							// The value will be 1 as the previous element is on the left or right that doen't matter.
            }
            else
            {
                temp[i][j] = temp[i-1][j] + A[i][j];    // If the left element is choosen then the sum will maximize
                result[i][j] = 1;			// Storing the path 
							// The value will be 1 as the previous element is on the left.
            }
        }
    }
    
    printf("The maximum sum possible is %d, the path choosen is \n",temp[m-1][n-1]);
    
    
// Trying to print the path taken to reach the maximum sum    
 
/*    int i = m, j = n;
    while(i > 0 || j > 0) 
    {
       if(result[i][j] == 0)
       {
	 printf("test_1");
	 printf("->%d", A[i][j]);
	 j--;
	}
       if(result[i][j] == 1)
       {
	       printf("test_2");
	       printf("->%d", A[i][j]);
	       i--;
        }
    }
  	
	for( int i =0 ; i<m; i++)
	{
		for(int j=0 ; j<n; j++)
		{
			printf("%d	", result[i][j]);
		}
	}
*/
	return 0;
}
