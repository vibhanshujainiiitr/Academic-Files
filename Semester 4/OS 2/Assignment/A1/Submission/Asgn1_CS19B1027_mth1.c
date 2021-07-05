/* 
*   Assignment 1 - Operating System
*   Vibhanshu Jain
*   CS19B1027
*/


#include <stdlib.h> /* for exit, atoi */
#include <stdio.h>  /* for fprintf */
#include <errno.h>  /* for error code eg. E2BIG */
#include <getopt.h> /* for getopt */
#include <assert.h> /* for assert */
#include <math.h>   /* for math functions */ 

#include <time.h>           /* Time of the day gettimeofday */
#include <pthread.h>        /* For thread */
#include <sys/types.h>      /* For pid_t function */
#include <signal.h>
#include <sys/time.h>
#include <stdint.h>

void    init_numbers();
/* Function to add random numbers to the array */
void    print_numbers();
/* Function to print the number inside the array */
void*   merge_sort(void* arg);
/* Merge sort function which is called by the thread */
void    merge(int l, int m, int r);
/* Main merge functio for merging the elememts between l and m with m + 1 and r */
void    mergesort(int l, int r);
/* Sorting the array between l and r indexes */
long*   A;
/* The array */
int     n, p;
/* 
   The total number of elements: n
   The total number of segments: p 
*/

int main()
{   
    
    /* For keeping record of the timing */ 
    clock_t t0, t1; 

    int pow_n, pow_p;
    /* For inputting the parameters */

    fscanf(stdin, "%d %d", &pow_n, &pow_p);

    n = pow(2, pow_n);
    p = pow(2, pow_p);
    /* Adding the values to the global variable */

    /* Allocating memory in heap segment */
    A = (long*)malloc(n*sizeof(long));

    /* Inputing the random values in the array */
    init_numbers();

    /* Printing the array */
    print_numbers(); 
    fprintf(stdout,"\n");

    t0 = clock();
    /* t0 stores the time of this point */

    /*Declearing the threads */
    pthread_t thread[p];

    /* Calling merge_sort function by the thread */
    for( int i =0; i < p; i++)
    {
        pthread_create( &thread[i], NULL, merge_sort, &i);                  
    }

    /* Calling the join function */
    for( int i =0; i < p; i++)
    {
        pthread_join(thread[i], NULL);
    }

    /* calling the merge function */
    for( int i =1; i <= p; i++)
    {   
        int start = ( (n/p)*(i-1) );
        int end = (( (n/p)*i ) - 1 );
        merge(0, start , end);
    }

    /* t1 will store the time of this instance*/
    t1 = clock();

    /* Printing the numbers */
    print_numbers();
    printf("\n");

    /* The time taken by the function to perform merge is t1 - t0 */
    printf("The time taken is %ld Microseconds", t1-t0);
}   

/* Function to input random values in the array*/
void init_numbers()
{
    for( int i = 0; i < n; i++)
    {
        A[i] = rand();          // rand function is used to generate the random values
    }
}

/* Function to print the array */
void print_numbers()
{
    for( int i = 0; i < n; i ++)
    {
        fprintf(stdout,"%ld ", A[i]);
    }
}

/* This function is called by the threads to sort the elements in the given segment */
void* merge_sort(void* arg)
{   
    int* value = (int* )arg;
    int start = (*value);
    /* Here, start will store the number of segment of whose elements we needed to sort */
    int l = (n/p)*(start - 1 );
    int r = (( (n/p)*start ) - 1 );

    /* Merge Sort function is called to perform the sorting of the elements between l & r indexes of the array */
    mergesort(l,r);
}

/* Function to perform the sorting of the elements between l & r indexes of the array */
void mergesort(int l, int r)
{
    if(l < r)
    {
        int m = l + (r-l)/2;

        mergesort(l,m);
        mergesort(m+1,r);
        
        /* 
        *   Calling the merge function to merge the elements between
        *   l & m ; and m & r indexes  
        */
        merge(l, m ,r);
    }
}


/* 
    The merge function to merge the elements between the index l & r, 
    where m is the index of the partation 
*/
void merge( int l, int m, int r)
{
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;

    long L[n1], R[n2];

    for(i=0; i<n1; i++)
        L[i] = A[l+i];

    for(j=0; j<n2; j++)
        R[j] = A[m+1+j];

    i = 0; j =0; k =l;

    while( i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }

        else
        {
            A[k] = R[j];
            j++;
        }

        k++;
    }

    while( i < n1)
    {
        A[k] = L[i];
        i++;
        k++;
    }

    while( j < n2)
    {
        A[k] = R[j];
        j++;
        k++;
    }

}
