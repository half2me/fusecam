#include <iostream>
#include <fuse.h>

int main(int argc, char *argv[]) {
    struct fuse_operations ops;
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    fuse_main(args.argc, args.argv, &ops, NULL);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}