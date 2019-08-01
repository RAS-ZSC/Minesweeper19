  #include <Joy_Arm.h>
#include <Stepper_CNC.h>
#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle_ <ArduinoHardware, 1, 1, 512, 128> nh;
sensor_msgs::Joy msg;

Stepper_CNC stepperX(8, 5, 2);
Stepper_CNC stepperY(8, 6, 3);

JoyControl joy(stepperX, stepperY);

void messageCb(const sensor_msgs::Joy& msg) {
  joy.handle(msg);
}

ros::Subscriber<sensor_msgs::Joy> sub("joy", messageCb);

void setup() {
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
