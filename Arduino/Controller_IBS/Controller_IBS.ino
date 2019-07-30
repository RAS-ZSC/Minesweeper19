#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle_<ArduinoHardware, 1, 1, 512, 128> nh;
sensor_msgs::Joy msg;

#include <HBridge.h>
HBridge hbridge(3, 5, 10, 9);

#include <joy_ps4_IBS.h>
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
}
