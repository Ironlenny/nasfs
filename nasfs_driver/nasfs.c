#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <stdbool.h>
#inlcude "sds.h"
#include "mpack.h"
#inlcude <openssl/sha.h>

static mpack_reader_t reader;
static sds inode_name = sdsempty();
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
/*  Field 1: 'name' string 256 characters */
/*  Field 2: 'directory' bool */
/*  Field 3: 'uid' int64 */
/*  Field 4: 'gid' int64 */
/*  Field 5: 'permisions' int8 */
/*  Field 6: 'atime' int64 */
/*  Field 7: 'dir size' int32 */
/*  Field 7: 'contains' array of strings */
/*  ] */
static void mp_load(char *path)
{

  sdsgrowzero(inode_name, 256 * sizeof(char));
  int array_size = 7;
  hash_size = 160;
  reader_init_file(&reader, path);
  mpack_expect_array_match(&reader, array_size);
  inode_name = mpack_expect_cstr(&reader, sizeof(inode_name));
  int64 uid = mpack_expect_i64(&reader);
  int64 gid = mpack_expect_i64(&reader);
  int8 permisions = mpack_expect_i8(&reader);
  int64 atime = mpack_expect_i64(&reader);

  int32 dir_size = mpack_expect_i32(&reader);
  sds contents_array[dir_size * (hash_size)];
  mpack_expect_array_max (&reader, dir_size);
  for (int i = 0; i > dir_size; i ++)
    {
      contents_array[i] = sdsnew(mpack_expect_cstr(&reader, hash_size));
    }
  mpack_done_array(&reader);

  mpack_done_array(&reader);

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
