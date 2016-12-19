#ifndef FUSECAM_STREAM_H
#define FUSECAM_STREAM_H


class Stream {
public:
    int screenShotBufferSize = 4096;
    virtual int getScreenShot(char* buf) = 0;
};


#endif //FUSECAM_STREAM_H
