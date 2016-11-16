all: test_fs test_meta
	test_meta
	test_fs

test_meta: test_meta_db.c ../../nasfs_driver/meta_db.c
	if [ -e meta_db ]; then rm -r meta_db; fi;

	clang -Wextra -W -Wall test_meta_db.c ../../nasfs_driver/meta_db.c -l tap -l lmdb -g -o test_meta

test_fs: test_nasfs.c ../../nasfs_driver/nasfs.c
	clang -D_FILE_OFFSET_BITS=64 -Wextra -W -Wall test_nasfs.c ../../nasfs_driver/nasfs.c -l tap -l lmdb -g -o test_fs
