#include <iostream>
#include <cstring>
#include <zconf.h>
#include <sstream>
#include "Router.h"
#include "Camera.h"

fuse_operations Router::ops = {0};
Camera *Router::cam;

void Router::setup() {
    ops.init = init;
    ops.destroy = destroy;
    ops.opendir = opendir;
    ops.readdir = readdir;
    ops.getattr = getattr;
}

void *Router::init(struct fuse_conn_info *conn) {
    std::cout << "FUSE version: " << conn->proto_major << "." << conn->proto_major << std::endl;
    cam = new Camera();
    return nullptr;
}

void Router::destroy(void *private_data) {
    delete cam;
}

int Router::getattr(const char *path, struct stat *st)
{
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time(NULL);
    st->st_mtime = time(NULL);

    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
    } else if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
    } else {
        st->st_mode = S_IFREG | 0644;
        st->st_nlink = 1;
        st->st_size = 1024;
    }

    return 0;
}

int Router::opendir(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, "/") != 0) {
        return -1;
    }
    fi->fh = 1;
    return 0;
}

int Router::readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    std::cout << "readdir " << path << std::endl;
    filler( buf, ".", NULL, 0 );
    filler( buf, "..", NULL, 0 );

    std::vector<std::string> split;
    splitRoute(path, split);

    if (strcmp(path, "/") == 0)
    {
        filler(buf, "streams", NULL, 0);
        filler(buf, "io", NULL, 0);
        filler(buf, "system_info", NULL, 0 );
    } else if (split.size() == 2) {
        if (split[1] == "streams") {
            // list camera streams
            filler(buf, "stream1", NULL, 0);
            filler(buf, "stream2", NULL, 0);
            filler(buf, "stream3", NULL, 0);
        } else if (split[1] == "io") {
            // list io ports
        } else if (split[1] == "streams") {
            // list camera streams
        }
    }

    return 0;
}

void Router::splitRoute(const char *path, std::vector<std::string> &vec) {
    std::stringstream p(path);
    std::string segment;
    while(std::getline(p, segment, '/'))
    {
        vec.push_back(segment);
    }
}
