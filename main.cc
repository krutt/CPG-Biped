#include "CPG.hh"

void serialtest(){
    SerialController c("/dev/ttyACM0");

    std::cout << "connection status: " << c.connect() << std::endl;

    unsigned char ch = 9;
    c.setSpeed(13, 5);
    c.setAcceleration(13, 3);
    c.setTarget(13, 1450);
}

int main(int argc, char ** argv){
    CPG *gen = new CPG();
    gen->run();

    delete gen;


    return 0;
}
