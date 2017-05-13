#!/usr/bin/python3
import msgpack
import ctypes

class FSMan():

    def __init__(self):
        self._super_block = 'super_block'
        self._meta_root = 'root'

    def create_fs(self, vol, raidLv, uid, gid, perm, ctime):
        # Schema:
        # [
        #  Field 1: 'name' string 256 characters
        #  Field 2: 'dir' bool
        #  Field 3: 'uid' uint64
        #  Field 4: 'gid' uint64
        #  Field 5: 'perm' uint8
        #  Field 6: 'ctime' uint64
        #  Field 7: 'dir_size' uint32; number of entries
        #  Field 7: 'contents_a' array of strings; entries
        #  ]
        root_rec = ['root', True, ctypes.c_uint64(uid), ctypes.c_uint64(gid),
                    ctypes.c_uint8(perm), ctypes.c_uint64(ctime),
                    ctypes.c_uint32(0), []]
        file = open(self._super_block, 'bx')
        file.write(msgpack.packb({"vol":vol, "raid_lv":raidLv}))
        file.close()
        file = open(self._meta_root, 'bx')
        file.write(msgpack.packb(root_rec))
        file.close()

    def add_vol(self, mount, vol):
        file = open( mount + self._super_block, 'br+')
        data = msgpack.unpackb(file.read())
        data[b'vol'].append(vol)
        file.seek(0)
        file.write(msgpack.packb(data))
        file.close()

    def remove_vol(self, mount, vol):
        return

    def balance_fs(self, mount):
        return
