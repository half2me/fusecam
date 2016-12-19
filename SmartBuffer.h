#ifndef FUSECAM_SMARTBUFFER_H
#define FUSECAM_SMARTBUFFER_H


class SmartBuffer {
private:
    unsigned int size;
    unsigned int maxSize;
public:
    char * buf;
    SmartBuffer(int maxSize);
    ~SmartBuffer();
    int read(const unsigned int offset, const unsigned int amount, char* dst);
};


#endif //FUSECAM_SMARTBUFFER_H
