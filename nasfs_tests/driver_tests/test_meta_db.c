#include <tap.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <sys/stat.h>
#include <string.h>

#define DB_DIR "./meta_db"
#define RM_DB "rm -rf " DB_DIR


int test_open(bool create, unsigned long db_id, int max_db)
{
  return meta_open
    (db_file, db_id, create, max_db);
}

void test_close()
{
  meta_close();
}

int main()
{
  plan(NO_PLAN);
  mkdir(db_file, 0777);
  cmp_ok((test_open(false, 0, 0)) , "==", 0, "Create and open db file");
  test_close();
  cmp_ok((test_open(true, 1, 10)) , "==", 0, "Create and open named db");
  test_close();
  cmp_ok((test_open(false, 1, 10)) , "==", 0, "Open named db");
  cmp_ok(meta_put("foo", "bar"), "==", 0, "Wrote \"bar\" at \"foo\".");
  cmp_ok(meta_get("foo", &meta_value), "==", 0,
         "Read \"foo\".");
  test_close();
  is(meta_value, "bar", "\"bar\" is read.");
  free(meta_value);
  return 0;
}
