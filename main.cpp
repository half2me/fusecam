#include <iostream>
#include <fuse.h>
#include <zconf.h>
#include <string>
#include <cstring>
#include "Router.h"

using namespace std;


int main(int argc, char* argv[]) {
    // Default params
    string argv_str(argv[0]);
    string base = argv_str.substr(0, argv_str.find_last_of("/"));
    base.append("/fusecam");
    string io_mount = base;
    io_mount.append("/io");
    string stream_mount = base;
    stream_mount.append("/stream");
    bool debug = true;

    // Make dirs
    struct stat st = {0};
    if (stat(base.c_str(), &st) == -1) {
        mkdir(base.c_str(), 0774);
    }
    if (stat(io_mount.c_str(), &st) == -1) {
        mkdir(io_mount.c_str(), 0774);
    }
    if (stat(stream_mount.c_str(), &st) == -1) {
        mkdir(stream_mount.c_str(), 0774);
    }

    // build FUSE settings
    vector<string> fuse_settings;
    fuse_settings.push_back(io_mount);
    if (debug) {
        fuse_settings.push_back("-f");
    }

    // FUSE
    Router::setup();
    int fuse_argc = (int) fuse_settings.size() + 1;
    char* fuse_argv[fuse_argc];
    fuse_argv[0] = argv[0];

    for(int i = 0; i < (int) fuse_settings.size(); i++) {
        auto opt = fuse_settings[i];
        fuse_argv[i+1] = new char[opt.size()+1];
        strcpy(fuse_argv[i+1], opt.c_str());
    }

    struct fuse_args fargs = FUSE_ARGS_INIT(fuse_argc, fuse_argv);
    fuse_main(fargs.argc, fargs.argv, &Router::ops, NULL); // Start FUSE
    return 0;
}