#ifndef _PININTERFACE_H_
#define _PININTERFACE_H_

#include <stdint.h>

class PinInterface 
{

public:
  virtual void doDigitalWrite(uint32_t val) = 0;
  virtual int doDigitalRead(void) = 0;
  virtual void doAnalogWrite(uint32_t ulValue) = 0;
   
};

#endif