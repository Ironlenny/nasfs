bin = ../../bin
scripts = $(bin)/test_all.sh $(bin)/setup.py
tests: $(bin)/test_fs $(scripts)
driver = ../../nasfs_driver

clean:
	rm -rf $(bin)

# '-D_FILE_OFFSET_BITS=64' is required by FUSE
$(bin)/test_fs: test_nasfs.c $(driver)/nasfs.c $(driver)/mpack.c $(driver)/sds.c
	mkdir -p $(@D)
	clang -D_FILE_OFFSET_BITS=64 -Wextra -Wall test_nasfs.c $(driver)/nasfs.c \
	$(driver)/sds.c $(driver)/mpack.c  -l tap -g -Wno-error=unused-function \
	-Wno-error=macro-redefined -o $@


$(scripts): \
$(bin)/%: %
	cp $< $(bin)/
	chmod +x $(bin)/$<
