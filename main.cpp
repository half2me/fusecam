#include <iostream>

#include <fuse.h>
#include "Router.h"

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    fuse_main(args.argc, args.argv, &Router::ops, NULL);
    return 0;
}