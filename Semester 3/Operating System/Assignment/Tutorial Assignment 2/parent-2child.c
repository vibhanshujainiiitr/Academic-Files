// Vibhanshu Jain

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	pid_t child_1, child_2;
	int temp;
	
		/*fork the child 1 process */
		child_1 = fork();
		/* fork the child 2 process */
		child_2 = fork();

		if(child_1 < 0 || child_2 < 0) 
		{
			/* error occured */
			fprintf(stderr, "Fork Failed");
			return 1;
		}
		else if( child_1 == 0) {
			/* child 1 process */
			sleep(1);
			fprintf(stdout, "My PID is %d and my parent PID is %d \n",getpid(), getppid());
		}

		else if(child_2 == 0)
		{	
			/* second child process */
				// Printing the values before the child 2 is going for sleep
				fprintf(stdout, "The PID values before child 2 sleeps\n Child 1: %d, Child 2: %d, Parent %d\n",getpid(), child_1, getppid());
				sleep(10);
				// Values after sleeping for 10s
				fprintf(stdout,"The PID values after child 2 sleeps\n Child 1: %d, Child 2: %d, Parent %d\n",getpid(), child_1, getppid());
				kill(child_1, SIGKILL);
				// Values after killing the child 1
				fprintf(stdout, "The values after the child 1 is killed by child two\n Child 2: %d, Parent: %d\n", getpid(), getppid());
				sleep(10);
				// The values after the child 2 sleeps for 10s
				fprintf(stdout, "The PID values after child 2 sleeps\nChild 2: %d, Parent %d\n",getpid(),getppid());
				
				exit(0);
			}

		else{
			/* Parent Process */
			/* Parents will wait for the child to complete */
			waitpid(child_1, &temp, 0);
			waitpid(child_2, &temp, 0);
			wait(NULL);
		}

		return 0;
}	
