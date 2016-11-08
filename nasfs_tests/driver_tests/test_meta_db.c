#include <tap.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <sys/stat.h>
#include <string.h>

#define DB_DIR "./meta_db"
#define RM_DB "rm -rf " DB_DIR

char *meta_value;
char **all_keys;
char **all_values;

int test_open(bool create, unsigned long db_id, int max_db)
{
  return meta_open(DB_DIR, db_id, create, max_db);
}

void test_close()
{
  meta_close();
}

size_t test_fill()
{
  test_open(true, 1, 10);

  for(int i = 0; i < 1000; i++)
    {
      char foo[30];
      sprintf(foo, "%s%d", "foo", i);
      meta_put(foo, "bar");
    }

  for(int i = 0; i < 1000; i++)
    {
      char foo[30];
      char *bar;
      sprintf(foo, "%d%s", i, "foo");
      meta_get(foo, &bar);
      //printf("foo: %s, bar: %s\n", foo, bar);
      if(strncmp(bar, "bar", 3))
        {
          printf("Test failed on index %d\n", i);
          printf("bar is %s\n", bar);
          return 1;
        }

    }

  return 0;
}

int main()
{
  plan(NO_PLAN);
  mkdir(DB_DIR, 0777);
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
  free(meta_value); //replace with meta_db.c function.
  system(RM_DB);
  mkdir(DB_DIR, 0777);
  cmp_ok(test_fill(), "==", 0, "Put 1000 entries in db");
  cmp_ok(meta_get_keys(&all_keys, &all_values, 1, DB_DIR), "==", 0, "Got all\
keys from db 1.");
  test_close();

  return 0;
}
