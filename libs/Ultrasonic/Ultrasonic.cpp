#include<Arduino.h>
#include<Ultrasonic.h>

Ultrasonic::Ultrasonic(uint8_t trig, uint8_t echo){
    this->trigh = trig;
    this->echo = echo;
 
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}
float Ultrasonic::getDistanceCm(){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    return pulseIn(echo, High) * 0.017;
}
float Ultrasonic::getDistanceM(){
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    
    return pulseIn(echo, HIGH) * 0.00017;
}
