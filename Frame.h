#ifndef FUSECAM_FRAME_H
#define FUSECAM_FRAME_H

#include <string>

class Frame {
public:
    std::string type;
    Frame();
    virtual ~Frame();
};


#endif //FUSECAM_FRAME_H
