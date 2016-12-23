#ifndef FUSECAM_DUMMYIO_H
#define FUSECAM_DUMMYIO_H


#include "../../Io.h"

class DummyIo : public Io {
public:
    DummyIo(bool soft = true, bool level = false);
};


#endif //FUSECAM_DUMMYIO_H
