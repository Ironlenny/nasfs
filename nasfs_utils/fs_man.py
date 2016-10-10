#!/usr/bin/python3
# TODO: Disallow duplicates in the database
import bson
import bsddb3

class FSMan():

    def __init__(self):
        self._db_name = "meta_db"
        self._super_file = "super_file"
        self.db = bsddb3.db.DB()

    def create_fs(self, vol, raidLv, uid, gid, perm):
        root_rec = {'contains': ['.', '..'], 'uid': uid, 'gid': gid,\
                     'perm': perm, 'atime': None, 'dir': True}
        file = open(self._super_file, 'bx')
        file.write(bson.dumps({"vol":vol, "raid":raidLv}))
        file.close()

        self.db.open(self._db_name, '1', bsddb3.db.DB_BTREE,\
                bsddb3.db.DB_CREATE)
        self.db.put(b'self', bson.dumps(root_rec))
        self.db.close()

    def add_vol(self, mount, vol):
        file = open( mount + self._super_file, 'br+')
        data = bson.loads(file.read())
        data['vol'].append(vol)
        file.seek(0)
        file.write(bson.dumps(data))
        file.close()

    def remove_vol(self, mount, vol):
        return

    def balance_fs(self, mount):
        return
