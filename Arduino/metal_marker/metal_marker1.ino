#include <ros.h>
#include <visualization_msgs/Marker.h>
#include <NewPing.h>

#define TRIG 8
#define ECHO 9
#define ALARM_PIN 13
#define METAL_DETECTOR_PIN 12
#define MAX_DISTANCE 30
#define TIME_DELAY 3  //time in seconds allowed to determine if the mine is surface mine or not 
#define PULSE_DURATION 200000 // if pulse takes more than that number in micro seconds it means that mine exists 

visualization_msgs::Marker marker;
ros::Publisher mark("mark", &marker);
ros::NodeHandle  nh;
NewPing ultrasonic(TRIG , ECHO, MAX_DISTANCE);

bool rd_md = 0; // Reading Value of Metal Detector
bool rd_us = 0; // Reading Value of Ultrasonic
unsigned long marker_id = 0;
unsigned long timer;
int distance = 0;



unsigned long reading;
void setup() {
  pinMode(ALARM_PIN, OUTPUT);
  pinMode(METAL_DETECTOR_PIN, INPUT);
  nh.initNode();
  nh.advertise(mark);

}

void loop() {
  reading = pulseIn(12, HIGH, 80000000);
  if (reading > PULSE_DURATION) {
    rd_md = 1;
    timer = millis();
    digitalWrite(13, LOW);
    delay(500);
  }
  distance = ultrasonic.ping_cm();
  if (distance == 0) {
    distance = MAX_DISTANCE;
  }
  if ((distance < 20) and ((millis() - timer) / 1000 < TIME_DELAY) ) {
    rd_us = 1;
  }
  if ( (rd_us == 0) and ((millis() - timer) / 1000 > TIME_DELAY) and (rd_md == 1)) {

    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time();
    marker.ns = "my_namespace";
    marker.id = marker_id;
    marker.type = visualization_msgs::Marker::CUBE; //if the mine above the ground will be shown as a blue cube on the suface
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;
    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 0.0;
    marker.color.b = 1.0;
    mark.publish( &marker );
    marker_id++;

    rd_md = 0;
    rd_us = 0;
  }

  if ((rd_md == true) and (rd_us == true)) {
    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_link";
    marker.header.stamp = ros::Time();
    marker.ns = "my_namespace";
    marker.id = marker_id;
    marker.type = visualization_msgs::Marker::CUBE; //if the mine under the ground will be shown as a green cube under the ground
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = -0.1;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;
    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;
    mark.publish( &marker );
    marker_id++;

    rd_md = 0;
    rd_us = 0;
  }

  digitalWrite(13, HIGH);
}
