#ifndef FUSECAM_DUMMYIO_H
#define FUSECAM_DUMMYIO_H


#include "../../Io.h"

class DummyIo : public Io {
public:
    DummyIo();

    DummyIo(bool soft);
};


#endif //FUSECAM_DUMMYIO_H
