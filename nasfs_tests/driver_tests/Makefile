bin=../../bin
bson_loc=$(shell pkg-config --cflags --libs libbson-1.0)

test: test_fs test_meta
	if [ -e $(bin)/test_all.sh ]; then rm $(bin)/test_all.sh; fi;
	cp test_all.sh $(bin)/

clean:
	if [ -e $(bin) ]; rm -rf $(bin); fi;

test_meta: test_meta_db.c ../../nasfs_driver/meta_db.c

	clang -Wextra -W -Wall test_meta_db.c ../../nasfs_driver/meta_db.c -l tap -l lmdb -g -o $(bin)/test_meta

test_fs: test_nasfs.c ../../nasfs_driver/nasfs.c
	clang -D_FILE_OFFSET_BITS=64 -Wextra -W -Wall test_nasfs.c ../../nasfs_driver/nasfs.c $(bson_loc) -l tap -l lmdb -g -o $(bin)/test_fs -Wno-error=unused-function -Wno-error=macro-redefined

