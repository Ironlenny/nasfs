#include <stdbool.h>
#include <lmdb.h>

int meta_open(const char *, unsigned long, bool, MDB_env **, MDB_dbi *);
void meta_close();
void meta_get();
void meta_put();
void meta_lock();
void meta_unlock();
