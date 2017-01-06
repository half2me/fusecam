#include <fcntl.h>
#include <zconf.h>
#include "Video4LinuxStream.h"
#include "../../Frame.h"

Video4LinuxStream::Video4LinuxStream(const std::string &dev) {
    deviceName = dev;
    openDevice();
    initDevice();
}

Video4LinuxStream::~Video4LinuxStream() {
    close(fd);
}

int Video4LinuxStream::xioctl(int fh, unsigned long request, void *arg) {
    int r;
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}

void Video4LinuxStream::getNextFrame(Frame* buf) {
    if (-1 == read(fd, buf->buf, buf->size)) {
        switch (errno) {
            case EAGAIN:
                throw "Try again!";
            case EIO:
                throw "EIO error";
            default:
                throw "Read error";
        }
    }
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

    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        throw "streaming i/o not supported";
    }

    // MMAP Init
    struct v4l2_requestbuffers req = {0};
    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            throw "Memory mapping not supported";
        } else {
            throw "VIDIOC_REQBUFS";
        }
    }

    if (req.count < 2) {
        throw "Insufficient buffer memory on device";
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

    frameBufferSize = fmt.fmt.pix.sizeimage;

}
