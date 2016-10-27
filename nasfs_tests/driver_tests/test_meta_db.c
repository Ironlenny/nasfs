#include <tap.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <sys/stat.h>

const char db_file[] = "./meta_db";
MDB_env *env = NULL;
MDB_dbi db_handle;
int result = 0;
char *meta_value;


int test_open(bool create, unsigned long db_id, int max_db)
{
  return meta_open(db_file, db_id, create, &env, &db_handle, max_db);
}

void test_close()
{
  meta_close(&env, &db_handle);
}

int main()
{
  plan(NO_PLAN);
  mkdir(db_file, 0777);
  result = test_open(false, 0, 0);
  cmp_ok(result , "==", 0, "Create and open db file");
  test_close();
  result = test_open(true, 1, 10);
  cmp_ok(result , "==", 0, "Create and open named db");
  test_close();
  result = test_open(false, 1, 10);
  cmp_ok(result , "==", 0, "Open named db");
  cmp_ok(meta_put(&env, &db_handle, "foo", "bar"), "==", 0, "Wrote \"foo\".");
  cmp_ok(meta_get(&env, &db_handle, "foo", meta_value), "==", 0,
         "Read \"foo\".");
  is(meta_value, "bar");

  return 0;
}
