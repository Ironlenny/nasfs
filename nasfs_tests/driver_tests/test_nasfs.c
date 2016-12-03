#include <tap.h>
#include "../../nasfs_driver/nasfs.c"
#include <fuse.h>
#include <bson.h>

static char super_path[] = "./super_block";

int test_initalize()
{
  if (nas_initalize(super_path))
    {
      return 1;
    }

  return 0;
}

int test_fuse_init()
{
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
  return 0;
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
  ok(test_initalize());
  cmp_ok(max_dir, "==", 1);
  cmp_ok(raid_lv, "==", 1);
  is(vol[0], "==", "./a");
  is(vol[1], "==", "./b");
  //  ok(test_init());
  ok(test_create());
  ok(test_open());
  ok(test_write());
  ok(test_release());
  ok(test_mkdir());
  ok(test_opendir());
  ok(test_readdir());
  ok(test_releasedir());
  return 0;
}
