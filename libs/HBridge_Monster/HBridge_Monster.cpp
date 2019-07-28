#include <Arduino.h>
#include <HBridge_Monster.h>

HBridge::HBridge(uint8_t lm1, uint8_t lm2, uint8_t rm1, uint8_t rm2, uint8_t pwm1, uint8_t pwm2, uint8_t EN1, uint8_t EN2, uint8_t C1, uint8_t C2) {
   this->m1 = lm1;
   this->m2 = lm2;
   this->m3 = rm1;
   this->m4 = rm2;
   this->pwm1 = pwm1;
   this->pwm2 = pwm2;
   this->EN1 = EN1;
   this->EN2 = EN2;
   this->C1 = C1;
   this->C2 = C2;

   m1Speed = 100;
   m2Speed = 100;

   pinMode(lm1, OUTPUT);
   pinMode(lm2, OUTPUT);
   pinMode(rm1, OUTPUT);
   pinMode(rm2, OUTPUT);

   pinMode(pwm1, OUTPUT);
   pinMode(pwm2, OUTPUT);

   pinMode(EN1, OUTPUT);
   pinMode(EN2, OUTPUT);
   
   pinMode(C1, INPUT);
   pinMode(C2, INPUT);

   digitalWrite(EN1, HIGH);
   digitalWrite(EN2, HIGH);
}

HBridge::HBridge(uint8_t lm1, uint8_t lm2, uint8_t rm1, uint8_t rm2, uint8_t pwm1, uint8_t pwm2, uint8_t EN1, uint8_t EN2) {
   this->m1 = lm1;
   this->m2 = lm2;
   this->m3 = rm1;
   this->m4 = rm2;

   this->pwm1 = pwm1;
   this->pwm2 = pwm2;

   this->EN1 = EN1;
   this->EN2 = EN2;
   
   m1Speed = 100;
   m2Speed = 100;

   pinMode(lm1, OUTPUT);
   pinMode(lm2, OUTPUT);
   pinMode(rm1, OUTPUT);
   pinMode(rm2, OUTPUT);
   pinMode(EN1, OUTPUT);
   pinMode(EN2, OUTPUT);
}

void HBridge::setMotors(bool m1, bool m2, bool m3, bool m4) {
   digitalWrite(this->m1, m1);
   digitalWrite(this->m2, m2);
   digitalWrite(this->m3, m3);
   digitalWrite(this->m4, m4);
}

void HBridge::forward() {
   setMotors(1, 0, 1, 0);
   analogWrite(pwm1, m1Speed);
   analogWrite(pwm2, m2Speed);
}

void HBridge::backward() {
   setMotors(0, 1, 0, 1);
   analogWrite(pwm1, m1Speed);
   analogWrite(pwm2, m2Speed);
}

void HBridge::left() {
   setMotors(1, 0, 0, 1);
   analogWrite(pwm1, m1Speed);
   analogWrite(pwm2, m2Speed);
}

void HBridge::right() {
   setMotors(0, 1, 1, 0);
   analogWrite(pwm1, m1Speed);
   analogWrite(pwm2, m2Speed);
}

void HBridge::stop() {
   setMotors(0, 0, 0, 0);
   digitalWrite(pwm1, 0);
   digitalWrite(pwm2, 0);
}

void HBridge::setSpeed(int16_t m1Speed, int16_t m2Speed2){
   this->m1Speed = m1Speed;
   this->m2Speed = m2Speed;
}

uint16_t HBridge::getM1Current(){
   return analogRead(C1);
}

uint16_t HBridge::getM2Current(){
   return analogRead(C2);
}

void HBridge::move(int16_t l, int16_t r){
if (l > 0 && r > 0){
   setMotors(1, 0, 1, 0);
   analogWrite(pwm1, l);
   analogWrite(pwm2, r);
}
else if (l > 0 && r < 0){
   setMotors(0, 1, 1, 0);
   analogWrite(pwm1, l);
   analogWrite(pwm2, -r);
}
else if (l < 0 && r > 0){
   setMotors(1, 0, 0, 1);
   analogWrite(pwm1, -l);
   analogWrite(pwm2, r);
}
else if (l < 0 && r < 0){
   setMotors(1, 0, 0, 1);
   analogWrite(pwm1, -l);
   analogWrite(pwm2, -r);
}
else{
stop();
}
}
