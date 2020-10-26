#ifndef CURRENTSENSOR_H_
#define CURRENTSENSOR_H_

#include <eXoCAN.h>

class CurrentSensor
{
public:
    void init(void);
    void service(void);
    float getCurrentInAmps(void);
    signed long getChargeInmASeconds(void);
    void setChargeInmASeconds(signed long charge);
private:
    eXoCAN can;
    int canId, canFltIdx;
    uint8_t canRxbytes[8];
    signed long CANmilliamps;
    signed long chargeInmASeconds;
};


#endif  //CURRENTSENSOR_H_