
#include <sys/mman.h>
#include <stdio.h>
#include "d_shmem.h"

int shmem_fd;

void *init_shmem()

{
  void *p;
  char fname[1024];

  sprintf(fname,"/tmp/dios.%d\n",getpid());
  shmem_fd = creat(fname);
  p = mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_SHARED,shmem_fd,0);
  return(p);
}

void kill_shmem(void *p)

{
  munmap(p,0);
}
