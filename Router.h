#ifndef FUSECAM_ROUTER_H
#define FUSECAM_ROUTER_H

#include <vector>
#include <set>
#include "fuse.h"
#include "Camera.h"

class Router {
private:
    static void splitRoute(const char* path, std::vector<std::string> &vec);
    static std::set<std::string> dirs;
    static std::set<std::string> files;
public:
    static Camera* cam;
    static struct fuse_operations ops;
    static void setup();
    static void* init(struct fuse_conn_info *conn);
    static void destroy(void* private_data);
    static int getattr(const char* path, struct stat *statbuf);
    static int readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi);
    static int opendir(const char* path, struct fuse_file_info* fi);
    static int mkdir(const char *path, mode_t mode);
    static int rmdir(const char* path);
    static int unlink(const char *path);
    static int rename(const char *path, const char *newpath);
    static int truncate(const char* path, off_t size);
    static int open(const char* path, struct fuse_file_info* fi);
    static int release(const char *path, struct fuse_file_info *fi);
    static int read(const char* path, char *buf, size_t size, off_t offset, struct fuse_file_info* fi);
    static int write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
    static int lock(const char* path, struct fuse_file_info* fi, int cmd, struct flock* locks);
    static int mknod(const char *path, mode_t mode, dev_t dev);
};


#endif //FUSECAM_ROUTER_H
