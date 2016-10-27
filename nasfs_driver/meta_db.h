#include <stdbool.h>
#include <lmdb.h>

int meta_open(const char *, unsigned long, bool, MDB_env **, MDB_dbi *, int);
void meta_close(MDB_env **, MDB_dbi *);
int meta_get(MDB_env **, MDB_dbi *, char *, char *);
int meta_put(MDB_env **, MDB_dbi *, char *, char *);
