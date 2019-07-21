#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int16.h>
ros::NodeHandle  nh;

#include <HBridge_Monster.h>
//m1 Cw, m1 CCw, m2 Cw, m2 CCW, pwm1, pwm2, EN1, EN2 , C1, C2
HBridge hbridge(7, 8, 4, 9, 5, 6, A0, A1, A2, A3);

#include <JoyControl_Monster.h>
JoyControl joystick(hbridge);

char x;

std_msgs::Int16 m1Current;
std_msgs::Int16 m2Current;

ros::Publisher m2CurrentPub("lmotor_current", &m1Current);
ros::Publisher m1CurrentPub("rmotor_current", &m2Current);

void ROS_CALLBACK(const std_msgs::String &msg) {
  x = msg.data[0] ;
  joystick.handle(x);
}

ros::Subscriber<std_msgs::String> s("Joystick_",  &ROS_CALLBACK);

void setup() {
  nh.initNode();
  nh.advertise(m1CurrentPub);
  nh.advertise(m2CurrentPub);
  nh.subscribe(s);
}

void loop() {
  m1Current.data = hbridge.getM1Current();
  m1CurrentPub.publish(&m1Current);
  m2Current.data = hbridge.getM2Current();
  m2CurrentPub.publish(&m2Current);
  nh.spinOnce();
  delay(1);
}
