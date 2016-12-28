#include "DummyCamera.h"
#include "DummyIo.h"
#include <string>

DummyCamera::DummyCamera() : Camera() {
    systemInfo = "Dummy Camera Info\n";
    setIo("hwi0", new DummyIo(false, false));
    setIo("hwi1", new DummyIo(false, false));
    setIo("hwo0", new DummyIo(false, false));
    setIo("hwo1", new DummyIo(false, false));
}
