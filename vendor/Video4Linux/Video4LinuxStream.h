#ifndef FUSECAM_VIDEO4LINUXSTREAM_H
#define FUSECAM_VIDEO4LINUXSTREAM_H


#include "../../Stream.h"
#include <linux/videodev2.h>
#include <sys/ioctl.h>

class Video4LinuxStream : public Stream {
private:
    const std::string deviceName;
    int fd = -1;
    int xioctl(int fh, unsigned long request, void* arg);
    unsigned int h, w;

    struct v4l2_capability cap = {0};
    struct v4l2_cropcap cropcap = {0};
    struct v4l2_crop crop = {0};
    struct v4l2_format fmt = {0};

    void openDevice();
    void initDevice();
public:
    Video4LinuxStream(const std::string& dev);
    ~Video4LinuxStream();
    Frame& getNextFrame();
};


#endif //FUSECAM_VIDEO4LINUXSTREAM_H
