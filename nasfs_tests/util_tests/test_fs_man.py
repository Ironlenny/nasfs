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
uid = 'test'
gid = 'test'
perm = 772

def _open_super_file():
    file = open(super_file, 'rb')
    return bson.loads(file.read())

def _cleanup():
    if os.path.isfile(super_file):
        os.remove(super_file)

    if os.path.isfile(meta_db):
        os.remove(meta_db)

def test_create_super_file():
    _cleanup()
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raidLv, uid, gid, perm)
    bson_dict = _open_super_file()
    assert super_dict == bson_dict
    with pytest.raises(FileExistsError):
        test_obj.create_fs(dev, raidLv, uid, gid, perm)

def test_create_meta_db():
    _cleanup()
    test = {'contains': ['.', '..'], 'uid': uid, 'gid': gid, 'perm': perm\
            , 'atime': None, 'dir': True}
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raidLv, uid, gid, perm)
    test_db = db.DB()
    test_db.open(meta_db, '1', db.DB_BTREE, db.DB_RDONLY)
    assert test == bson.loads(test_db.get(b'self'))

def test_add_volume():
    _cleanup()
    test_obj = fs_man.FSMan()
    test_obj.create_fs(dev, raidLv, uid, gid, perm)
    test_dict = super_dict
    vol = '/dev/sdb1'
    test_dict['vol'].append(vol)
    test_obj.add_vol(mount, vol)
    bson_dict = _open_super_file()
    assert test_dict == bson_dict

def test_cleanup():
    _cleanup()
