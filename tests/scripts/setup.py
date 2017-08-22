#!/usr/bin/python3

import sys
import mp_gen
import math
import time

vol = ['./a', './b']
raid_lv = 1
uid = 1
gid = 1
perm = 777
ctime = math.trunc(time.time())
inode = '0'
super_block = 'block'
dir_size = 0


mp_gen.gen_super(vol, raid_lv, super_block)
mp_gen.generate(uid, gid, perm, ctime, inode, dir_size)
