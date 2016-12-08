#! /bin/sh

rm -rf meta_db/
rm super_block

mkdir meta_db

./setup.py
./test_meta
./test_fs
