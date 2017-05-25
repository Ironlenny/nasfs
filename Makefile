bin = bin
scripts = $(bin)/test_all.sh $(bin)/setup.py
driver = nasfs_driver
lib = lib
driver_tests = nasfs_tests/driver_tests
test_scripts = nasfs_tests/scripts
all: tests

tests: $(bin)/test_fs $(scripts)

clean:
	rm -rf $(bin)

# '-D_FILE_OFFSET_BITS=64' is required by FUSE
$(bin)/test_fs: $(driver_tests)/test_nasfs.c $(driver)/nasfs.c $(lib)/mpack.c \
	$(lib)/sds.c

	mkdir -p $(@D)
	clang -D_FILE_OFFSET_BITS=64 -Wextra -Wall $(driver_tests)/test_nasfs.c
	$(driver)/nasfs.c $(lib)/sds.c $(lib)/mpack.c  -l tap -g \
	-Wno-error=unused-function -Wno-error=macro-redefined -o $@


$(scripts): \
$(bin)/%: $(test_scripts)/%
	cp $< $(bin)/
	chmod +x $(bin)/$(<F)
