#!/usr/bin/python3

import sys
sys.path.append ("../nasfs_utils/")
import fs_man

fs = fs_man.FSMan()
vol = ['./a', './b']
raid_lv = 1
uid = 1
gid = 1
perm = 777
max_dir = 65000

fs.create_fs(vol, raid_lv, uid, gid, perm, max_dir)
