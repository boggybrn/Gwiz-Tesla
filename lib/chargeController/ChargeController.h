#ifndef __CHARGE_CONTROLLER_H
#define __CHARGE_CONTROLLER_H
#include <PinInterface.h>
#include <GwizPackInterface.h>

typedef enum ChargerState 
{
    IDLE,
    CHARGING,
    CHARGE_COMPLETE
} ChargerState;

class ChargeController
{
private:
    PinInterface *acConnectedPin;
    GwizPackInterface *myPack;

public:
    ChargerState state;
    ChargeController(PinInterface *pin, GwizPackInterface *pack);
    void init(void);
    void service(void);
};

#endif