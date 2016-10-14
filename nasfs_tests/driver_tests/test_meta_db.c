#include <tap.h>
#include "../../nasfs_driver/meta_db.h"
#include <stdbool.h>

const char db_file[] = "meta_db";
DB *db;

int main()
{
  plan(NO_PLAN);

  todo();
  ok(meta_open(db_file, '1', true), "Create db file, and root logical db");
  end_todo;
}
