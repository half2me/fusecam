#ifndef FUSECAM_IO_H
#define FUSECAM_IO_H


class Io {
public:
    bool soft;
private:
    bool level;
public:
    Io(bool soft = true, bool level = false);
    virtual ~Io();
    virtual bool getLevel();
    virtual void setLevel(bool level);
};


#endif //FUSECAM_IO_H
