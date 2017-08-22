project('nasfs', 'c')
src = './src'
lib_src = './lib'
test_driver_src = './tests/driver_tests'

# Make Mpack a shared library and dependency
libmpack = shared_library('mpack', lib_src + '/mpack.c')
mpack_dep = declare_dependency(link_with : libmpack)

# Make SDS a shared library and dependency
libsds = shared_library('sds', lib_src + '/sds.c')
sds_dep = declare_dependency(link_with : libsds)

fuse_dep = dependency('fuse')
tap_dep = dependency('tap')

executable('nasfs', src + '/nasfs.c', dependencies : [fuse_dep, tap_dep, sds_dep, mpack_dep])

# Unit tests
test_src = [test_driver_src + 'test_nasfs.c', src + '/nasfs.c']
test_fs = executable(test_nafs, test_src, dependencies : [fuse_dep, tap_dep, sds_dep, mpack_dep)
