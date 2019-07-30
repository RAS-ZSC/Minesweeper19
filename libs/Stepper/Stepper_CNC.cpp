#include <Arduino.h>
#include <Stepper_CNC.h>

Stepper_CNC::Stepper_CNC(uint8_t enPin, uint8_t dirPin, uint8_t stepPin){

this->dirPin = dirPin;
this->stepPin = stepPin;
this->enPin = enPin;

pinMode(enPin, OUTPUT);
pinMode(dirPin, OUTPUT);
pinMode(stepPin, OUTPUT);

digitalWrite(enPin, LOW);

}

void Stepper_CNC::step(bool dir, uint8_t steps){

    digitalWrite(this->dirPin, dir);
    delay(1);
    for (int i = 0; i <steps; i++) {
        digitalWrite (this->stepPin, HIGH);
        delayMicroseconds(800);
        digitalWrite (this->stepPin, LOW);
        delayMicroseconds(800);
    }

}
