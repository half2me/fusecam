#include "Io.h"

Io::~Io() {

}

Io::Io(bool soft = true): soft(soft) {

}

bool Io::getLevel() {
    return level;
}

void Io::setLevel(bool level) {
    this->level = level;
}
