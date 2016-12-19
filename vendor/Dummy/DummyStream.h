#ifndef FUSECAM_DUMMYSTREAM_H
#define FUSECAM_DUMMYSTREAM_H


#include "../../Stream.h"

class DummyStream : public Stream {
public:
    DummyStream();
    ~DummyStream();
    virtual unsigned int getScreenShot(char* buf);
};


#endif //FUSECAM_DUMMYSTREAM_H
