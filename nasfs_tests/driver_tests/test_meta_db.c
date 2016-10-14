#include <tap.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <sys/stat.h>

const char db_file[] = "./meta_db";
MDB_env *env;
MDB_dbi *dbi;
int result = 0;

int main()
{
  plan(NO_PLAN);
  mkdir(db_file, 0777);
  result = meta_open(db_file, 0, false, &env, dbi);
  cmp_ok(result , "==", 0, "Create db file");

  return 0;
}
