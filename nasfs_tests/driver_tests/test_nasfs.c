#include <tap.h>
#include "../../nasfs_driver/nasfs.c"
#include <fuse.h>

int test_init()
{
  struct fuse_conn_info conn;
  if (nas_init(&conn) == NULL)
    {
      return 1;
    }

  return 0;
}

int main()
{
  printf("nasfs.c tests:\n");
  plan(NO_PLAN);
  ok(test_init());
  return 0;
}
