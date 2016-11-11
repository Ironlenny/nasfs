#include <stdbool.h>
#include <lmdb.h>

int meta_open(const char *, unsigned long, bool, int);
void meta_close();
int meta_get(char *, char **);
int meta_put(char *, char *);
int meta_get_keys(char ***, char ***, int, const char*);
void meta_free(char *, char **);
