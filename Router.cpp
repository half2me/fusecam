#include "Router.h"

void *Router::init(struct fuse_conn_info *conn) {
    return nullptr;
}

void Router::destroy(void *private_data) {

}

int Router::readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    return 0;
}
