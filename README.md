# NASFS: A Dynamic Raid File System

## About

NASFS is a logical filesystem. It sits on top of a traditional filesystem, such 
as ext4. This allows the layering of advanced filesystem features on top of
existing filesystem. One such feature (and NASFS raison d'etre) is Dynamic RAID
.

Dynamic RAID is a feature where the filesystem can dynamically adjust its RAID 
level, from a given target level,  according to available resources. This 
feature is especially useful in a SOHO environment where hardware is often
purchased piecemeal. With Dynamic RAID, it is possible to progressively upgrade
ones NAS with drives of increasing capacity, and the filesystem can rearrange
data in the background. No extra steps required.

NASFS is currently in development, and at this point the filesystem logic has
not been implemented. Basic mirroring and standared filesystem operations I hope
to have implemented by January.
