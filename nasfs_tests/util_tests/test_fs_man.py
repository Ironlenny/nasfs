import pytest
import sys
sys.path.append ("../../nasfs_utils/")
import fs_man
import bson
import os

super_file = 'super_file'
raidLv = 1
dev = ['/dev/sda1']
super_dict = {'vol': dev, 'raid': raidLv}
mount = './'

def _open_super_file():
    file = open(super_file, 'rb')
    return bson.loads(file.read())

def test_create_super_file():
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raidLv)
    bson_dict = _open_super_file()
    assert super_dict == bson_dict
    with pytest.raises(FileExistsError):
        test_obj.create_fs("/dev/sda1", 1)
    os.remove(super_file)

def test_add_volume():
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raidLv)
    test_dict = super_dict
    vol = '/dev/sdb1'
    test_dict['vol'].append(vol)
    test_obj.add_vol(mount, vol)
    print(_open_super_file())
    bson_dict = _open_super_file()
    assert test_dict == bson_dict
    os.remove(super_file)
