#include <string>
#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
    // Cleanup Io
    for (auto& i: io) {
        delete i.second;
    }
}

Io* Camera::getIo(const std::string &name) {
    return io[name];
}

void Camera::setIo(const std::string &name, Io* io) {
    removeIo(name); // make sure we remove any with the same name
    this->io[name] = io;
}

void Camera::removeIo(const std::string &name) {
    Io* i = getIo(name);
    if (i != nullptr) {
        delete i;
        io.erase(name);
    }
}

const std::string& Camera::getSystemInfo() const {
    return systemInfo;
}
