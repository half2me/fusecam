#include "Stream.h"

Stream::Stream() {

}

Stream::~Stream() {

}

Filter *Stream::getFilter(const std::string &name) {
    return filters[name];
}

void Stream::setFilter(const std::string &name, Filter *filter) {
    removeFilter(name); // make sure we remove any with the same name
    this->filters[name] = filter;
}

void Stream::removeFilter(const std::string &name) {
    Filter* i = getFilter(name);
    if (i != nullptr) {
        delete i;
        filters.erase(name);
    }
}
