
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <dlfcn.h>

static int initFlag = 0;

static void doInit()

{
  printf("Initialised\n");
  initFlag = 1;
}

int open(const char *pathname, int flags, ...)

{
  int (*kernel_open)(const char *, int, ...) = dlsym(RTLD_NEXT,"open");
  va_list oargs;
  mode_t mode;
  int rval;

  printf("initflag = %d\n",initFlag);
/*  if (initFlag == 0) */ doInit;
  printf("initflag = %d\n",initFlag);

  if ((flags & O_CREAT) || (flags & O_TMPFILE)) {
    va_start(oargs,flags);
    mode = va_arg(oargs,mode_t);
  } else
    mode = 0;
  rval = kernel_open(pathname, flags, mode);
  printf("open: %s %d %d - rval = %d\n",pathname,flags,mode,rval);
  return rval;
}
