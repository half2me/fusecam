#include <iostream>

#include <fuse.h>
#include "Router.h"

int main(int argc, char *argv[]) {
    Router::setup(); // Setup router
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    fuse_main(args.argc, args.argv, &Router::ops, NULL); // Start FUSE
    return 0;
}