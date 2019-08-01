#include <ros.h>
#include <std_msgs/Int32.h>
#include <ros/time.h>

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


void setup() {
  pinMode(13, OUTPUT);
  
  setupLeftEncoder();
  setupRightEncoder();
  
  nh.initNode();
  nh.advertise(lwheel_pub);
  nh.advertise(rwheel_pub);
}

void loop() {
  isLRotating = true;  // reset the debouncer
  isRRotating = true;  // reset the debouncer

  lwheel_count.data = lencoder;
  rwheel_count.data = rencoder;
  
  lwheel_pub.publish( &lwheel_count );
  rwheel_pub.publish( &rwheel_count );

  nh.spinOnce();
  delay(100);
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
    rA_set = !rA_set;

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
    if ( rB_set && !rA_set )
      rencoder -= 1;

    isRRotating = false;
  }
}
