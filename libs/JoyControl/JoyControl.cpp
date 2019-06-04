#include <JoyControl.h>

JoyControl::JoyControl(HBridge& hbridge) : hbridge(hbridge) {

}

void JoyControl::handle(char code) {
     
   /*TODO handle analog values*/
   /*if (code == 'S')
      hbridge.move(x, y);*/
        
   if (code == 'Y') 
      hbridge.left() ;

   else if (code == 'P') 
      hbridge.forward();

   else if (code== 'B')
      hbridge.right();

   else if (code=='A') 
      hbridge.backward();
	
   else if (code=='Q')
      hbridge.stop();


}
