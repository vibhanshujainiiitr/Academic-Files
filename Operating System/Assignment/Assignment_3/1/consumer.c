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

  /* Open the Shared Buffer for reading by Consumer */
  fd = shm_open("/myBuffer", O_RDONLY, 0666);

  if (fd == -1)
    {  /* Handle error */;
    printf("No Shared Buffer Exists\n");
    return -1;
    }

  /* Map shared memory object to process’ address space */
  bptr = mmap(NULL, sizeof(int)*BUFFER_SIZE, PROT_READ, MAP_SHARED, fd, 0);
  if (bptr == MAP_FAILED)
    {
      printf("Error in mapping Shared Buffer\n");
      return -1;
    }
  
  printf("Consumer with PID=%d is reading from Shared Buffer\n",getpid());
  
  for(int i=0; i<BUFFER_SIZE; i++)
    {
      //Reading 
      printf("%dth item in the Shared Buffer:%d\n", i, bptr[i]); 
    }
  
  int i = 0;
  while(1)
  {
    if(bptr[i] != 0)
    {
      printf("The consumer is cosuming the item %d with a value of %d", i, bptr[i]);
      bptr[i] = 0;
    }

     i = (i+1)%10;
  }

  shm_unlink("/myBuffer");
  return 0;
}