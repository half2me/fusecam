#ifndef FUSECAM_ROUTER_H
#define FUSECAM_ROUTER_H
#include "fuse.h"

class Router {
public:
    static void setup();
    static struct fuse_operations ops;
    static void* init(struct fuse_conn_info *conn);
    static void destroy(void* private_data);
    static int readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi);
};


#endif //FUSECAM_ROUTER_H
