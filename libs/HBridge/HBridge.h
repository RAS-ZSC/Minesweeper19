#ifndef _HBRIDGE_H
#define _HBRIDGE_H

class HBridge {
private:
   uint8_t m1, m2, m3, m4, pwm1, pwm2;
   void setMotors(uint8_t, uint8_t, uint8_t, uint8_t);
   bool PWMEnabled = false;

public:
   HBridge(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
   HBridge(uint8_t, uint8_t, uint8_t, uint8_t);

   void setMotorsPWM(float, float, float, float);

   void move(short, short);
  
   void forward();
   void backward();
   void left();
   void right();
   void stop();

   void enablePWM();
   void disablePWM();
};

#endif
