#include "Io.h"

Io::~Io() {

}

Io::Io(bool soft, bool level): soft(soft), level(level) {

}

bool Io::getLevel() {
    return level;
}

void Io::setLevel(bool level) {
    this->level = level;
}
