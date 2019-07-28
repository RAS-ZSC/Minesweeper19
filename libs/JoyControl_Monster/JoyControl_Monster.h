#ifndef _JOYCONTROL_H
#define _JOYCONTROL_H

#include <Arduino.h>
#include <HBridge_Monster.h>

class JoyControl {
private:
   /*TODO handle analog values*/
   /*int x = 0, y = 0;*/
   int16_t Speed;
   HBridge& hbridge;  /* Attached H-Bridge */

public:
  JoyControl(HBridge&);
  void handle(char[]);
};

#endif
