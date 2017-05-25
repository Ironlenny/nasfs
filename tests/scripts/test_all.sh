#! /bin/sh

rm -rf meta_db/
rm super_block

./setup.py
./test_meta
./test_fs
