#ifndef FUSECAM_STREAM_H
#define FUSECAM_STREAM_H

#include <map>
#include "Filter.h"

class Stream {
protected:
    virtual void processFrame(Frame& frame);
public:
    size_t frameBufferSize;
    std::map<std::string, Filter*> filters;
    Stream();
    virtual ~Stream();
    virtual Filter* getFilter(const std::string& name);
    virtual void setFilter(const std::string& name, Filter* filter);
    virtual void removeFilter(const std::string &name);
    virtual void getNextFrame(Frame* buf) = 0;
};


#endif //FUSECAM_STREAM_H
