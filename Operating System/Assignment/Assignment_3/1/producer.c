#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#define BUFFER_SIZE 10

int main () {

  int fd;
  int *bptr;

  /* Create shared memory object and set its size */
  fd = shm_open("/myBuffer", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

  if (fd == -1)
    {  /* Handle error */;
    printf("Error in creating Shared Buffer\n");
    return -1;
    }

  if (ftruncate(fd, sizeof(int)*BUFFER_SIZE) == -1) //set Size
    {
      printf("Errror in setting the size of Shared Buffer\n"); /* Handle error */
      return -1;
    }

  /* Map shared memory object to process’ address space */
  bptr = mmap(NULL, sizeof(int)*BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (bptr == MAP_FAILED)
    {
      printf("Error in mapping Shared Buffer\n");
      return -1;
    }
  
/* Now we can refer to mapped region using fields of bptr */
  printf("This is for test");
  
  int i = 1;
  while(1)
    {
      //Check wether there is already a value in the buffer or not, if not then input the value
      if( bptr[i] != 0 ){
          //write to shared memory by producer
   	      printf("Enter integer number for writing to the buffer");
	        scanf("%d",&bptr[i]);
	        printf("Producer with PID %d is writing to the %dth slot of the buffer with the value %d",getpid(),i,bptr[i] );
      }

      if( i == 10)
        {
          printf("The buffer is completely fulled.\n");
        }
      // Increamenting the value of i each time and also considering it must run in a loop.
      i = (i+1)%10;   
    }

  //shm_unlink("/myBuffer");
  return 0;
}
