#include <string>
#include "Camera.h"
#include <iostream>

Camera::Camera() {
}

Camera::~Camera() {
    stop();

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

void Camera::start() {
    running = true;

    // Make frame buffers
    for (auto& s : streams) {
        frameBuffers[s.first] = new Frame(s.second->frameBufferSize);
    }

    while(running) {
        // Get dem frames... TODO: make multithreaded
        for (auto& s : streams) {
            auto buf = frameBuffers[s.first];
            s.second->getNextFrame(buf);
            for (size_t i=0; i<buf->size; i++) {
                std::cout << (buf->buf)[i];
            }
            std::cout << std::endl;
        }
        stop(); // get only one frame now.
    }
}

void Camera::stop() {
    running = false;
    // TODO: join threads here (only free when all frame grabbers have stopped)
    // Free frame buffers
    for (auto& s : streams) {
        delete frameBuffers[s.first];
        frameBuffers.erase(s.first);
    }
}
