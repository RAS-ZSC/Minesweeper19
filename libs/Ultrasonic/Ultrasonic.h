#ifndef _Ultrasonic
#define _Ultrasonic

class Ultrasonic{
    public:
   	// trig - echo pins
    	Ultrasonic(uint8_t, uint8_t);
    	int16_t getDistanceCm();
    	float getDistanceM();

    private:
        int16_t distance;
        uint8_t trig, echo;
};

#endif
