#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <errno.h>
#include <bson.h>
#include "meta_db.h"
#include "stdbool.h"

static const bson_t *super_block;
static char **vol;
static int max_dir = 0;
static int raid_lv = 0;
static bson_error_t bson_error;
static bson_iter_t iter;

static int nas_initalize(const char *path)
{
bson_reader_t *reader = bson_reader_new_from_file(path, &bson_error);
super_block = bson_reader_read(reader, NULL);
bson_iter_init(&iter, super_block);

bson_iter_find(&iter, "max_dir");
max_dir = bson_iter_int32(&iter);

bson_iter_find(&iter, "raid_lv");
raid_lv = bson_iter_int32(&iter);

bson_iter_find(&iter, "vol");
*vol = bson_iter_array(&iter);

return 0;
}

static void *nas_init(struct fuse_conn_info *conn)
{
  (void) conn;
  return NULL;
}

static int nas_getattr()
{
  return -ENOSYS;
}

static int nas_access()
{
  return -ENOSYS;
}

static int nas_readlink()
{
  return -ENOSYS;
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

static int nas_mknod()
{
  return -ENOSYS;
}

static int nas_mkdir()
{
  return -ENOSYS;
}

static int nas_symlink()
{
  return -ENOSYS;
}

static int nas_unlink()
{
  return -ENOSYS;
}

static int nas_rmdir()
{
  return -ENOSYS;
}

static int nas_rename()
{
  return -ENOSYS;
}

static int nas_link()
{
  return -ENOSYS;
}

static int nas_chmod()
{
  return -ENOSYS;
}

static int nas_chown()
{
  return -ENOSYS;
}

static int nas_truncate()
{
  return -ENOSYS;
}

static int nas_utimens()
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

static int nas_read_buf()
{
  return -ENOSYS;
}

static int nas_write()
{
  return -ENOSYS;
}

static int nas_write_buf()
{
  return -ENOSYS;
}

static int nas_statfs()
{
  return -ENOSYS;
}

static int nas_flush()
{
  return -ENOSYS;
}

static int nas_release()
{
  return -ENOSYS;
}

static int nas_fsync()
{
  return -ENOSYS;
}

static int nas_fallocate()
{
  return -ENOSYS;
}

static int nas_setxattr()
{
  return -ENOSYS;
}

static int nas_getxattr()
{
  return -ENOSYS;
}

static int nas_listxattr()
{
  return -ENOSYS;
}

static int nas_removexattr()
{
  return -ENOSYS;
}

static int nas_lock()
{
  return -ENOSYS;
}

static int nas_flock()
{
  return -ENOSYS;
}

 static struct fuse_operations nas_oper = {
	.init           = nas_init,
	.getattr	= nas_getattr,
	.access		= nas_access,
	.readlink	= nas_readlink,
	.opendir	= nas_opendir,
	.readdir	= nas_readdir,
	.releasedir	= nas_releasedir,
	.mknod		= nas_mknod,
	.mkdir		= nas_mkdir,
	.symlink	= nas_symlink,
	.unlink		= nas_unlink,
	.rmdir		= nas_rmdir,
	.rename		= nas_rename,
	.link		= nas_link,
	.chmod		= nas_chmod,
	.chown		= nas_chown,
	.truncate	= nas_truncate,
#ifdef HAVE_UTIMENSAT
	.utimens	= nas_utimens,
#endif
	.create		= nas_create,
	.open		= nas_open,
	.read		= nas_read,
	.read_buf	= nas_read_buf,
	.write		= nas_write,
	.write_buf	= nas_write_buf,
	.statfs		= nas_statfs,
	.flush		= nas_flush,
	.release	= nas_release,
	.fsync		= nas_fsync,
#ifdef HAVE_POSIX_FALLOCATE
	.fallocate	= nas_fallocate,
#endif
#ifdef HAVE_SETXATTR
	.setxattr	= nas_setxattr,
	.getxattr	= nas_getxattr,
	.listxattr	= nas_listxattr,
	.removexattr	= nas_removexattr,
#endif
#ifdef HAVE_LIBULOCKMGR
	.lock		= nas_lock,
#endif
.flock		= nas_flock,
};
