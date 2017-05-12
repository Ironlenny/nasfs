#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <stdbool.h>
#include "sds.h"
#include "mpack.h"

/* TODO
   All strings should be UTF8
*/

static mpack_reader_t reader;
static int max_name_len = 256 * sizeof(char);
static const char *vol[10];
static const int array_size = 7;
static const int hash_size = 160; /* Size of hash string */
typedef struct
{
  sds name;
  bool dir;
  unsigned long long int uid;
  unsigned long long int gid;
  unsigned char perm;
  unsigned long long int ctime;
  unsigned int dir_size;
  sds *contents_a;
} Inode;

/* Schema: */
/* [ */
/*  Field 1: 'name' string 256 characters */
/*  Field 2: 'dir' bool */
/*  Field 3: 'uid' uint64 */
/*  Field 4: 'gid' uint64 */
/*  Field 5: 'perm' uint8 */
/*  Field 6: 'ctime' uint64 */
/*  Field 7: 'dir size' uint32; number of entries */
/*  Field 7: 'contents' array of strings; entries */
/*  ] */
static Inode *mp_load(char *path)
{
  mpack_error_t error;

  mpack_reader_init_file(&reader, path);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  Inode *new_node = malloc(sizeof(Inode));
  mpack_expect_array_match(&reader, 8);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }
  new_node->name = sdsempty();
  new_node->name = sdsgrowzero(new_node->name, max_name_len);
  mpack_expect_utf8_cstr(&reader, new_node->name, sdslen(new_node->name));
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->dir = mpack_expect_bool(&reader);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->uid = mpack_expect_u64(&reader);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->gid = mpack_expect_u64(&reader);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->perm = mpack_expect_u8(&reader);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->ctime = mpack_expect_u64(&reader);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->dir_size = mpack_expect_u32(&reader);
  error = mpack_reader_flag_if_error (&reader, error);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  mpack_expect_array_match(&reader, new_node->dir_size);
  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  new_node->contents_a = malloc(new_node->dir_size * sizeof(sds *));
  for (unsigned int i = 0; i < new_node->dir_size; i++)
    {
      new_node->contents_a[i] = sdsempty();
      new_node->contents_a[i] = sdsgrowzero(new_node->contents_a[i],
                                            hash_size * sizeof(char));
      mpack_expect_cstr(&reader, new_node->contents_a[i],
                        hash_size * sizeof(char));
    }

  if (error != mpack_ok) {
    fprintf(stderr, "Error %i occurred reading data!\n", (int)error);
  }

  mpack_done_array(&reader);
  mpack_done_array(&reader);

  return new_node;
}

static int nas_initalize(const char *path)
{
  return -ENOSYS;
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
  return -ENOSYS;
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
