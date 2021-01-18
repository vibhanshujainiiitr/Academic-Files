/*
 * Program: Speedup calculation of matrix multiplication with
 *          multi-processing and multi-threading.
 * Author:  S.Reethu & Vibhanshu Jain
 * Roll# :  CS19B1023 & CS19B1027
 */

#include <stdlib.h> /* for exit, atoi */
#include <stdio.h>  /* for fprintf */
#include <errno.h>  /* for error code eg. E2BIG */
#include <getopt.h> /* for getopt */
#include <assert.h> /* for assert */


#include <time.h>  /* Time of the day gettimeofday */
#include<pthread.h>     /* For thread */
#include <unistd.h>     /* For fork */
#include<sys/wait.h>    /* For wait function */
#include<sys/types.h>   /* For pid_t function */
#include<signal.h>
#include <sys/ipc.h>    /* For inter process communication */
#include <sys/shm.h>    /* For the shared memory */
#include<sys/time.h>
#include<stdint.h>
/*
 * Forward declarations
 */

void usage(int argc, char *argv[]);
void init_matrix();
void input_matrix(int *mat, int nrows, int ncols);
void output_matrix(int *mat, int nrows, int ncols);

unsigned long long single_thread_mm();
unsigned long long multi_thread_mm();
unsigned long long multi_process_mm();

int *A, *B, *C;
int crows, ccols;
int arows, acols, brows, bcols;
char interactive = 0;

int shared_C;
// Shared memory variable

int usec, sec;
// Variable for time

struct  timeval start, end;
// timeval structure of time.h 



int main(int argc, char *argv[])
{
	int c;

	/* Loop through each option (and its's arguments) and populate variables */
	while (1) {
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{"help",	no_argument,		0, 'h'},
			{"ar",		required_argument,	0, '1'},
			{"ac",		required_argument,	0, '2'},
			{"br",		required_argument,	0, '3'},
			{"bc",		required_argument,	0, '4'},
			{"interactive",	no_argument, 		0, '5'},
			{0,		0,			0,  0 }
		};

		c = getopt_long(argc, argv, "h1:2:3:4:5", long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 0:
			fprintf(stdout, "option %s", long_options[option_index].name);
			if (optarg)
				fprintf(stdout, " with arg %s", optarg);
				fprintf(stdout, "\n");
			break;

		case '1':
			arows = atoi(optarg);
			break;

		case '2':
			acols = atoi(optarg);
			break;

		case '3':
			brows = atoi(optarg);
			break;

		case '4':
			bcols = atoi(optarg);
			break;

		case '5':
			interactive = 1;
			break;

		case 'h':
		case '?':
			usage(argc, argv);

		default:
			fprintf(stdout, "?? getopt returned character code 0%o ??\n", c);
			usage(argc, argv);
		}
	}

	if (optind != argc) {
		fprintf(stderr, "Unexpected arguments\n");
		usage(argc, argv);
	}

	unsigned long long time_single, time_multi_process, time_multi_thread;
	/* Add your code here */

	//the order of matrix C
    crows = arows;
    ccols = bcols;

	//Allocating memory in Heap segment
    A=(int*)malloc(arows*acols*sizeof(int));
    B=(int*)malloc(brows*bcols*sizeof(int));
	C=(int*)malloc(crows*ccols*sizeof(int));

    time_single=single_thread_mm();
    time_multi_process=multi_process_mm();
    time_multi_thread=multi_thread_mm();

	/* TODO */

	fprintf(stdout, "Time taken for single threaded: %llu us\n",
			time_single);
	fprintf(stdout, "Time taken for multi process: %llu us\n",
			time_multi_process);
	fprintf(stdout, "Time taken for multi threaded: %llu us\n",
			time_multi_thread);
	fprintf(stdout, "Speedup for multi process : %4.2f x\n",
			(double)time_single/time_multi_process);
	fprintf(stdout, "Speedup for multi threaded : %4.2f x\n",
			(double)time_single/time_multi_thread);

	exit(EXIT_SUCCESS);
}

/*
 * Show usage of the program
 */
void usage(int argc, char *argv[])
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s --ar <rows_in_A>  --ac <cols_in_A>"
			" --br <rows_in_B>  --bc <cols_in_B>"
			" [--interactive]",
			argv[0]);
	exit(EXIT_FAILURE);
}

/* 
*  Initializing the Matrix A and B
*/
void init_matrix()
{
    for(int i = 0; i < arows*acols; i++)
        A[i] = rand();
    for(int i = 0; i < brows*bcols; i++)
        B[i] = rand();

    for( int i = 0; i < crows*ccols; i++)
        C[i] = 0;
}

/*
 * Input a given 2D matrix
 */
void input_matrix(int *mat, int rows, int cols)
{
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			fscanf(stdin, "%d", mat+(i*cols+j));
		}
	}
}

/*
 * Output a given 2D matrix
 */
void output_matrix(int *mat, int rows, int cols)
{
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			fprintf(stdout, "%d ", *(mat+(i*cols+j)));
		}
		fprintf(stdout, "\n");
	}
}


/*   Single Thread Matrix Multiplication */

