#include <iostream>

#include <fuse.h>

int readDir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return 0;
}

int main(int argc, char *argv[]) {
    struct fuse_operations ops;
    ops.readdir = readDir;
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    fuse_main(args.argc, args.argv, &ops, NULL);
    return 0;
}