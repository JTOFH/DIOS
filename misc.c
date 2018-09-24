
#include "misc.h"
#include <time.h>

int debug_level = 0;
FILE *logfp = NULL;

void fatal(int errnum, char *msg)

{
   char buf[1024];

   sprintf(buf,"FATAL ERROR: %d (%s)\n",errnum,msg);
   fprintf(stderr,"%s",buf);
   writeLog(buf);
   closeLog();
   exit(errnum); 
}

void debug(int level, char *msg)

{
  char buf[1024];

  if (level < debug_level)
    return;
  sprintf(buf,"DEBUG: (%s)\n",msg);
  fprintf(logfp,"%s",buf);
}

char *emalloc(int nbytes)

{
  char *p;

  if ((p = malloc(nbytes)) == NULL)
    fatal(-1,"Out of memory");
  return(p);
}

char *cloneString(char *os)

{
  char *p;
 
  p = emalloc(strlen(os)+1);
  strcpy(os,p);
  p[strlen(os)] = '\0';
  return(p);
}

void openLog(char *fname)

{
  if ((logfp = fopen(fname,"w")) == NULL)
    fatal(-2,"Cannot create logfile");
  writeLog("Log Started");
}

void writeLog(char *msg)

{
  time_t tval;
  char buf[1024];

  tval = time(NULL);
  strcpy(buf,ctime(&tval));
  buf[23] = '\0';
  fprintf(logfp,"%s = %s\n",buf,msg);
}
 
void closeLog()

{
  writeLog("Log Closed");
  fclose(logfp);
}
