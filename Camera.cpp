#include <string>
#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
    // Cleanup Io
    for (auto& i: io) {
        delete i.second;
    }

    // Cleanup streams
    for (auto& i: streams) {
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

Stream *Camera::getStream(const std::string &name) {
    return streams[name];
}

void Camera::setStream(const std::string &name, Stream *stream) {
    removeStream(name); // make sure we remove any with the same name
    this->streams[name] = stream;
}

void Camera::removeStream(const std::string &name) {
    Stream* i = getStream(name);
    if (i != nullptr) {
        delete i;
        streams.erase(name);
    }
}
