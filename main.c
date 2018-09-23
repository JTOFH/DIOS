
// main.c - Main Line for standalone DIOS shim
//

#include "dios.h"
#include "misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void doArgs(int, char **);
void Usage(const char *);

D_Mode mode;
char *cfg_fname;
char *exe_fname;

void Usage(const char *name)

{
  fprintf(stderr,"Usage: %s [-c <cfg-file>][-h][-m <mode>] <prog> [args]\n",
	name);
  fprintf(stderr,"\nOPtions:\n");
  fprintf(stderr,
	"\t-c <cfg-file>\tUse <cfg-file for config (default dios.cfg)\n");
  fprintf(stderr,"\t-h\t\tPrint this message\n");
  fprintf(stderr,
	"\t-m <mode>\tSpecify passthru or simulate mode (default passthru)\n");
  exit(1);
}

void doArgs(int argc, char *argv[])

{
  char c, *p;

  exe_fname = cloneString(*argv);
  while (--argc && (*++argv)[0] == '-')
    for (p = *argv+1; *p != '\0'; p++)
      switch(*p) {
        case 'c': // Config File
          argv++; argc--;
          cfg_fname = cloneString(*argv);
          cfg_fname = emalloc(strlen(*argv));
          strcpy(cfg_fname,*argv);
          exe_fname[strlen(*argv)] = '\0';
          break;
        case 'h': // Help
          Usage(exe_fname);
        case 'm': //Mode
          argv++; argc--;
          if (strcmp(*argv,"passthru") == 0)
            mode = D_PASSTHRU;
          else if (strcmp(*argv,"simulate") == 0)
            mode = D_SIMULATE;
          else
            Usage(exe_fname);
        default:
          Usage(exe_fname);
      }
}

int main(int argc, char *argv[])

{
  doArgs(argc,argv);
}

