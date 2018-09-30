
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <string.h>
#include "unistd.h"
#include "d_shmem.h"

static void *shmem_base;
 __attribute__((constructor)) static void doInit()

{
  unsigned dpid, shmem_fd;
  char buf[256];
  long pagesize = sysconf(_SC_PAGE_SIZE);
  int (*kernel_open)(const char *, int, ...) = dlsym(RTLD_NEXT,"open");

  FILE *fp = fopen("/tmp/dios.lock","r");
  fscanf(fp,"%d",&dpid);
  fclose(fp);
  sprintf(buf,"/tmp/dios.%d",dpid);
  shmem_fd = kernel_open(buf,O_RDWR);
  printf("Initialising. dpid = %d, shmem_fd = %d\n",dpid, shmem_fd);
  shmem_base = mmap(
	NULL, 2*pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
  printf("init: shmem_base = %p, pgsize = %ld\n",shmem_base,pagesize);
  if (shmem_base == MAP_FAILED)
    fprintf(stderr,"Culdn't mmap\n");
}

 __attribute__((destructor)) static void doFini()

{
  printf("Tearing Down\n");
}


int open(const char *pathname, int flags, ...)

{
  int (*kernel_open)(const char *, int, ...) = dlsym(RTLD_NEXT,"open");
  va_list oargs;
  mode_t mode;
  int rval;
  DSHHdr hdr;
  char data[256];

  if ((flags & O_CREAT) || (flags & O_TMPFILE)) {
    va_start(oargs,flags);
    mode = va_arg(oargs,mode_t);
  } else
    mode = 0;
  rval = kernel_open(pathname, flags, mode);
  printf("open: %s %d %d - rval = %d\n",pathname,flags,mode,rval);
  sprintf(data,"open: %d %d %d %s",flags,mode,rval,pathname);
  hdr.type = DSH_SAMPLE;
  hdr.offset = 128;
  hdr.MsgLen = strlen(data);
  write_shmem(shmem_base,hdr,data);
  return rval;
}
