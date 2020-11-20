#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	
		/*fork a child process */
		pid = fork();

		if(pid < 0 ) 
		{
			/* error occured */
			fprintf(stderr, "Fork Failed");
			return 1;
		}
		else if( pid == 0 ) {
			/* child process */
			execlp("/bin/ls", "ls", NULL);
		}
		else{
			/* Parent Process */
			/* Parents will wait for the child to complete */
			wait(NULL);
			printf("Child Complete");
		}

		return 0;
}

			
