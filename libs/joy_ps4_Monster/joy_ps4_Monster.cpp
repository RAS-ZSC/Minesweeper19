#include <joy_ps4_Monster.h>
#include <sensor_msgs/Joy.h>

JoyControl::JoyControl(HBridge& hbridge) : hbridge(hbridge) {
}

void JoyControl::handle(sensor_msgs::Joy msg) {
   x_ = msg.axes[0] * 255;
   y_ = msg.axes[1] * 255;
   R2_pwm = -msg.axes[5] * 125;
   L2_pwm = -msg.axes[2] * 125;
   square = msg.buttons[3];
   x  = msg.buttons[0];
   circle = msg.buttons[1];
   tri = msg.buttons[2];
   L1 = msg.buttons[4];
   R1 = msg.buttons[5];
   L2 = msg.buttons[6];
   R2 = msg.buttons[7];
   share = msg.buttons[8];
   options = msg.buttons[9];
   L3 = msg.buttons[11];
   R3 = msg.buttons[12];
   home = msg.buttons[10];

  R2_pwm = map(R2_pwm,-125 ,125 ,0 ,255);
  L2_pwm = map(L2_pwm,-125 ,125 ,0 ,255);

   if (R2 == 1 && R1 == 0){
      hbridge.setSpeed(R2_pwm, R2_pwm);
      hbridge.forward();
   }

   else if (L2 == 1 && L1 == 0) {
      hbridge.setSpeed(L2_pwm, L2_pwm);
      hbridge.backward();
   }

   else if (R1 == 1 && R2 == 1){
      hbridge.setSpeed(R2_pwm, R2_pwm); //turning speed
      hbridge.right();
   }
   else if (L1 == 1 && L2 == 1){
      hbridge.setSpeed(L2_pwm, L2_pwm); 
      hbridge.left(); 
   }
   else
      hbridge.stop();
}
