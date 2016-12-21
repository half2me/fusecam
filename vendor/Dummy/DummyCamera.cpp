#include "DummyCamera.h"
#include "DummyIo.h"

DummyCamera::DummyCamera() {
    setIo("hwi0", new DummyIo(false, false));
    setIo("hwi1", new DummyIo(false, false));
    setIo("hwo0", new DummyIo(false, false));
    setIo("hwo1", new DummyIo(false, false));
}
