#!/usr/bin/python3
import pdb
import bson # Do not use debian version. Use https://github.com/py-bson/bson
import lmdb

class FSMan():

    def __init__(self):
        self._db_name = 'meta_db'
        self._super_file = 'super_file'
        self.db = lmdb.open(self._db_name)

    def create_fs(self, vol, raidLv, uid, gid, perm, max_dir):
        root_rec = {'contains': ['.', '..'], 'uid': uid, 'gid': gid,\
                     'perm': perm, 'atime': None, 'dir': True}
        file = open(self._super_file, 'bx')
        file.write(bson.dumps({"vol":vol, "raid":raidLv, "max_dir":max_dir}))
        file.close()

        with self.db.begin(write=True) as txn:
            txn.put(b'self', bson.dumps(root_rec))

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
