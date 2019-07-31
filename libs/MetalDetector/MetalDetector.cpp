#include <Arduino.h>
#include <MetalDetector.h>
long int time_low;
long int time_high;
bool run;

MetalDetector::MetalDetector(uint8_t pin) {

  this->pin = pin;
  pinMode(pin, INPUT);
}

/*returns timeon */
/*in main check if timeon > filter_time
  then there is a mine */
long MetalDetector::detect() {

  while(digitalRead(pin)==HIGH){
    reading = pulseIn(12, HIGH);
    if(reading > 50){
      run = 1;
    }
  }

  timeon=time_low-time_high;

  }
  return run;
}
