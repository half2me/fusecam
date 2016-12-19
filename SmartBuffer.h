#ifndef FUSECAM_SMARTBUFFER_H
#define FUSECAM_SMARTBUFFER_H


class SmartBuffer {
public:
    char * buf;
    unsigned int size;
    SmartBuffer(int maxSize);
    ~SmartBuffer();
    int read(const unsigned int offset, const unsigned int amount, char* dst);
};


#endif //FUSECAM_SMARTBUFFER_H
