#include "SerialController.hh"

SerialController::SerialController(){

}

SerialController::SerialController(const char* src): device(const_cast<char*>(src)){

}

bool SerialController::writeTT(unsigned char msg[]){
    //flush(fd);
    return (write(fd, msg, sizeof(msg)) != -1);
}

bool SerialController::readFT(unsigned char* buffer, int len){
    return read(fd, buffer, len);
}

bool SerialController::connect(){
    fd = open(device, O_RDWR | O_NOCTTY);
    return fd != -1;
}

void SerialController::disconnect(){
    close(fd);
}

int SerialController::getPosition(unsigned char channel){
    unsigned char cmd[] = {G_POSITION, channel};
    unsigned char * response;
    if(writeTT(cmd))
        readFT(response, 2);
    return response[0] * 256 * response[1];
}

int SerialController::setTarget(unsigned char channel, unsigned short target){
    target *= 4;
    unsigned char cmd[] = { S_TARGET, channel, target & 0x7F, (target >> 7) & 0x7F };
    return (writeTT(cmd) ? 0 : -1);
}

int SerialController::setSpeed(unsigned char channel, unsigned short speed){
    unsigned char cmd[] = { 0x87, channel, speed & 0x7F, (speed >> 7) & 0x7F };
    return (writeTT(cmd) ? 0 : -1);
}

int SerialController::setAcceleration(unsigned char channel, unsigned short acceleration){
    unsigned char cmd[] = { 0x89, channel, acceleration & 0x7F, (acceleration >> 7) & 0x7F };
    return (writeTT(cmd) ? 0 : -1);
}

bool SerialController::isIdle(){
    unsigned char cmd = 0x93;
    unsigned char bf;

    if(!writeTT(&cmd))
    {
        //recheck [obsolete]
        return false;
    }

    if(!readFT(&bf, sizeof(bf))){
        //recheck [obsolete]
        return false;
    }

    return (bf == 0x01);
}

int SerialController::goHome(){
    unsigned char cmd = 0xA2;
    return (writeTT(&cmd) ? 0 : -1);
}

unsigned short getErrors(){
    //0xA1 -> [0] & 0x7F + 256 * [1]&0x7f
}
