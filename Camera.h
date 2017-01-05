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
    virtual Io* getIo(const std::string& name);
    virtual void setIo(const std::string& name, Io* io);
    virtual void removeIo(const std::string &name);
    virtual Stream* getStream(const std::string& name);
    virtual void setStream(const std::string& name, Stream* stream);
    virtual void removeStream(const std::string &name);
    virtual const std::string& getSystemInfo() const;
    virtual ~Camera();
};


#endif //FUSECAM_CAMERA_H
