#ifndef _JOYCONTROL_H
#define _JOYCONTROL_H

#include <Arduino.h>
#include <HBridge.h>

class JoyControl {
private:
   /*TODO handle analog values*/
   /*int x = 0, y = 0;*/
  
   HBridge& hbridge;  /* Attached H-Bridge */

public:
  JoyControl(HBridge&);
  void handle(char);
};

#endif
