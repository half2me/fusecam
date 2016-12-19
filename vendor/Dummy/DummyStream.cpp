#include <cstring>
#include "DummyStream.h"

DummyStream::DummyStream() {
    screenShotBufferSize = 30;
}

DummyStream::~DummyStream() {

}

unsigned int DummyStream::getScreenShot(char *buf) {
    const char* s = "Hello World";
    strcpy(buf, s);
    return sizeof(s);
}
