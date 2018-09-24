
#ifndef __MISC_H__
#define __MISC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int debug_level;
extern FILE *logfp;

void fatal(int, char *);
void debug(int, char *);
char *emalloc(int);
char *cloneString(char *);
void openLog(char *);
void writeLog(char *);
void closeLog();

#endif
