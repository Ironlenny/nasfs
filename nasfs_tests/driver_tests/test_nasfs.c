#include <tap.h>
#include "../../nasfs_driver/nasfs.c"
#include <fuse.h>
#include <bson.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdlib.h>

static char super_path[] = "./super_block";
static char *meta_return;
static char meta_db[] = "./meta_db";

int test_initalize()
{
  if (nas_initalize(super_path) == 0)
    {
      return 1;
    }

  return 0;
}

int test_create()
{
  return 0;
}

int test_open()
{
  return 0;
}

int test_read()
{
  return 0;
}

int test_release()
{
  return 0;
}

int test_write()
{
  return 0;
}

int test_mkdir()
{
  int result = 0;
  unsigned long db_id = 0;
  if(nas_mkdir("/foo", 0777) == 0)
    {
      result = 1;
    }

  if ((meta_open(meta_db, 0, false, max_dir) && (meta_get("/foo", &meta_return) == 0)))
    {
      result = 1;
    }

  if (meta_return != NULL)
    {
      db_id = strtoul (meta_return, NULL, 10);
    }

  if ((db_id != 0) && (meta_open(meta_db, db_id, false, max_dir) == 0))
    {
      result = 1;
    }

  meta_free (meta_return, NULL);

  return result;
}

int test_opendir()
{
  return 0;
}

int test_rmdir()
{
  return 0;
}

int test_readdir()
{
  return 0;
}

int test_releasedir()
{
  return 0;
}

int main(int argc, const char *argv[])
{
  printf("nasfs.c tests:\n");
  plan(NO_PLAN);
  ok(test_initalize(), "Super block read");
  cmp_ok(max_dir, "==", 65000, "max_dir is set correctly");
  cmp_ok(raid_lv, "==", 1, "raid_lv is set correctly");
  is(vol[0], "./a", "vol[0] is set correctly");
  is(vol[1], "./b", "vol[1] is set correctly");
  ok(test_create());
  ok(test_open());
  ok(test_write());
  ok(test_release());
  ok(test_mkdir(), "Made new directory");
  ok(test_readdir());
  ok(test_releasedir());
  return 0;
}
