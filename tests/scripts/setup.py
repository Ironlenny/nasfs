#!/usr/bin/python3

import sys
sys.path.append ("../nasfs_utils/")
import fs_man
import math
import time

fs = fs_man.FSMan()
vol = ['./a', './b']
raid_lv = 1
uid = 1
gid = 1
perm = 777
ctime = math.trunc(time.time())

fs.create_fs(vol, raid_lv, uid, gid, perm, ctime)
