#ifndef _STEPPER_CNC
#define _STEPPER_CNC

class Stepper_CNC{
    private:
        byte enPin, dirPin, stepPin;

public:
    Stepper_CNC(byte, byte , byte); 
    void step(bool, uint8_t);

};
#endif
