#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t child_1, child_2;
	
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
		else if( child_2 == 0 ) {
			// The second will sleep for 10 sec and waits for the child one to complete
			sleep(10);
			/* child 1 process */
			if(child_1 == 0 )
			{	
				// The child one will execute till the child 2 will kill it
				sleep(1);
			    fprintf(stdout, "My PID is %d and my parent PID is %d",getpid(), getppid()); 
			}
			kill(child_1, SIGKILL)
			sleep(10);
		}

		else{
			/* Parent Process */
			/* Parents will wait for the child to complete */
			wait(NULL);
			printf("Child Complete");
		}

		return 0;
}	
