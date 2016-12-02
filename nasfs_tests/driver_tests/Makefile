bin=../../bin
bson_loc=$(shell pkg-config --cflags --libs libbson-1.0)

tests: $(bin)/test_fs $(bin)/test_meta $(bin)/test_all.sh

clean:
	rm -rf $(bin)

$(bin)/test_meta: test_meta_db.c ../../nasfs_driver/meta_db.c
	mkdir -p $(@D)
	clang -Wextra -W -Wall test_meta_db.c ../../nasfs_driver/meta_db.c -l tap -l lmdb -g -o $@

$(bin)/test_fs: test_nasfs.c ../../nasfs_driver/nasfs.c ../../nasfs_driver/meta_db.c
	mkdir -p $(@D)
	clang -D_FILE_OFFSET_BITS=64 -Wextra -W -Wall test_nasfs.c ../../nasfs_driver/meta_db.c ../../nasfs_driver/nasfs.c $(bson_loc) -l tap -l lmdb -g -Wno-error=unused-function -Wno-error=macro-redefined -o $@

$(bin)/test_all.sh: test_all.sh
	cp $< $(bin)/
	chmod +x $(bin)/$<
