#include <tap.h> /* https://github.com/zorgnax/libtap */
#include "../../nasfs_driver/nasfs.c"
#include "../../lib/mpack.h"
#include <fuse.h>
#include <stdlib.h>
#include "../../lib/sds.h"

static char super_path[] = "./super_block";
static char root_path[] = "./test_root";

void test_mp_load(char *path)
{
  Inode *node = NULL;
  char *test_contents[2];
  cmp_ok(node = mp_load(path), "!=" , NULL , "inode created");
  if (node != NULL)
    {
      is(node->name, "root" , "Node is named root");
      cmp_ok(node->dir, "==" , true , "Node is a directory");
      cmp_ok(node->uid, "==" , 1 , "uid is 1");
      cmp_ok(node->dir_size, "==", 4, "dir_size is 4");
      for (int i = 0; i < node->dir_size; i++)
        {
          sds string = sdsnew("foo");
          string = sdscat(string, sdsfromlonglong(i));
          is(node->contents_a[i], string,  "Contents match");
          sdsfree(string);
        }
    }
}

int main(int argc, const char *argv[])
{
  printf("nasfs.c tests:\n");
  plan(NO_PLAN);
  test_mp_load(root_path);

  return 0;
}

