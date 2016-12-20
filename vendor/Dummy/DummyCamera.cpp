#include "DummyCamera.h"
#include "DummyIo.h"

DummyCamera::DummyCamera() {
    setIo("static", new DummyIo(true));
}
