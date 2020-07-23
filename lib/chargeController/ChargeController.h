#ifndef __CHARGE_CONTROLLER_H
#define __CHARGE_CONTROLLER_H
#include <PinInterface.h>

typedef enum ChargerState 
{
    IDLE,
    AC_CONNECTED
} ChargerState;

class ChargeController
{
private:
    PinInterface *acConnectedPin;

public:
    ChargerState state;
    ChargeController(PinInterface *pin);
    void init(void);
    void service(void);
};

#endif