#include "DummyCamera.h"
#include "DummyIo.h"

DummyCamera::DummyCamera() {
    setIo("hwi0", new DummyIo(false));
    getIo("hwi0")->setLevel(true);
    setIo("hwi1", new DummyIo(false));
    setIo("hwo0", new DummyIo(false));
    setIo("hwo1", new DummyIo(false));
}
