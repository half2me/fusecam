#include "Camera.h"

Camera::Camera() {
    // debug generate streams and io
    setStream("str1", *new Stream());
    setStream("str2", *new Stream());
    setIo("io1", *new Io());
    setIo("io2", *new Io());
}

Camera::~Camera() {
    // Cleanup Streams
    for (std::pair<const std::string, Stream *> & s: streams) {
        delete s.second;
    }

    // Cleanup Io
    for (std::pair<const std::string, Io *> & i: io) {
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
