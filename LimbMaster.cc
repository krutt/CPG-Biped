#include "LimbMaster.hh"

void LimbMaster::move_hip_p(short limb, double angle){
    //scale it
    //400 is max delta for 45 degrees
    if(limb == 1) hip_p_right = angle;
    else if(limb == 2) hip_p_left = angle;

    bool minus = (angle < 0);
    angle = abs(angle);
    angle = std::min(angle, 40.0);
    //45..400
    //angle..y

    //y = (angle*400)/45

    minus = (limb == 1 ? minus : !minus);

    double val = (limb == 1 ? HIP_P_RIGHT_DEFAULT : HIP_P_LEFT_DEFAULT) + (((minus ? 1 : -1) * (400*angle)) / 40);

    int channel = (limb == 1 ? 1 : 7);
    std::cout << "[val] hip [" << limb << "] is " << val << std::endl;
    m_controller->setSpeed(channel, 0);
    m_controller->setTarget(channel, val);
}

void LimbMaster::move_hip_y(short limb, double angle){}
void LimbMaster::move_hip_r(short limb, double angle){}

void LimbMaster::move_knee_p(short limb, double angle){
    if(limb == 1) knee_p_right = angle;
    else if(limb == 2) knee_p_left = angle;

    angle = std::max(-5.0, angle);
    angle = std::min(angle, 40.0);

    double val = (limb == 1 ? KNEE_P_RIGHT_DEFAULT : KNEE_P_LEFT_DEFAULT) + (limb == 1 ? 1 : -1) * ((450*angle) / 40);
    int channel = (limb == 1 ? 3 : 12);

    std::cout << "[val] knee [" << limb << "] is " << val << std::endl;
    m_controller->setSpeed(channel, 0);
    m_controller->setTarget(channel, val);
}
void LimbMaster::move_ankle_p(short limb, double angle){
    angle = std::max(-5.0, angle);
    angle = std::min(angle, 40.0);

    double val = (limb == 1 ? ANKLE_P_RIGHT_DEFAULT : ANKLE_P_LEFT_DEFAULT) + (limb == 1 ? 1 : -1) * ((400 * angle ) / 40);
    int channel = (limb == 1 ? 4 : 13);

    std::cout << "[val] ankle [" << limb << "] " << angle << " / " << val << std::endl;

    m_controller->setSpeed(channel, 0);
    m_controller->setTarget(channel, val);
}


void LimbMaster::move_ankle_r(short limb, double angle){}
