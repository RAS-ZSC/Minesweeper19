#ifndef _METAL_DETECTOR_H
#define _METAL_DETECTOR_H

class MetalDetector {
private:
  uint8_t pin;
public:
  MetalDetector(uint8_t);
  long detect();
};

#endif
