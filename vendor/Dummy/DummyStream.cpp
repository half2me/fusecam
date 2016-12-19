#include <cstring>
#include "DummyStream.h"

DummyStream::DummyStream() {
    screenShotBufferSize = 30;
}

DummyStream::~DummyStream() {

}

int DummyStream::getScreenShot(char *buf) {
    memcpy(buf, "Hello World", 12);
    return 12;
}
