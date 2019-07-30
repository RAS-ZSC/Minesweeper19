#include <Joy_Arm.h>
#include <sensor_msgs/Joy.h>

JoyControl::JoyControl(Stepper_CNC& stepperX, Stepper_CNC& stepperY){
    this->stepperX = stepperX;
    this->stepperY = stepperY;
}

void JoyControl::handle(sensor_msgs::Joy msg) {
   x = msg.axes[6] ;
   y = msg.axes[7] ;

   if (x == -1){
       stepperX.step(true, 4);
   }

   else if (x == 1) {
       stepperX.step(false, 4);
   }

   else if (y == -1){
       stepperY.step(true, 4);
   }

   else if (y == 1){
       stepperY.step(false, 4);;
   }
}
