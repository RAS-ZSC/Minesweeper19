#include <NewPing.h>
#include <ros.h>

ros::NodeHandle_ <3, 3, 128, 128> nh;
#define TRIGGER_PIN_FRONT  A0  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_FRONT     A1  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define TRIGGER_PIN_BACK  A2  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN_BACK     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.

#define MAX_DISTANCE 200
NewPing frontUltrasonic(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing backUltrasonic(TRIGGER_PIN_BACK, ECHO_PIN_BACK, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  nh.init_node("");

}

void loop() {
  if (frontUltrasonic.ping_cm() < 20) {
    // spawn a mine
  }


}
