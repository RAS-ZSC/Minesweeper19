#ifndef _JOYPS4_H
#define _JOYPS4_H

#include <ros.h>
#include <Arduino.h>
#include <HBridge_Monster.h>
#include <sensor_msgs/Joy.h>

class JoyControl {
private:
   /*TODO handle analog values*/
   /*int x = 0, y = 0;*/
   uint8_t square, x, circle, tri, L1, R1, L2, R2, share, options, L3, R3, home, touchPad, x_, y_;
   float R2_pwm, L2_pwm;
   HBridge& hbridge;  /* Attached H-Bridge */

public:
  JoyControl(HBridge&);
  void handle(sensor_msgs::Joy msg);
};

#endif
