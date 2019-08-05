#ifndef _JOY_ARM
#define _JOY_ARM

#include <ros.h>
#include <Arduino.h>
#include <Stepper_CNC.h>
#include <sensor_msgs/Joy.h>

class JoyControl {
private:
   int8_t x, y, magnetOn, magnetOff;
   Stepper_CNC stepperX;
   Stepper_CNC stepperY;

public:
  JoyControl(Stepper_CNC, Stepper_CNC);
  void handle(sensor_msgs::Joy msg);
};

#endif
