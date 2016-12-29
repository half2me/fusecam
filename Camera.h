#ifndef FUSECAM_CAMERA_H
#define FUSECAM_CAMERA_H


#include <vector>
#include <map>
#include "Io.h"

class Camera {
protected:
    std::string systemInfo;
public:
    std::map<std::string, Io*> io;
    Camera();
    Io* getIo(const std::string& name);
    void setIo(const std::string& name, Io* io);
    void removeIo(const std::string &name);
    virtual const std::string& getSystemInfo() const;
    virtual ~Camera();
};


#endif //FUSECAM_CAMERA_H
