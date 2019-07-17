#include <HBridge.h>
HBridge hbridge(3, 5, 6, 9);//, 10, 11);

#include <JoyControl.h>
JoyControl joystick(hbridge);

#include <ros.h>
#include <std_msgs/String.h>
ros::NodeHandle  nh;

/* Control Mehtods */
char x ;

void ROS_CALLBACK(const std_msgs::String &msg) {
  x = msg.data[0] ;
  joystick.handle(x);
}

ros::Subscriber<std_msgs::String> s("Joystick_", &ROS_CALLBACK);

void setup() {
  nh.initNode();
  nh.subscribe(s);
}

void loop() {
  nh.spinOnce();
  delay(1);
}
