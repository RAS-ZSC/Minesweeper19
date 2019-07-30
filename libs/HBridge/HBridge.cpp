#include <Arduino.h>
#include <HBridge.h>

HBridge::HBridge(uint8_t lm1, uint8_t lm2, uint8_t rm1, uint8_t rm2, uint8_t pwm1, uint8_t pwm2) {
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

HBridge::HBridge(uint8_t lm1, uint8_t lm2, uint8_t rm1, uint8_t rm2) {
   this->m1 = lm1;
   this->m2 = lm2;
   this->m3 = rm1;
   this->m4 = rm2;

   pinMode(lm1, OUTPUT);
   pinMode(lm2, OUTPUT);
   pinMode(rm1, OUTPUT);
   pinMode(rm2, OUTPUT);
}

void HBridge::setMotorsPWM(float m1, float m2, float m3, float m4) {
   analogWrite(this->m1, m1);
   analogWrite(this->m2, m2);
   analogWrite(this->m3, m3);
   analogWrite(this->m4, m4);

  /* if (PWMEnabled) {
      analogWrite(this->pwm1, pwm1);
      analogWrite(this->pwm2, pwm2);
     }*/
}

void HBridge::setMotors(uint8_t m1, uint8_t m2, uint8_t m3, uint8_t m4) {
//replace it to digitalWrite for other kinds of drivers
   analogWrite(this->m1, m1);
   analogWrite(this->m2, m2);
   analogWrite(this->m3, m3);
   analogWrite(this->m4, m4);

   if (PWMEnabled) {
        analogWrite(this->pwm1, 240);  //review driver's restrictions 
        analogWrite(this->pwm2, 240);
   }
}

void HBridge::move(short l, short r) {
/*replace first four numbers with only 0,1 with other drivers
  and use setMotorsPWM();
  for example setMotorsPWM(1, 0, 0, 1, l, r); instead of 
  setMotors(l, 0, 0, r); */ 
   if (l == 0 && r == 0)
      setMotors(0, 0, 0, 0);
   else if (l >= 0 && r >= 0)
      setMotors(l, 0, 0, r);
   else if (l <= 0 && r <= 0)
      setMotors(0, -l, -r, 0);
   else if (l >= 0 && r <= 0)
      setMotors(l, 0, -r, 0);
   else if (l <= 0 && r >= 0)
      setMotors(0, -l, 0, r);
}

//replace 240 to HIGH for other kinds of drivers
void HBridge::forward() {
   setMotors(240, 0, 240, 0);
}

void HBridge::backward() {
   setMotors(0, 240, 0, 240);
}

void HBridge::left() {
   setMotors(100, 0, 0, 100);
}

void HBridge::right() {
   setMotors(0, 100, 100, 0);
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
