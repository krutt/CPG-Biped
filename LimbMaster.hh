#include "driver/SerialController.hh"
#include <cmath>
#include <algorithm>
#include <iostream>

#define HIP_Y_RIGHT_DEFAULT 1721
#define HIP_P_RIGHT_DEFAULT 1344
#define HIP_R_RIGHT_DEFAULT 1480 //check
#define KNEE_P_RIGHT_DEFAULT 1427
#define ANKLE_P_RIGHT_DEFAULT 1459
#define ANKLE_R_RIGHT_DEFAULT 1606

#define HIP_Y_LEFT_DEFAULT 1510
#define HIP_P_LEFT_DEFAULT 1477
#define HIP_R_LEFT_DEFAULT 1480 //check
#define KNEE_P_LEFT_DEFAULT 1565
#define ANKLE_P_LEFT_DEFAULT 1423
#define ANKLE_R_LEFT_DEFAULT 1188

class LimbMaster{
private:
    SerialController* m_controller;
    double knee_p_right;
    double hip_p_right;
    double ankle_p_right;

    double knee_p_left;
    double hip_p_left;
    double ankle_p_left;
public:
    LimbMaster(){
        m_controller = new SerialController("/dev/ttyACM0");
        m_controller->connect();
    }

    ~LimbMaster(){
        delete m_controller;
    }

    inline double get_knee_p(short limb){ return limb == 1 ? knee_p_right : knee_p_left; }
    inline double get_hip_p(short limb){ return limb == 1 ? hip_p_right : hip_p_left; }
    inline double get_ankle_p(short limb){ return limb == 1 ? hip_p_right : hip_p_left; }

    void move_hip_y(short, double);
    void move_hip_p(short, double);
    void move_hip_r(short, double);
    void move_knee_p(short, double);
    void move_ankle_p(short, double);
    void move_ankle_r(short, double);
};
