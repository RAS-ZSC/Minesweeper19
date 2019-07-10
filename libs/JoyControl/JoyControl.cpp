#include <JoyControl.h>

JoyControl::JoyControl(HBridge& hbridge) : hbridge(hbridge) {

}

void JoyControl::handle(char code) {
     
   /*TODO handle analog values*/
   /*if (code == 'S')
      hbridge.move(x, y);*/
        
   if (code == 'L') 
      hbridge.left() ;

   else if (code == 'N') 
      hbridge.forward();

   else if (code== 'M')
      hbridge.right();

   else if (code=='A') 
      hbridge.backward();
	
   else if (code=='Q')
      hbridge.stop();


}
