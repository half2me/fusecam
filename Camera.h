#ifndef FUSECAM_CAMERA_H
#define FUSECAM_CAMERA_H


#include <vector>
#include <map>
#include "Stream.h"
#include "Io.h"

class Camera {
private:
    std::map<std::string, Stream> streams;
    std::vector<Io> io;
public:
    Camera();
    Stream& getStream(const std::string& stream);
    virtual ~Camera();
};


#endif //FUSECAM_CAMERA_H
