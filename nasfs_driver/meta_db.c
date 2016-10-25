#include "meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <stdio.h>

int meta_max_dbs = 0;

int meta_open(const char *file, unsigned long db_name, bool create,
              MDB_env **env, MDB_dbi *dbi)
{
  int rc = 0;
  const int buff_size = 11;
  char buff[buff_size];
  char *name = NULL;
  MDB_txn *txn = NULL;

  if (db_name != 0)
    {
      snprintf(buff, buff_size, "%lu", db_name);
      name = buff;
    }

  rc = mdb_env_create(env);
  rc = mdb_env_set_maxdbs(*env, meta_max_dbs);
  rc = mdb_env_open(*env, file, 0, 0644);
  rc = mdb_txn_begin(*env, NULL, 0, &txn);
  if (create == true)
    rc = mdb_dbi_open(txn, name, MDB_CREATE, dbi);

  rc = mdb_dbi_open(txn, name, 0, dbi);

  return rc;
}

void meta_close( MDB_env **env, MDB_dbi *dbi)
{
  mdb_close(*env, *dbi);
  mdb_env_close(*env);
}
