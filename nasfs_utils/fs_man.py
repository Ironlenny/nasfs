#!/usr/bin/python3

import bson
import bsddb3

class FSMan():

    def __init__(self):
        self._db_name = "meta_db"
        self._super_file = "super_file"

    def create_fs(self, vol, raidLv):
        file = open(self._super_file, 'bx')
        file.write(bson.dumps({"vol":vol, "raid":raidLv}))
        file.close()
        db = bsddb3.db.open(self._db_name, None, bsddb3.db.DB_BTREE,\
                            bsddb3.db.DB_CREATE)
        db.put('root', 'self')
        db.close()

    def add_vol(self, mount, vol):
        return

    def remove_vol(self, mount, vol):
        return

    def balance_fs(self, mount):
        return
