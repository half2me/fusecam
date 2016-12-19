#ifndef FUSECAM_STREAM_H
#define FUSECAM_STREAM_H


class Stream {
public:
    Stream();
    virtual ~Stream();
    unsigned int screenShotBufferSize;
    virtual unsigned int getScreenShot(char* buf) = 0;
};


#endif //FUSECAM_STREAM_H
