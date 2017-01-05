#include "DummyCamera.h"
#include "DummyIo.h"
#include "../Video4Linux/Video4LinuxStream.h"
#include <string>

DummyCamera::DummyCamera() : Camera() {
    systemInfo = "Dummy Camera Info\n";
    setIo("hwi0", new DummyIo(false, false));
    setIo("hwi1", new DummyIo(false, false));
    setIo("hwo0", new DummyIo(false, false));
    setIo("hwo1", new DummyIo(false, false));

    setStream("v4l-yuv", new Video4LinuxStream("/dev/video0"));
}
