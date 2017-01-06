#include <iostream>
#include <cstring>
#include <string>
#include <zconf.h>
#include <sstream>
#include <set>
#include "Router.h"
#include "Camera.h"

#ifdef VENDOR_DUMMY
    #include "vendor/Dummy/DummyCamera.h"
#endif

fuse_operations Router::ops = {0};
Camera *Router::cam;

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
    ops.mknod = mknod;
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
#ifdef VENDOR_DUMMY
    cam = new DummyCamera();
#endif

    cam->start();
    return nullptr;
}

void Router::destroy(void *private_data) {
    std::cout << "FuseCam shutting down...";
    cam->stop();
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
        Io *io = cam->getIo(split[1]);
        if (io != nullptr) {
            st->st_mode = S_IFREG | 0666;
            st->st_nlink = 1;
            st->st_size = 4;
            return 0;
        }
    }

    return -ENOENT;
}

int Router::opendir(const char *path, struct fuse_file_info *fi) {
    std::cout << "opendir " << path << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    if (strcmp(path, "/") == 0) {
        return 0;
    }

    if (split.size() == 2) {
        if (cam->getIo(split[1]) != nullptr) {
            return -ENOTDIR;
        }
    }

    return -ENOENT;
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
            } else {
                return -EPERM;
            }
        } else {
            return -ENOENT;
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
    std::cout << "release " << path << std::endl;
    return 0;
}

int Router::read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    std::cout << "read " << path << " Size: " << size << " Offset: " << offset << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    if (offset > 0) {
        return 0; // Seeking is not supported
    }

    if (split.size() == 2) {
        auto io = cam->getIo(split[1]);
        if (io != nullptr) {
            switch (size) {
                case 0:
                    return 0;
                case 1:
                    buf[0] = io->getLevel() ? '1' : '0';
                    return 1;
                default:
                    buf[0] = io->getLevel() ? '1' : '0';
                    buf[1] = '\n';
                    return 2;
            }
        } else {
            return -ENOENT;
        }
    }

    return -1;
}

int Router::write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    std::cout << "write " << path << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    if (offset != 0) {
        return 0;
    }

    if (split.size() == 2) {
        auto io = cam->getIo(split[1]);
        if (io != nullptr) {
            if (size <= 2) {
                io->setLevel(buf[0] != '0');
                return (int) size;
            }
        }
    }

    return -1;
}

int Router::lock(const char *path, struct fuse_file_info *fi, int cmd, struct flock *locks) {
    std::cout << "lock " << path << std::endl;
    return 0;
}

int Router::mknod(const char *path, mode_t mode, dev_t dev) {
    std::cout << "mknod " << path << std::endl;
    std::vector<std::string> split;
    splitRoute(path, split);

    if (!(mode & S_IFREG)) {
        // only allow regular files
        return -1;
    }

    if (split.size() == 2) {
        if (cam->getIo(split[1]) == nullptr) {
            cam->setIo(split[1], new Io());
            return 0;
        } else {
            return -EEXIST;
        }
    }

    return -1;
}
