#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

Stream& Camera::getStream(const std::string &stream) {
    return streams[stream];
}
