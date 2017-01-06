#include "Frame.h"

Frame::Frame(size_t size) {
    this->size = size;
    buf = new char[size];
}

Frame::~Frame() {
    delete[] buf;
}
