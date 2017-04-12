#include <tap.h>
#include "../../nasfs_driver/nasfs.c"
#include <fuse.h>
#include <bson.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdlib.h>

static char super_path[] = "./super_block";

int test_mp_load(char *path)
{
  inode *node = mp_load(path);
  isOk
}

int main(int argc, const char *argv[])
{
  printf("nasfs.c tests:\n");
  plan(NO_PLAN);

  return 0;
}
