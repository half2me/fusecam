#ifndef FUSECAM_FILTER_H
#define FUSECAM_FILTER_H


#include "Frame.h"

class Filter {
public:
    Filter();
    virtual ~Filter();
    virtual void processFrame(Frame& frame);
};


#endif //FUSECAM_FILTER_H
