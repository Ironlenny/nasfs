#include <stdbool.h>
#include <lmdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static MDB_txn *txn = NULL;
static int rc = 0;
static MDB_env *env = NULL;
static MDB_dbi dbi;
static MDB_val key, value;

int error_rpt( int rc )
{
  if(rc)
    {
      fprintf(stderr, "error: (%d) %s\n", rc, mdb_strerror(rc));
      return rc;
    }

  return 0;
}

void meta_close()
{
  mdb_close(env, dbi);
  mdb_env_close(env);
  env = NULL;
}

int meta_open(const char *file, unsigned long db_id, bool create,
              int meta_max_db)
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

  if (env == NULL)
    {
      error_rpt(mdb_env_create(&env));
      error_rpt(mdb_env_set_maxdbs(env, meta_max_db));
      error_rpt(mdb_env_open(env, file, 0, 0644));
    }

  error_rpt(mdb_txn_begin(env, NULL, 0, &txn));

  if (create == true)
    rc = mdb_dbi_open(txn, name, MDB_CREATE,  &dbi);
  else
    rc = mdb_dbi_open(txn, name, 0, &dbi);

  if (rc)
    {
      error_rpt(rc);
      meta_close();
      return rc;
    }
  mdb_txn_commit(txn);

  return 0;
}

int meta_get( char *meta_key, char **meta_value)
{
  key.mv_size = sizeof(meta_key);
  key.mv_data = meta_key;

  error_rpt(mdb_txn_begin(env, NULL, 0, &txn));
  rc = mdb_get(txn, dbi, &key, &value);
  mdb_txn_abort(txn);
  *meta_value = strdup(value.mv_data);

  return error_rpt(rc);
}

int meta_put(char *meta_key, char *meta_input)
{
  key.mv_size = sizeof(meta_key);
  key.mv_data = meta_key;
  value.mv_size = sizeof(meta_input);
  value.mv_data = meta_input;

  error_rpt(mdb_txn_begin(env, NULL, 0, &txn));
  error_rpt(mdb_put(txn, dbi, &key, &value, 0));

  return error_rpt(mdb_txn_commit(txn));
}

int meta_get_keys(char ***all_keys, char ***all_values, int db_id, char *meta_db)
{
  MDB_cursor *cursor;
  MDB_stat stat;
  meta_open(meta_db, db_id, false, 0);
  error_rpt(mdb_txn_begin(env, NULL, 0, &txn));
  error_rpt(mdb_stat(txn, dbi, &stat));
  size_t db_size = stat.ms_entries;
  int arr_size = db_size * sizeof(char *);
  size_t count = 1;

  mdb_cursor_open(txn, dbi, &cursor);
  *all_keys = malloc(arr_size);
  *all_values = malloc(arr_size);
  mdb_cursor_get(cursor, &key, &value, MDB_FIRST);
  (*all_keys)[0] = strdup(key.mv_data);
  (*all_values)[0] = strdup(value.mv_data);

  while (mdb_cursor_get(cursor, &key, &value, MDB_NEXT) == 0)
    {
      assert(count < db_size);
      (*all_keys)[count] = strdup(key.mv_data);
      (*all_values)[count] = strdup(value.mv_data);
      count++;
    }

  mdb_cursor_close(cursor);
  mdb_txn_abort(txn);

  return 0;
}
