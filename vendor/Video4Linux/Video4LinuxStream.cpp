#include <fcntl.h>
#include <zconf.h>
#include "Video4LinuxStream.h"
#include "../../Frame.h"

Video4LinuxStream::Video4LinuxStream(const std::string &dev) {
    openDevice();
    initDevice();
}

Video4LinuxStream::~Video4LinuxStream() {

}

int Video4LinuxStream::xioctl(int fh, unsigned long request, void *arg) {
    int r;
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}

Frame *Video4LinuxStream::getNextFrame() {
    auto f = new Frame(bufferSize);
    if (-1 == read(fd, f->buf, f->size)) {
        switch (errno) {
            case EAGAIN:
                throw "Try again!";
            case EIO:
                throw "EIO error";
            default:
                throw "Read error";
        }
    }
    return f;
}

void Video4LinuxStream::openDevice() {
    // Open device
    fd = open(deviceName.c_str(), O_RDWR | O_NONBLOCK, 0);
    if (-1 == fd) {
        throw "Cannot open video device";
    }
}

void Video4LinuxStream::initDevice() {
    if (-1 == xioctl(fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            throw "Not a V4L2 device";
        } else {
            throw "VIDIOC_QUERYCAP";
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        throw "Not a video capture device";
    }

    if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
        throw "read i/o not supported";
    }

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl(fd, VIDIOC_CROPCAP, &cropcap)) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl(fd, VIDIOC_S_CROP, &crop)) {
            switch (errno) {
                case EINVAL:
                    /* Cropping not supported. */
                    break;
                default:
                    /* Errors ignored. */
                    break;
            }
        }
    } else {
        /* Errors ignored. */
    }

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == xioctl(fd, VIDIOC_G_FMT, &fmt))
        throw "VIDIOC_G_FMT";

    bufferSize = fmt.fmt.pix.sizeimage;

}
