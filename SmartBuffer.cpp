#include <cstring>
#include "SmartBuffer.h"

SmartBuffer::SmartBuffer(int maxSize) {
    buf = new char [maxSize];
}

SmartBuffer::~SmartBuffer() {
    delete [] buf;
}

int SmartBuffer::read(const unsigned int offset, const unsigned int amount, char *dst) {

    if (offset >= size) {
        return 0;
    }

    if (offset + amount > size) {
        memcpy(dst, buf + offset, (size - offset));
        return (int) (size - offset);
    }

    memcpy(dst, &buf[offset], amount);
    return (int) amount;
}