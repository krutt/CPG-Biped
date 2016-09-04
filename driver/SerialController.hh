#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <termios.h>

#define G_POSITION 0x90
#define S_TARGET 0x84

#ifndef SERIAL_CONTROLLER_HH
#define SERIAL_CONTROLLER_HH

class SerialController{
    private:
        char * device; // /dev/ttyACM0
        int fd, position, target;
        bool writeTT(unsigned char*);
        bool readFT(unsigned char*, int len);
        int errorCode;
    public:
        SerialController();
        SerialController(const char*);
        bool connect();
        void disconnect();
        int getPosition(unsigned char);
        int setTarget(unsigned char, unsigned short);
        int setSpeed(unsigned char, unsigned short);
        int setAcceleration(unsigned char, unsigned short);
        bool isIdle();
        int goHome();
        unsigned short getErrors();
};
#endif
