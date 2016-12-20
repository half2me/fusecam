#ifndef FUSECAM_IO_H
#define FUSECAM_IO_H


class Io {
private:
    bool level;
public:
    bool soft;
    Io(bool soft);
    virtual ~Io();
    virtual bool getLevel();
    virtual void setLevel(bool level);
};


#endif //FUSECAM_IO_H
