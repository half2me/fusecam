#include <iostream>
#include "Router.h"

void *Router::init(struct fuse_conn_info *conn) {
    std::cout << "FUSE version: " << conn->proto_major << "." << conn->proto_major << std::endl;
    return nullptr;
}

void Router::destroy(void *private_data) {
    std::cout << "FUSE unloading..." << std::endl;
}

int Router::readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return 0;
}

fuse_operations Router::ops = {0};

void Router::setup() {
    ops.readdir = readdir;
    ops.init = init;
    ops.destroy = destroy;
}
