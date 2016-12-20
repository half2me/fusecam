#include <iostream>
#include <cstring>
#include <zconf.h>
#include <sstream>
#include <set>
#include "Router.h"
#include "Camera.h"

#ifdef VENDOR_DUMMY

#include "vendor/Dummy/DummyCamera.h"
#include "SmartBuffer.h"

#endif

fuse_operations Router::ops = {0};
Camera *Router::cam;
std::set<std::string> Router::dirs;
std::set<std::string> Router::files;

void Router::setup() {
    ops.init = init;
    ops.destroy = destroy;
    ops.opendir = opendir;
    ops.readdir = readdir;
    ops.getattr = getattr;
    ops.mkdir = mkdir;
    ops.rmdir = rmdir;
    ops.unlink = unlink;
    ops.rename = rename;
    ops.truncate = truncate;
    ops.open = open;
    ops.release = release;
    ops.read = read;
    ops.write = write;
    ops.lock = lock;

#ifdef VENDOR_DUMMY
    cam = new DummyCamera();
#endif
}

void Router::splitRoute(const char *path, std::vector<std::string> &vec) {
    std::stringstream p(path);
    std::string segment;
    while (std::getline(p, segment, '/')) {
        vec.push_back(segment);
    }
}

void *Router::init(struct fuse_conn_info *conn) {
    std::cout << "FuseCam - FUSE version: " << conn->proto_major << "." << conn->proto_major << std::endl;
    return nullptr;
}

void Router::destroy(void *private_data) {
    std::cout << "FuseCam shutting down...";
    delete cam;
}

int Router::getattr(const char *path, struct stat *st) {
    std::cout << "getattr " << path << std::endl;

    std::vector<std::string> split;
    splitRoute(path, split);

    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time(NULL);
    st->st_mtime = time(NULL);

    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
        return 0;
    }

    if (split.size() == 2) {
        Io *io = cam->getIo(split[2]);
        if (io != nullptr) {
            st->st_mode = S_IFREG | 0666;
            st->st_nlink = 1;
            st->st_size = 1;
            return 0;
        }
    }

    return -1;
}

int Router::opendir(const char *path, struct fuse_file_info *fi) {
    std::cout << "opendir " << path << std::endl;
    return 0;
}

int Router::readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    std::cout << "readdir " << path << std::endl;

    if (strcmp(path, "/") == 0) {
        filler(buf, ".", NULL, 0);
        filler(buf, "..", NULL, 0);
        for (std::pair<const std::string, Io *> &io: cam->io) {
            filler(buf, io.first.c_str(), NULL, 0);
        }
        return 0;
    }

    return -1;
}

int Router::mkdir(const char *path, mode_t mode) {
    std::cout << "mkdir " << path << std::endl;
    return -1;
}

int Router::rmdir(const char *path) {
    std::cout << "rmdir " << path << std::endl;
    return -1;
}

int Router::unlink(const char *path) {
    std::cout << "unlink " << path << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    if (split.size() == 2) {
        auto io = cam->getIo(split[1]);
        if (io != nullptr) {
            if (io->soft) {
                cam->removeIo(split[1]);
                return 0;
            }
        }
    }
    return -1;
}

int Router::rename(const char *path, const char *newpath) {
    std::cout << "rename " << path << std::endl;
    return -1;
}

int Router::truncate(const char *path, off_t size) {
    std::cout << "truncate " << path << std::endl;
    return 0;
}

int Router::open(const char *path, struct fuse_file_info *fi) {
    std::cout << "open " << path << std::endl;
    return 0;
}

int Router::release(const char *path, struct fuse_file_info *fi) {
    std::cout << "open " << path << std::endl;
    return 0;
}

int Router::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    std::cout << "read " << path << " Size: " << size << " Offset: " << offset << std::endl;
    std::vector<std::string> split;

    if (offset != 0) {
        return 0;
    }

    if (split.size() == 2) {
        auto io = cam->getIo(split[1]);
        if (io != nullptr) {
            buf[0] = io->getLevel() ? '1' : '0';
            return 1;
        }
    }

    return -1;
}

int Router::write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    std::cout << "write " << path << std::endl;
    return -1;
}

int Router::lock(const char *path, struct fuse_file_info *fi, int cmd, struct flock *locks) {
    std::cout << "lock " << path << std::endl;
    return -1;
}