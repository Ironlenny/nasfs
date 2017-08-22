#include <tap.h> /* https://github.com/zorgnax/libtap */
#include "../../src/nasfs.c"
#include "../../lib/mpack.h"
#include <fuse.h>
#include <stdlib.h>
#include "../../lib/sds.h"

static char super_path[] = "./test_super";
char root_path[] = "./test_root";
Inode *node = NULL;

void test_nas_init()
{
  printf("Initialize the file system\n");
  if (cmp_ok(nas_initalize(super_path), "==", 0, "File system initialized"))
    {
      cmp_ok(raid_lv, "==", 1, "Raid level set to 1");
      is(vol[0], "./a", "'a' is the first volume");
      is(vol[1], "./b", "'b' is the second volume");
    }
}

void test_mp_load(char *path)
{
  printf("Try to load MessagePack file and create inode:\n");
  cmp_ok(mp_load(path, &node), "==" , 0 , "inode created");
  if (node != NULL)
    {
      is(node->name, "root" , "Node is named root");
      cmp_ok(node->dir, "==" , true , "Node is a directory");
      cmp_ok(node->uid, "==" , 1 , "uid is 1");
      cmp_ok(node->dir_size, "==", 4, "dir_size is 4");
      cmp_ok(node->perm, "==", 777, "perm is 777");
      cmp_ok(node->ctime, "==", 1494872263, "ctime is 1494872263");
      for (int i = 0; i < node->dir_size; i++)
        {
          sds string = sdsnew("foo");
          string = sdscat(string, sdsfromlonglong(i));
          is(node->contents_a[i], string,  "Contents match");
          sdsfree(string);
        }
    }
}


void test_mp_store()
{
  printf("Try to write inode to file:\n");
  if(node == NULL)
    {
      fail("Cannot store in file. 'node' is NULL");
      return;
    }
  cmp_ok(mp_store(node, root_path), "==", 0, "Store successful");
  cmp_ok(mp_load(root_path, &node), "==", 0, "Load successful");
}

int main(int argc, const char *argv[])
{
  printf("nasfs.c tests:\n");
  plan(NO_PLAN);
  test_nas_init();
  test_mp_load(root_path);
  test_mp_store();
  cmp_ok(nas_mkdir("foo", 0777), "==", 0, "Made directory 'foo'");
  cmp_ok(nas_rmdir("foo"), "==", 0, "Removed directory 'foo'");
  return 0;
}
