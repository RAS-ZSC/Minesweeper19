#include <Joy_Arm.h>
#include <sensor_msgs/Joy.h>

JoyControl::JoyControl(Stepper_CNC stepperX, Stepper_CNC stepperY): stepperX(stepperX), stepperY(stepperY){
}

void JoyControl::handle(sensor_msgs::Joy msg) {
   x = msg.axes[6] ;
   y = msg.axes[7] ;
   magnetOn = msg.buttons[0];
   magnetOff = msg.buttons[1];  
 
   if (x == -1){
       stepperX.step(true, 2);
   }

   else if (x == 1) {
       stepperX.step(false, 2);
   }

   else if (y == -1){
       stepperY.step(true, 70);
   }

   else if (y == 1){
       stepperY.step(false, 70);;
   }
   
   if (magnetOn == 1)
       digitalWrite(4, HIGH);
   else if (magnetOff == 1)
       digitalWrite(4, LOW); 
}