unsigned long long single_thread_mm()
{   
    // Checking wether the multiplication can be done.
 /*   if(acols != bcols)
    {
        return 0;
    }
*/
    if(interactive == 0)
        init_matrix();

    else if(interactive == 1) {
        fprintf(stdout,"Enter A:\n");
        fflush(stdout);
        input_matrix(A,arows,acols);
        fprintf(stdout,"Enter B:\n");
        fflush(stdout);
        input_matrix(B,brows,bcols);
    }

    int x, y ,z ;

    // Starting time
    gettimeofday(&start, 0 );

    for( int i = 0 ; i < crows ; i ++)
    {
        y = i*acols, z =i*ccols;
        for(int j=0; j<ccols; j++)
        {
            x = 0;
            for( int k = 0; k<acols; k++)
            {
                x += A[y + k] * B[k*bcols + j];
            }
            C[z+j] = x;
        }
    }


    gettimeofday(&end, 0);          //ending time
    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    unsigned long long int time =sec*1000000+usec; //calculating time in microseconds


    if(interactive == 1) {
        fprintf(stdout,"Result:\n");
        fflush(stdout);
        output_matrix(C,crows,ccols);
    }

    return time;
}


/* Multiplication for thread */
void * multiplication(void *arg)
{
    int *data = (int *)arg;

    int i = (*data) , x = 0, y = i*acols, z = i*ccols;
    //Multi Process to heap segment

    for( int j = 0; j < ccols ; j++)
    {
        x = 0;

        for( int k = 0; k<acols ; k++)
        {
            x+= A[y+k] * B[k*bcols + j];
        }
        C[z+j] = x;
    }
}

/* Multiple Thread Matrix Multiplication */
unsigned long long multi_thread_mm()
{   
    // Checking wether the multiplication can be done.
/*    if(acols != bcols)
    {
        return 0;
    }
*/
    if( interactive == 0)
        init_matrix();
    
    else if( interactive == 1)
    {
        fprintf(stdout, "Matrix A: \n");
        fflush(stdout);
        input_matrix(A, arows, acols);

        fprintf(stdout, "Matrix B: \n");
        fflush(stdout);
        input_matrix(B, brows, bcols);      
    }

    pthread_t thread[crows];
    //Optimal number of reads as crows

    int *value = (int*)malloc(crows * sizeof(int));
    // Dynamic memory allocation of heap

    for(int i=0; i< crows; i++)
    {
        value[i] = i;
        pthread_create( &thread[i], NULL, multiplication, &value[i]); 
        // Creating the threads
        }

        gettimeofday(&start, 0 );
        // keeping the track of start time

        for( int i = 0; i<crows; i++)
        {
            pthread_join( thread[i], NULL);
        }

        gettimeofday(&end, 0);

        sec = end.tv_sec - start.tv_sec;
        usec = end.tv_usec - start.tv_usec;
        unsigned long long int time =sec*1000000+usec; 
        //calculating time

        // Outputing the result

        if( interactive == 1)
        {
            fprintf(stdout, "Result: \n");
            fflush(stdout);
            output_matrix( C, crows, ccols);
        }

        return time;
    }


/* Multiprocess Matrix Multiplication Function */
unsigned long long multi_process_mm()
{   
    // Checking wether the multiplication can be done.
/*    if(acols != bcols)
    {
        return 0;
    }
*/
    if(interactive == 0 )
        init_matrix();
    
    else if (interactive == 1)
    {
        // Matrix A
        fprintf(stdout, "Matrix A: \n");
        fflush(stdout);
        input_matrix(A, arows, acols);

        // Matrix B
        fprintf(stdout, "Matrix B \n");
        fflush(stdout);
        input_matrix(B, brows, bcols);
    }

    int x, y, z;

    // Assigning C to the shared memory

    key_t key = ftok("shmfile", 789);
    int flag = IPC_CREAT | 0666;

    shared_C = shmget( key, (sizeof(int))*arows*bcols, flag );
    C = shmat(shared_C, NULL, 0);

    // Storing the start time
    gettimeofday(&start, 0);

    // Creating the new process for work
    pid_t child;
    child = fork();

    if( child < 0)
    {
        // This indicates error in creating the child process
        exit(EXIT_FAILURE);
    }

    else if (child == 0 )
    {
        child = fork();
        // Creating another child process 

        if( child < 0)
        {
            // This again indicates error in creating this child process   
            exit(EXIT_FAILURE);
        }

        else if (child == 0)
        {
            // Now we will do the computation
            // The half computation part 
            for( x = 0 ; x < (crows)/2 ; x ++ )
            {
                for( y = 0; y < ccols; y++)
                {
                    C[ x*ccols + y] = 0;
                    for( z = 0 ; z < acols; z++)
                    {
                        C[x*ccols + y] += A[x*acols + z ]*B[ z*bcols + y];
                    }
                }
            }

            shmdt(C);
            exit(0);
        }

        else 
        {
            // Computing the other half
            for( x = (crows)/2 ; x < arows; x++ )
            {
                for( y = 0; y <ccols; y++)
                {
                    C[x*ccols + y] = 0;
                    for( z =0 ; z < acols; z++)
                    {
                        C[x*ccols + y ] += A[x*acols + z]*B[z*bcols + y];
                    }
                }
            }

            shmdt(C);
            exit(0);
        }
    }

    else
    {
        // The Parent should not do any computation
        while(wait(NULL)!= -1);
        //Wait till all the process get over

        shmctl( shared_C , IPC_RMID, 0);
    }


    // Traking the ending time
    gettimeofday(&end, 0);

    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;
    unsigned long long int time; 
    time =sec*1000000+usec;    
    // Calculating time


    // The interactive is one then print output too
    if( interactive == 1)
    {
        fprintf(stdout, "Result: \n");
        fflush(stdout);
        output_matrix(C, crows, ccols);
    }

    // Returning the time
    return time;
}
