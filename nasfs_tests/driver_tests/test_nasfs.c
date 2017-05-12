#include <tap.h> /* https://github.com/zorgnax/libtap */
#include "../../nasfs_driver/nasfs.c"
#include "../../nasfs_driver/mpack.h"
#include <fuse.h>
#include <stdlib.h>

static char super_path[] = "./super_block";
static char root_path[] = "./root";

void test_mp_load(char *path)
{
  Inode *node;
  char *test_contents[2];
  test_contents[0] = ".";
  test_contents[1] = "..";
  cmp_ok(node = mp_load(path), "!=" , NULL , "inode created");
  is(node->name, "root" , "Node is named root");
  cmp_ok(node->dir, "==" , true , "Node is a directory");
  cmp_ok(node->uid, "==" , 1 , "uid is 1");
}

int main(int argc, const char *argv[])
{
  printf("nasfs.c tests:\n");
  plan(NO_PLAN);
  test_mp_load(root_path);

  return 0;
}
