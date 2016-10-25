#include <tap.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <sys/stat.h>

const char db_file[] = "./meta_db";
MDB_env *env = NULL;
MDB_dbi db_handle;
int result = 0;
MDB_txn *txn = NULL;

int test_open(bool create, unsigned long db_id, int max_db)
{
  return meta_open(db_file, db_id, create, &env, &db_handle, max_db, txn);
}

int main()
{
  plan(NO_PLAN);
  mkdir(db_file, 0777);
  result = test_open(false, 0, 0);
  cmp_ok(result , "==", 0, "Create and open db file");
  result = test_open(true, 1, 10);
  cmp_ok(result , "==", 0, "Create and open named db");
  mdb_txn_commit(txn);
  result = test_open(false, 1, 10);
  cmp_ok(result , "==", 0, "Open named db");
  return 0;
}
