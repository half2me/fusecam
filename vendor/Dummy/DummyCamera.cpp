#include "DummyCamera.h"

DummyCamera::DummyCamera() {
    setStream("static", new DummyStream());
}
