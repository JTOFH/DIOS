#include <sqlite3.h>
#include <string.h>
#inclide "dios.h"

sqlite3 *dbhandle;

void update_db(char *msg)

{
  sqlite3_stmt *dbstmt;
  int len = strlen(msg)+1;

  sqlite3_prepare_v2(dbhandle,msg,len,&dbstmt,NULL);
  sqlite3_step(dbstmt);
  sqlite3_finalize(dbstmt);
}

int size_table(char *table)

{
  const char *stmt = "SELECT COUNT(*) FROM ";
  char buf[1024];
  sqlite3_stmt *dbstmt;
  int len;

  sprintf(buf,"%s %s",stmt,table);
  len = strlen(buf)+1;

  sqlite3_prepare_v2(dbhandle,buf,len,&dbstmt,NULL);
  sqlite3_step(dbstmt);
  ival = sqlite3_column_int(dbstmt,0);
  sqlite3_finalize(dbstmt);
  return(ival);
}

void open_db()

{
  char dbname[256];
  sprintf(dbname,"diosd.%d",cpid); 
  sqlite3_open(dbname,&dbhandle);
}

void close_db()

{
  sqlite3_close(dbhandle);
}

void write_markers()

{
  const char *sstmt = "INSERT INTO StringTable";
  const char *mstmt = "INSERT INTO CUPTI_ACTIVITY_KIND_MARKER";
  msg *p;
  int i = 1;
  int snum;

  p = root_msg;
  snum = size_table("StringTable");
  while (p != NULL) {
    sprintf(buf,"%s VALUES(snum,\'%s\')",sstmt,p->name);
    update_db(buf);
    sprintf(buf,"%s VALUES(%d,2,%lu,X\'%x\',%d,0)",
	mstmt,i++,p->stime,p->objid,snum);
    update_db(buf);
    sprintf(buf,"%s VALUES(%d,4,%lu,X\'%x\',0,0)",
	mstmt,i++,p->etime,p->objid);
    update_db(buf);
    p = p->next;
  }
}
