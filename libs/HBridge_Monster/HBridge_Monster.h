#ifndef _HBRIDGE_H_MONSTER
#define _HBRIDGE_H_MONSTER

class HBridge {
private:
   uint8_t m1, m2, m3, m4, pwm1, pwm2, EN1, EN2, C1, C2;
   int16_t m1Speed, m2Speed;
   void setMotors(bool, bool, bool, bool);
   
public:
   HBridge(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
   HBridge(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
    
   void setSpeed(int16_t, int16_t);
   
   uint16_t getM1Current();
   uint16_t getM2Current();

   void forward();
   void backward();
   void left();
   void right();
   void stop();

   void move(int16_t, int16_t);
};

#endif
