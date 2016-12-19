#include <cstring>
#include "DummyStream.h"

DummyStream::DummyStream() {
    screenShotBufferSize = 30;
}

DummyStream::~DummyStream() {

}

unsigned int DummyStream::getScreenShot(char *buf) {
    auto s = "Hello World";
    strcpy(buf, s);
    return 12;
}
