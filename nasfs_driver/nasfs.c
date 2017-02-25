#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "mpack.h"

static mpack_reader_t reader;
static const char *vol[10];
typedef struct Path
{
  int len;
  char *str;
  char *tail;
} Path;

/*   static unsigned long get_parent_id_(int path_len, char *path, */
/*                                       unsigned long in_id) */
/* { */
/*   char *tmp = NULL; */
/*   unsigned long id = 0; */
/*   int tmp_len = 0; */
/*     meta_open(db_path, in_id, false, max_dir); */
/*   if (meta_get(path, &tmp) == 0) */
/*     { */
/*       id = strtoul(tmp, NULL, 10); */
/*     } */

/*   if (path_len > 0) */
/*     { */
/*       tmp_len = strlen(path); */
/*       path_len = tmp_len - strlen(path); */
/*       path = path + tmp_len + 1; */
/*       get_parent_id_(path_len, path, id); */
/*     } */

/*   return id ; */
/* } */

/* Schema: */
/* [ */
/*  Field 1: 'contains' array of strings */
/*  Field 2: 'uid' int */
/*  Field 3: 'gid' int */
/*  Field 4: 'permisions' int */
/*  Field 5: 'atime' int */
/*  Field 6: 'directory' bool */
/*  ] */
static void mp_validate(mpack_reader_t *reader, char *path)
{

  reader_init_file(reader, path);

}

static void tokenize(Path *path)
{
  const char delim[] = "/";
  char *token = strtok (path->str, delim);

  while (token != NULL)
    {
      path->tail = token;
      token = strtok (NULL, delim);
    }
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

static int nas_opendir(const char *path, struct fuse_file_info *file_handle)
{
  return 0;
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
  bson_t *record;
  char *rec_tmp = NULL;
  char *id_tmp = malloc(sizeof(unsigned long));
  unsigned long parent_id = 0;
  Path new_dir;
  new_dir.len = strlen(path);

  strncpy(new_dir.str, path, new_dir.len * sizeof(char));
  tokenize(&new_dir);

  parent_id = get_parent_id_(new_dir.len, new_dir.str, parent_id);

  snprintf(id_tmp, sizeof(unsigned long), "%lu", db_next_id);
  meta_open(db_path, parent_id, false, max_dir);
  meta_put(new_dir.tail, id_tmp);
  meta_close();
  meta_open(db_path, db_next_id, true, max_dir);
  record = BCON_NEW("contains", "[", ".", "..", "]", "perm", BCON_INT32(mode),
                    "dir", BCON_BOOL(true));
  rec_tmp = bson_as_json(record, NULL);
  meta_put("self", rec_tmp);
  meta_close();
  db_next_id = ++db_count;

  free(id_tmp);
  bson_destroy(record);

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
