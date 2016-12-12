#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <bson.h>
#include "meta_db.h"
#include <stdbool.h>
#include <string.h>

static const bson_t *super_block;
static const char *vol[10];
static int max_dir = 0;
static int raid_lv = 0;
static bson_error_t bson_error;
static bson_iter_t iter;
static bson_iter_t sub_iter;
static unsigned long db_count = 1;
static unsigned long db_next_id = db_count;
static char db_path[] = "./meta_db"

static int nas_initalize(const char *path)
{
  int error = 0;
  bson_reader_t *reader = bson_reader_new_from_file(path, &bson_error);
  if (!reader) {
    fprintf (stderr, "ERROR: %d.%d: %s\n",
             bson_error.domain, bson_error.code, bson_error.message);
  }
  super_block = bson_reader_read(reader, NULL);

  if(bson_iter_init_find(&iter, super_block, "vol"))
    {
      int count = 0;
      bson_iter_recurse(&iter, &sub_iter);
      while(bson_iter_next(&sub_iter) == true)
        {
          vol[count++] = bson_iter_utf8 (&sub_iter, NULL);
        }
    }
  else
    {
      error = -1;
      bson_reader_destroy(reader);
    }

  if (bson_iter_init_find(&iter, super_block, "max_dir"))
    {
      max_dir = bson_iter_int32(&iter);
    }
  else
    {
      error = -1;
      bson_reader_destroy(reader);
    }

  if (bson_iter_init_find(&iter, super_block, "raid_lv"))
    {
      raid_lv = bson_iter_int32(&iter);
    }
  else
    {
      error = -1;
      bson_reader_destroy(reader);
    }

  bson_reader_destroy(reader);

  return error;
}

static int nas_opendir()
{
  return -ENOSYS;
}

static int nas_readdir()
{
  return -ENOSYS;
}

static int nas_releasedir()
{
  return -ENOSYS;
}

static int nas_mkdir(const char *path, mode_t mode)
{
  char *tmp[100];

  while ()
}

static int nas_rmdir()
{
  return -ENOSYS;
}

static int nas_create()
{
  return -ENOSYS;
}

static int nas_open()
{
  return -ENOSYS;
}

static int nas_read()
{
  return -ENOSYS;
}

static int nas_write()
{
  return -ENOSYS;
}

static int nas_release()
{
  return -ENOSYS;
}

 static struct fuse_operations nas_oper = {
	.opendir	= nas_opendir,
	.readdir	= nas_readdir,
	.releasedir	= nas_releasedir,
	.mkdir		= nas_mkdir,
	.rmdir		= nas_rmdir,
	.create		= nas_create,
	.open		= nas_open,
	.read		= nas_read,
	.write		= nas_write,
	.release	= nas_release,
};
