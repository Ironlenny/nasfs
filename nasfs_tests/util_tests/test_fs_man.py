from bsddb3 import db
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
meta_db = 'meta_db'

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

def test_create_meta_db():
    test = {'root': 'self'}
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raidLv)
    self.db = db.open(meta_db, None, db.DB_BTREE, db.DB_RDONLY)
    assert test == db['root']
    os.remove(super_file)
    os.remove(meta_db)

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
