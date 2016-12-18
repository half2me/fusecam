#include <string>
#include "Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
    // Cleanup Streams
    for (auto& s: streams) {
        delete s.second;
    }

    // Cleanup Io
    for (auto& i: io) {
        delete i.second;
    }
}

Stream* Camera::getStream(const std::string &name) {
    return streams[name];
}

void Camera::setStream(const std::string &name, Stream &stream) {
    removeStream(name); // make sure we remove any with the same name
    streams[name] = &stream;
}

void Camera::removeStream(const std::string &name) {
    Stream* s = getStream(name);
    if (s != nullptr) {
        delete s;
        streams.erase(name);
    }
}

Io* Camera::getIo(const std::string &name) {
    return io[name];
}

void Camera::setIo(const std::string &name, Io &io) {
    removeIo(name); // make sure we remove any with the same name
    this->io[name] = &io;
}

void Camera::removeIo(const std::string &name) {
    Io* i = getIo(name);
    if (i != nullptr) {
        delete i;
        io.erase(name);
    }
}
