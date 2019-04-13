#pragma once

#include "utility/MPU9250.h"
#include "WHILL.h"

class RPYController
{

public:
    RPYController();

    void setRPY(MPU9250 *imu);
    void updateDirectionControl(WHILL *whill);
    int8_t getJoyX(void){ return joy_x_;}
    int8_t getJoyY(void){ return joy_y_;}
    
private:
    const float MAX_ROLL_;
    const float MIN_ROLL_;
    const float MAX_PITCH_;
    const float MIN_PITCH_;

    int8_t joy_y_;
    int8_t joy_x_;

    int8_t setAccel(MPU9250 *imu);
    int8_t setTurn(MPU9250 *imu);
};



