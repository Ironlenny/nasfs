#include <fuse.h>
#include <errno.h>
#include <bson.h>

#define FUSE_USE_VERSION 30

bson_reader_t *reader;
bson_t *doc;

int nas_init(char *super_path)
{
  return -ENOSYS;
}

int nas_getattr()
{
  return -ENOSYS;
}

int nas_access()
{
  return -ENOSYS;
}

int nas_readlink()
{
  return -ENOSYS;
}

int nas_opendir()
{
  return -ENOSYS;
}

int nas_readdir()
{
  return -ENOSYS;
}

int nas_releasedir()
{
  return -ENOSYS;
}

int nas_mknod()
{
  return -ENOSYS;
}

int nas_mkdir()
{
  return -ENOSYS;
}

int nas_symlink()
{
  return -ENOSYS;
}

int nas_unlink()
{
  return -ENOSYS;
}

int nas_rmdir()
{
  return -ENOSYS;
}

int nas_rename()
{
  return -ENOSYS;
}

int nas_link()
{
  return -ENOSYS;
}

int nas_chmod()
{
  return -ENOSYS;
}

int nas_chown()
{
  return -ENOSYS;
}

int nas_truncate()
{
  return -ENOSYS;
}

int nas_utimens()
{
  return -ENOSYS;
}

int nas_create()
{
  return -ENOSYS;
}

int nas_open()
{
  return -ENOSYS;
}

int nas_read()
{
  return -ENOSYS;
}

int nas_read_buf()
{
  return -ENOSYS;
}

int nas_write()
{
  return -ENOSYS;
}

int nas_write_buf()
{
  return -ENOSYS;
}

int nas_statfs()
{
  return -ENOSYS;
}

int nas_flush()
{
  return -ENOSYS;
}

int nas_release()
{
  return -ENOSYS;
}

int nas_fsync()
{
  return -ENOSYS;
}

int nas_fallocate()
{
  return -ENOSYS;
}

int nas_setxattr()
{
  return -ENOSYS;
}

int nas_getxattr()
{
  return -ENOSYS;
}

int nas_listxattr()
{
  return -ENOSYS;
}

int nas_removexattr()
{
  return -ENOSYS;
}

int nas_lock()
{
  return -ENOSYS;
}

int nas_flock()
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
