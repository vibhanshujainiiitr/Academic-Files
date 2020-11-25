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
  for(int i=0; i<BUFFER_SIZE; i+=2)
    {
     //write to shared memory by producer
      bptr[i]=i;
    }

  for(int i=0; i<BUFFER_SIZE; i++)
    {
      //Test that writing is successful
      printf("%dth item in the Shared Buffer:%d\n", i, bptr[i]); 
    }
  //shm_unlink("/myBuffer");
  return 0;
}
