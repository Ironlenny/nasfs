#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <stdbool.h>
#inlcude "sds.h"
#include "mpack.h"

/* TODO
   All strings should be UTF8
*/

static mpack_reader_t reader;
static int max_name_len = 256 * sizeof(char);
static const char *vol[10];
static const int array_size = 7;
static const int hash_size = 160; /* Size of hash string */
typedef static struct inode
{
  sds name;
  bool dir;
  int64 uid;
  int64 gid;
  int8 perm;
  int64 atime;
  int32 dir_size;
  sds *contents_array;
}

/* Schema: */
/* [ */
/*  Field 1: 'name' string 256 characters */
/*  Field 2: 'dir' bool */
/*  Field 3: 'uid' uint64 */
/*  Field 4: 'gid' uint64 */
/*  Field 5: 'perm' uint8 */
/*  Field 6: 'atime' uint64 */
/*  Field 7: 'dir size' uint32; number of entries */
/*  Field 7: 'contains' array of strings; entries */
/*  ] */
static inode *mp_load(sds *path)
{
  mpack_reader_init_file(&reader, path);
  inode *new_node = malloc(sizeof(inode));
  mpack_expect_array_match(&reader, 7);
  new_node->name = sdsempty();
  new_node->name = sdsgrowzero(name, max_name_len);
  new_node->name = mpack_expect_cstr(&reader, name, sizeof(&new_node->name));

  new_node->dir = mpack_expect_bool(&reader);
  new_node->uid = mpack_expect_u64(&reader);
  new_node->gid = mpack_expect_u64(&reader);
  new_node->perm = mpack_expect_u8(&reader);
  new_node->atime = mpack_expect_u64(&reader);
  new_node->dir_size = mpack_expect_u32(&reader);

  mpack_expect_array_match(&reader, new_node->dir_size);
  new_node->contains = malloc(dir_size * sizeof(sds *));
  for (int i = 0; i < dir_size; i++)
    {
      new_node->contains[i] = sdsnew(mpack_expect_cstr
                                     (&reader, new_node->contains[i],
                                      hash_size * sizeof(char) ));
    }
  mpack_array_done();
  mpack_array_done();

  return new_node;
}

static int nas_initalize(const char *path)
{
 
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
