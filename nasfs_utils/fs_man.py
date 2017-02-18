#!/usr/bin/python3
import pdb
import msgpack


class FSMan():

    def __init__(self):
        self._super_block = 'super_block'

    def create_fs(self, vol, raidLv, uid, gid, perm):
        root_rec = {'contains': ['.', '..'], 'uid': uid, 'gid': gid,\
                     'perm': perm, 'atime': None, 'dir': True}
        file = open(self._super_block, 'bx')
        file.write(msgpack.dumps({"vol":vol, "raid_lv":raidLv}))
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
