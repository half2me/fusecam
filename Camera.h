#ifndef FUSECAM_CAMERA_H
#define FUSECAM_CAMERA_H


#include <vector>
#include <map>
#include "Io.h"
#include "Stream.h"

class Camera {
protected:
    std::string systemInfo;
public:
    std::map<std::string, Io*> io;
    std::map<std::string, Stream*> streams;
    Camera();
    Io* getIo(const std::string& name);
    void setIo(const std::string& name, Io* io);
    void removeIo(const std::string &name);
    Stream* getStream(const std::string& name);
    void setStream(const std::string& name, Stream* stream);
    void removeStream(const std::string &name);
    virtual const std::string& getSystemInfo() const;
    virtual ~Camera();
};


#endif //FUSECAM_CAMERA_H
