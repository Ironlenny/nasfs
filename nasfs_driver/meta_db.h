#include <db.h>
#include <stdbool.h>

int meta_open(const char *, const char, bool);
void meta_close();
void meta_get();
void meta_put();
void meta_lock();
void meta_unlock();
