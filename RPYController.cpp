#include "RPYController.h"

RPYController::RPYController() :
    MAX_ROLL_(70.0),
    MIN_ROLL_(10.0),
    MAX_PITCH_(70.0),
    MIN_PITCH_(10.0)
{

}

int8_t RPYController::setAccel(MPU9250 *imu)
{
    if(imu->roll <= MIN_ROLL_){
        return 0;
    }
    if(imu->roll >= MAX_ROLL_){
       return MAX_ROLL_;
    }

    //normalize
    return ((imu->roll - MIN_ROLL_) / (MAX_ROLL_ - MIN_ROLL_) * MAX_ROLL_);
}

int8_t RPYController::setTurn(MPU9250 *imu)
{
  if(imu->pitch < 0){
    if(abs(imu->pitch) <= MIN_PITCH_){
        return 0;
    }
    if(abs(imu->pitch) >= MAX_PITCH_){
       return -MAX_PITCH_;
    }
    //normalize
    
    return ((imu->pitch + MIN_PITCH_) / (MAX_PITCH_ - MIN_PITCH_) * MAX_PITCH_);
  }else{
    if(abs(imu->pitch) <= MIN_PITCH_){
        return 0;
    }
    if(abs(imu->pitch) >= MAX_PITCH_){
       return MAX_PITCH_;
    }
    //normalize
    return ((imu->pitch - MIN_PITCH_) / (MAX_PITCH_ - MIN_PITCH_) * MAX_PITCH_);    
  }
}

void RPYController::setRPY(MPU9250 *imu)
{
    joy_y_ = setAccel(imu);
    joy_x_ = setTurn(imu);
}
    
void RPYController::updateDirectionControl(WHILL *whill)
{
    whill->setJoystick(joy_x_, joy_y_);
}


