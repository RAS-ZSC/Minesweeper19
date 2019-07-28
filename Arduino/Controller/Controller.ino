
#include <HBridge.h>
HBridge hbridge(3, 5, 10, 9);//, 10, 11);

/* Control Mehtods */

#include <JoyControl.h>
JoyControl joystick(hbridge);

#include <ros.h>
#include <std_msgs/String.h>
ros::NodeHandle  nh;

void ROS_CALLBACK(const std_msgs::String &msg) {
  joystick.handle(msg.data);
}

ros::Subscriber<std_msgs::String> s("Joystick_",  &ROS_CALLBACK);

void setup() {

  nh.initNode();
  nh.subscribe(s);

}


void loop() {
  nh.spinOnce();
  delay(1);

}
