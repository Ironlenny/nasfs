#include "meta_db.h"
#include <stdbool.h>
#include <lmdb.h>
#include <stdio.h>

int error_rpt( int rc )
{
  if(rc)
    {
      fprintf(stderr, "mdb_dbi_open: (%d) %s\n", rc, mdb_strerror(rc));
      return rc;
    }

  return 0;
}

int meta_open(const char *file, unsigned long db_id, bool create, MDB_env **env,
              MDB_dbi *dbi, int meta_max_db, MDB_txn *txn)
{
  int rc = 0;
  const int buff_size = 11;
  char buff[buff_size];
  char *name = NULL;

  if (db_id != 0)
    {
      snprintf(buff, buff_size, "%lu", db_id);
      name = buff;
    }

  error_rpt(mdb_env_create(env));
  error_rpt(mdb_env_set_maxdbs(*env, meta_max_db));
  error_rpt(mdb_env_open(*env, file, 0, 0644));
  error_rpt(mdb_txn_begin(*env, NULL, 0, &txn));

  if (create == true)
    rc = mdb_dbi_open(txn, name, MDB_CREATE,  dbi);
  else
    rc = mdb_dbi_open(txn, name, 0, dbi);

  if (rc)
    {
      error_rpt(rc);
      meta_close(env, dbi);
      return rc;
    }
  mdb_txn_commit(txn);

  return 0;
}

int meta_get(MDB_env **env, MDB_dbi *dbi, char *meta_key, char *meta_value)
{
  MDB_val key, value;
  key.mv_size = sizeof(meta_key);
  key.mv_data = meta_key;

  error_rpt(mdb_txn_begin(*env, NULL, 0, &txn));
  rc = mdb_get(txn, *dbi, &key, &value);
  mdb_txn_abort(txn);
  meta_value = value.mv_data;

  return error_rpt(rc);
}

int meta_put(MDB_env **env, MDB_dbi *dbi, char *meta_key, char *meta_value)
{
  MDB_val key, value;
  key.mv_size = sizeof(*meta_key);
  key.mv_data = meta_key;
  value.mv_size = sizeof(*meta_value);
  value.mv_data = meta_value;

  error_rpt(mdb_txn_begin(*env, NULL, 0, &txn));
  error_rpt(mdb_put(txn, *dbi, &key, &value, 0));

  return error_rpt(mdb_txn_commit(txn));
}
