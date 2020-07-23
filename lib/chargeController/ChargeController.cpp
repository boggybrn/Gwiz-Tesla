#include <ChargeController.h>


ChargeController::ChargeController(PinInterface *pin)
{
    state = IDLE;
    acConnectedPin = pin;
}

void ChargeController::init(void)
{
    
}

void ChargeController::service(void)
{
    if(!acConnectedPin->doDigitalRead())
    {
        state = AC_CONNECTED;
    }
    else
    {
        state = IDLE;
    }
    
}