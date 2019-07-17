#ifndef Ultrasonic
#define Ultrasonic

class Ultrasonic{
    public:
	// trig - echo pins
    	Ultrasonic(uint8_t, uint8_t);
        float getDistanceCm();
	float getDistanceM();

    private:
        int16_t distance;
        uint8_t trig, echo;
}

#endif
