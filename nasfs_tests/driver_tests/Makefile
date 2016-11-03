test: test_meta_db.c ../../nasfs_driver/meta_db.c
	if [ -e meta_db ]; then rm -r meta_db; fi;

	clang -Wextra -W -Wall test_meta_db.c ../../nasfs_driver/meta_db.c -l tap -l lmdb -g -o test
