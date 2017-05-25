import pytest
import sys
sys.path.append ("../../nasfs_utils/")
import fs_man
import os
import shutil
import msgpack
import time
import math

super_file = 'super_block'
meta_root = 'root'
raid_lv = 1
dev = [b'/dev/sda1']
super_dict = {b'vol': dev, b'raid_lv': raid_lv}
mount = './'
uid = 1
gid = 1
perm = 772
ctime = math.trunc(time.time())

def _open_mp_file(path):
    file = open(path, 'rb')
    return msgpack.loads(file.read())

def _cleanup():
    if os.path.isfile(super_file):
        os.remove(super_file)
    if os.path.isfile(meta_root):
        os.remove(meta_root)

def test_create_super_file():
    _cleanup()
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raid_lv, uid, gid, perm, ctime)
    msgpack_dict = _open_mp_file(super_file)
    assert super_dict == msgpack_dict
    test_rec = [b'root', True, uid, gid, perm, ctime, 0, []]
    assert test_rec == _open_mp_file(meta_root)
def test_add_volume():
    _cleanup()
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raid_lv, uid, gid, perm, ctime)
    test_dict = super_dict
    vol = b'/dev/sdb1'
    test_dict[b'vol'].append(vol)
    test_obj.add_vol(mount, vol)
    msgpack_dict = _open_mp_file(super_file)
    assert test_dict == msgpack_dict

def test_cleanup():
    _cleanup()
