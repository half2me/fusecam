#ifndef FUSECAM_STREAM_H
#define FUSECAM_STREAM_H

#include <map>
#include "Filter.h"

class Stream {
public:
    std::map<std::string, Filter*> filters;
    Stream();
    virtual ~Stream();
    Filter* getFilter(const std::string& name);
    void setFilter(const std::string& name, Filter* filter);
    void removeFilter(const std::string &name);
};


#endif //FUSECAM_STREAM_H
