#include <Arduino.h>
#include <HBridge.h>

HBridge::HBridge(int lm1, int lm2, int rm1, int rm2, int pwm1, int pwm2) {
   this->m1 = lm1;
   this->m2 = lm2;
   this->m3 = rm1;
   this->m4 = rm2;
   this->pwm1 = pwm1;
   this->pwm2 = pwm2;

   pinMode(lm1, OUTPUT);
   pinMode(lm2, OUTPUT);
   pinMode(rm1, OUTPUT);
   pinMode(rm2, OUTPUT);

   pinMode(pwm1, OUTPUT);
   pinMode(pwm2, OUTPUT);

   digitalWrite(this->pwm1, HIGH);  //review driver's restrictions 
   digitalWrite(this->pwm2, HIGH);
   PWMEnabled = true;
}

HBridge::HBridge(int lm1, int lm2, int rm1, int rm2) {
   this->m1 = lm1;
   this->m2 = lm2;
   this->m3 = rm1;
   this->m4 = rm2;

   pinMode(lm1, OUTPUT);
   pinMode(lm2, OUTPUT);
   pinMode(rm1, OUTPUT);
   pinMode(rm2, OUTPUT);
}

void HBridge::setMotorsPWM(bool m1, bool m2, bool m3, bool m4, short pwm1, short pwm2) {
   digitalWrite(this->m1, m1);
   digitalWrite(this->m2, m2);
   digitalWrite(this->m3, m3);
   digitalWrite(this->m4, m4);

   if (PWMEnabled) {
      analogWrite(this->pwm1, pwm1);
      analogWrite(this->pwm2, pwm2);
   }
}

void HBridge::setMotors(int m1, int m2, int m3, int m4) {
   digitalWrite(this->m1, m1);
   digitalWrite(this->m2, m2);
   digitalWrite(this->m3, m3);
   digitalWrite(this->m4, m4);

   if (PWMEnabled) {
        analogWrite(this->pwm1, 255);  //review driver's restrictions 
        analogWrite(this->pwm2, 255);
   }
}

void HBridge::move(short l, short r) {
   if (l == 0 && r == 0)
      setMotorsPWM(0, 0, 0, 0, 0, 0);
   else if (l >= 0 && r >= 0)
      setMotorsPWM(1, 0, 0, 1, l, r);
   else if (l <= 0 && r <= 0)
      setMotorsPWM(0, 1, 1, 0, -l, -r);
   else if (l >= 0 && r <= 0)
      setMotorsPWM(1, 0, 1, 0, l, -r);
   else if (l <= 0 && r >= 0)
      setMotorsPWM(0, 1, 0, 1, -l, r);
}

void HBridge::forward() {
   setMotors(1, 0, 1, 0);
}

void HBridge::backward() {
   setMotors(0, 1, 0, 1);
}

void HBridge::left() {
   setMotors(1,0 , 0, 1);
}

void HBridge::right() {
   setMotors(0, 1, 1, 0);
}

void HBridge::stop() {
   setMotors(0, 0, 0, 0);
}

void HBridge::enablePWM() {
   PWMEnabled = true;
}

void HBridge::disablePWM() {
   PWMEnabled = false;
}
