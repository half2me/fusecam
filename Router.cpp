#include <iostream>
#include <cstring>
#include <zconf.h>
#include <sstream>
#include <set>
#include "Router.h"
#include "Camera.h"

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

    dirs.insert("streams");
    dirs.insert("io");

    files.insert("system_info");
}

void *Router::init(struct fuse_conn_info *conn) {
    std::cout << "FuseCam - FUSE version: " << conn->proto_major << "." << conn->proto_major << std::endl;
    cam = new Camera();
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

    bool dir = false;
    bool exists = false;

    if (strcmp(path, "/") == 0) {
        dir = true;
        exists = true;
    } else if (split.size() == 2) {
        if (dirs.find(split[1]) != dirs.end()) {
            dir = true;
            exists = true;
        } else if (files.find(split[1]) != files.end()) {
            exists = true;
        }
    } else if (split.size() == 3) {
        if (split[1] == "streams") {
            Stream* stream = cam->getStream(split[2]);
            if (stream != nullptr) {
                dir = true;
                exists = true;
            }
        } else if (split[1] == "io") {
            Io* io = cam->getIo(split[2]);
            if (io != nullptr) {
                dir = true;
                exists = true;
            }
        }
    }

    if (exists) {
        st->st_uid = getuid();
        st->st_gid = getgid();
        st->st_atime = time(NULL);
        st->st_mtime = time(NULL);
        if (dir) {
            st->st_mode = S_IFDIR | 0755;
            st->st_nlink = 2;
        } else {
            // file
            st->st_mode = S_IFREG | 0644;
            st->st_nlink = 1;
        }
    } else {
        return -1;
    }

    return 0;
}

int Router::opendir(const char *path, struct fuse_file_info *fi) {
    std::cout << "opendir " << path << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    if (strcmp(path, "/") == 0) {
        return 0;
    } else if (split.size() == 2) {
        if (dirs.find(split[1]) != dirs.end()) {
            return 0;
        }
    } else if (split.size() == 3) {
        if (split[1] == "streams") {
            Stream* stream = cam->getStream(split[2]);
            if (stream != nullptr) {
                return 0;
            }
        } else if (split[1] == "io") {
            Io* io = cam->getIo(split[2]);
            if (io != nullptr) {
                return 0;
            }
        }
    }

    return -1;
}

int Router::readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    std::cout << "readdir " << path << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    bool exists = false;

    if (strcmp(path, "/") == 0) {
        exists = true;
        filler(buf, "streams", NULL, 0);
        filler(buf, "io", NULL, 0);
        filler(buf, "system_info", NULL, 0);
    } else if (split.size() == 2) {
        if (split[1] == "streams") {
            exists = true;
            // list camera streams
            for (std::pair<const std::string, Stream *> & stream: cam->streams) {
                filler(buf, stream.first.c_str(), NULL, 0);
            }
        } else if (split[1] == "io") {
            exists = true;
            // list io ports
            for (std::pair<const std::string, Io *> & io: cam->io) {
                filler(buf, io.first.c_str(), NULL, 0);
            }
        }
    } else if (split.size() == 3) {
        if (split[1] == "streams") {
            Stream* stream = cam->getStream(split[2]);
            if (stream != nullptr) {
                exists = true;
            }
        } else if (split[1] == "io") {
            Io* io = cam->getIo(split[2]);
            if (io != nullptr) {
                exists = true;
            }
        }
    }

    if (exists) {
        filler(buf, ".", NULL, 0);
        filler(buf, "..", NULL, 0);
    }

    return 0;
}

void Router::splitRoute(const char *path, std::vector<std::string> &vec) {
    std::stringstream p(path);
    std::string segment;
    while (std::getline(p, segment, '/')) {
        vec.push_back(segment);
    }
}
