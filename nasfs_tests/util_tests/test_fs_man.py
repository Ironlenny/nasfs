import pytest
import sys
sys.path.append ("../../nasfs_utils/")
import fs_man
import os
import shutil
import msgpack

super_file = 'super_block'
raid_lv = 1
dev = [b'/dev/sda1']
super_dict = {b'vol': dev, b'raid_lv': raid_lv}
mount = './'
uid = b'test'
gid = b'test'
perm = 772

def _open_super_file():
    file = open(super_file, 'rb')
    return msgpack.loads(file.read())

def _cleanup():
    if os.path.isfile(super_file):
        os.remove(super_file)

def test_create_super_file():
    _cleanup()
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raid_lv, uid, gid, perm)
    msgpack_dict = _open_super_file()
    assert super_dict == msgpack_dict
    with pytest.raises(FileExistsError):
        test_obj.create_fs(dev, raid_lv, uid, gid, perm)

def test_add_volume():
    _cleanup()
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raid_lv, uid, gid, perm)
    test_dict = super_dict
    vol = b'/dev/sdb1'
    test_dict[b'vol'].append(vol)
    test_obj.add_vol(mount, vol)
    msgpack_dict = _open_super_file()
    assert test_dict == msgpack_dict

def test_cleanup():
    _cleanup()
