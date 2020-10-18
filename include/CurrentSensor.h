#ifndef CURRENTSENSOR_H_
#define CURRENTSENSOR_H_

#include <eXoCAN.h>

class CurrentSensor
{
public:
    void init(void);
    void service(void);
    float getCurrentInAmps(void);

private:
    eXoCAN can;
    int canId, canFltIdx;
    uint8_t canRxbytes[8];
    signed long CANmilliamps;
};


#endif  //CURRENTSENSOR_H_