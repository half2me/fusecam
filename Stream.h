#ifndef FUSECAM_STREAM_H
#define FUSECAM_STREAM_H


class Stream {
public:
    Stream();
    virtual ~Stream();
    int screenShotBufferSize;
    virtual int getScreenShot(char* buf) = 0;
};


#endif //FUSECAM_STREAM_H
