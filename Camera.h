#ifndef FUSECAM_CAMERA_H
#define FUSECAM_CAMERA_H


#include <vector>
#include <map>
#include "Stream.h"
#include "Io.h"

class Camera {
private:
    std::string systemInfo;
public:
    std::map<std::string, Stream*> streams;
    std::map<std::string, Io*> io;
    Camera();
    Stream* getStream(const std::string& name);
    void setStream(const std::string& name, Stream& stream);
    void removeStream(const std::string &name);
    Io* getIo(const std::string& name);
    void setIo(const std::string& name, Io& io);
    void removeIo(const std::string &name);
    virtual const std::string& getSystemInfo() const;
    virtual ~Camera();
};


#endif //FUSECAM_CAMERA_H
