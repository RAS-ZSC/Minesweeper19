#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle_<ArduinoHardware, 1, 1, 512, 128> nh;
sensor_msgs::Joy msg;

#include <HBridge_Monster.h>
HBridge hbridge(7, 8, 4, 9, 5, 6, A0, A1, A2, A3);

#include <joy_ps4_Monster.h>
JoyControl joystick(hbridge);

void messageCb( const sensor_msgs::Joy& msg) {
  joystick.handle(msg);
}

ros::Subscriber<sensor_msgs::Joy> sub("joy", messageCb );

void setup() {
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
