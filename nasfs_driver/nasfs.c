#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <bson.h>
#include "meta_db.h"
#include <stdbool.h>
#include <string.h>


static const char *vol[10];
static int max_dir = 0;
static int raid_lv = 0;
static bson_error_t bson_error;
static bson_iter_t iter;
static bson_iter_t sub_iter;
static unsigned long db_count = 1;
static unsigned long db_next_id = 1;
static char db_path[] = "./meta_db";

static unsigned long get_parent_id_(int index, char *lst_tmp[],
                                    unsigned long in_id)
{
  char *tmp = NULL;
  unsigned long id = 0;
    meta_open(db_path, in_id, false, max_dir);
  if (meta_get(lst_tmp[index], &tmp) == 0)
    {
      id = strtoul(tmp, NULL, 10);
    }

  if (id != 0)
    {
      get_parent_id_(index++, lst_tmp, id);
    }

  return id ;
}

static int nas_initalize(const char *path)
{
  static const bson_t *super_block;
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
  char *lst_tmp[100];
  const char delim[] = "/";
  int path_len = 0;
    int count = 0;
  bson_t *record;
  char *rec_tmp = NULL;
  char *id_tmp = malloc(sizeof(unsigned long));
  unsigned long parent_id = 0;
  path_len = strlen(path);
  char tmp[path_len];
  char *token = strtok (tmp, delim);

  strncpy(tmp, path, path_len);

  while (token != NULL)
    {
      lst_tmp[count] = token;

      token = strtok (NULL, delim);

      if(token != NULL)
        {
          count++;
        }
    }

  parent_id = get_parent_id_(parent_id, lst_tmp, parent_id);

  snprintf(id_tmp, sizeof(unsigned long), "%lu", db_next_id);
  meta_open(db_path, parent_id, false, max_dir);
  meta_put(lst_tmp[parent_id], id_tmp);
  meta_close();
  meta_open(db_path, db_next_id, true, max_dir);
  record = BCON_NEW("contains", "[", ".", "..", "]", "perm", BCON_INT32(mode),
                    "dir", BCON_BOOL(true));
  rec_tmp = bson_as_json(record, NULL);
  meta_put("self", rec_tmp);
  meta_close();
  db_next_id = ++db_count;

  return 0;
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
