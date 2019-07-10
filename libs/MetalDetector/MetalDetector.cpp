#include <Arduino.h>
#include <MetalDetector.h>
long int time_low;
long int time_high;
long int timeon;

MetalDetector::MetalDetector(uint8_t pin) {

  this->pin = pin;
  pinMode(pin, INPUT);
}

/*returns timeon */
/*in main check if timeon > filter_time
  then there is a mine */
long MetalDetector::detect() {

  while(digitalRead(pin)==HIGH){
    time_high=millis();
    while(1){
      if(digitalRead(pin)==LOW){
        time_low=millis();
    break;
    }
  }

  timeon=time_low-time_high;

  }
  return timeon;
}
