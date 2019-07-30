#include <ros.h>
#include <std_msgs/Int32.h>
#include <ros/time.h>

#include <visualization_msgs/Marker.h>


ros::NodeHandle nh;

std_msgs::Int32 lwheel_count;
std_msgs::Int32 rwheel_count;

enum PinAssignments {
  lencoderPinA = 2,   // right
  lencoderPinB = 3,   // left

  rencoderPinA = 20,   // right
  rencoderPinB = 21,   // left
};

boolean lA_set = false;
boolean lB_set = false;
boolean rA_set = false;
boolean rB_set = false;

ros::Publisher lwheel_pub("lwheel", &lwheel_count);
ros::Publisher rwheel_pub("rwheel", &rwheel_count);

volatile long int lencoder = 0;
volatile long int rencoder = 0;

static boolean isLRotating = false;
static boolean isRRotating = false;


#define TRIG 3
#define ECHO 4
#define MAX_DISTANCE 200
#define METAL_DETECTOR_PIN 5

uint16_t marker_id = 0;

#define MINE_THRESH 2000

// Metal detector pin
visualization_msgs::Marker marker;
ros::Publisher mark("mark", &marker);

// TODO add publishers for the encoders

void setup() {
  pinMode(13, OUTPUT);
  setupLeftEncoder();
  setupRightEncoder();
  nh.initNode();
  //broadcaster.init(nh);
  nh.advertise(mark);
  nh.advertise(lwheel_pub);
  nh.advertise(rwheel_pub);

}

void loop() {

  isLRotating = true;  // reset the debouncer
  lwheel_count.data = lencoder;
  lwheel_pub.publish( &lwheel_count );

  isRRotating = true;  // reset the debouncer
  rwheel_count.data = rencoder;
  rwheel_pub.publish( &rwheel_count );

  nh.spinOnce();
  delay(10);
}

void spawnMine() {
  visualization_msgs::Marker marker;
  marker.header.frame_id = "metal_detector";
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
  marker.scale.x = 0.05;
  marker.scale.y = 0.05;
  marker.scale.z = 0.05;
  marker.color.a = 1.0; // Don't forget to set the alpha!
  marker.color.r = 0.0;
  marker.color.g = 0.0;
  marker.color.b = 1.0;
  //only if using a MESH_RESOURCE marker type:
  // marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
  mark.publish( &marker );
  marker_id++;
}

void spawnUndergroundMine() {
  visualization_msgs::Marker marker;
  marker.header.frame_id = "metal_detector";
  marker.header.stamp = ros::Time();
  marker.ns = "my_namespace";
  marker.id = marker_id;
  marker.type = visualization_msgs::Marker::CUBE; //if the mine above the ground will be shown as a blue cube on the suface
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = 0;
  marker.pose.position.y = 0;
  marker.pose.position.z = -0.05;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 0.05;
  marker.scale.y = 0.05;
  marker.scale.z = 0.05;
  marker.color.a = 1.0; // Don't forget to set the alpha!
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  //only if using a MESH_RESOURCE marker type:
  // marker.mesh_resource = "package://pr2_description/meshes/base_v0/base.dae";
  mark.publish( &marker );
  marker_id++;
}

void setupLeftEncoder() {
  pinMode(lencoderPinA, INPUT);
  pinMode(lencoderPinB, INPUT);
  digitalWrite(lencoderPinA, HIGH);
  digitalWrite(lencoderPinB, HIGH);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(digitalPinToInterrupt(lencoderPinA), doLEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(digitalPinToInterrupt(lencoderPinB), doLEncoderB, CHANGE);
}

void setupRightEncoder() {
  pinMode(rencoderPinA, INPUT);
  pinMode(rencoderPinB, INPUT);
  digitalWrite(rencoderPinA, HIGH);
  digitalWrite(rencoderPinB, HIGH);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(digitalPinToInterrupt(rencoderPinA), doREncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(digitalPinToInterrupt(rencoderPinB), doREncoderB, CHANGE);
}

void doLEncoderA() {
  // debounce
  if ( isLRotating ) delay (2);  // wait a little until the bouncing is done

  // Test transition, did things really change?
  if ( digitalRead(lencoderPinA) != lA_set ) { // debounce once more
    lA_set = !lA_set;

    // adjust counter + if A leads B
    if ( lA_set && !lB_set )
      lencoder += 1;

    isLRotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doLEncoderB() {
  if ( isLRotating ) delay (2);
  if ( digitalRead(lencoderPinB) != lB_set ) {
    lB_set = !lB_set;
    //  adjust counter - 1 if B leads A
    if ( lB_set && !lA_set )
      lencoder -= 1;

    isLRotating = false;
  }
}



void doREncoderA() {
  // debounce
  if ( isRRotating ) delay (2);  // wait a little until the bouncing is done

  // Test transition, did things really change?
  if ( digitalRead(rencoderPinA) != rA_set ) { // debounce once more
    lA_set = !lA_set;

    // adjust counter + if A leads B
    if ( rA_set && !rB_set )
      rencoder += 1;

    isRRotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doREncoderB() {
  if ( isRRotating ) delay (2);
  if ( digitalRead(rencoderPinB) != rB_set ) {
    rB_set = !rB_set;
    //  adjust counter - 1 if B leads A
    if ( lB_set && !lA_set )
      rencoder -= 1;

    isRRotating = false;
  }
}
