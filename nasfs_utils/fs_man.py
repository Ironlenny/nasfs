#!/usr/bin/python3
import pdb
import msgpack


class FSMan():

    def __init__(self):
        self._super_block = 'super_block.mp'
        self._meta_root = 'root.mp'

    def create_fs(self, vol, raidLv, uid, gid, perm):
        # Schema:
        # [
        # Field 1: 'contains' array of strings
        # Field 2: 'uid' int
        # Field 3: 'gid' int
        # Field 4: 'permisions' int
        # Field 5: 'atime' int
        # Field 6: 'directory' bool
        # ]
        root_rec = [['.', '..'], uid, gid, perm, None, True]
        file = open(self._super_block, 'bx')
        file.write(msgpack.dumps({"vol":vol, "raid_lv":raidLv}))
        file.close()
        file = open(self._meta_root, 'bx')
        file.write(msgpack.dumps(root_rec))
        file.close()

    def add_vol(self, mount, vol):
        file = open( mount + self._super_block, 'br+')
        data = msgpack.loads(file.read())
        data[b'vol'].append(vol)
        file.seek(0)
        file.write(msgpack.dumps(data))
        file.close()

    def remove_vol(self, mount, vol):
        return

    def balance_fs(self, mount):
        return
