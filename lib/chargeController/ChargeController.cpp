#include <ChargeController.h>
#include <EEPROMSettings.h>


extern EEPROMSettings settings;

ChargeController::ChargeController(PinInterface *pin, GwizPackInterface *pack)
{
    state = IDLE;
    acConnectedPin = pin;
    myPack = pack;
}

void ChargeController::init(void)
{
    
}

void ChargeController::service(void)
{
    if(!acConnectedPin->doDigitalRead())
    {
        if(myPack->getHighestCellVoltage() >= settings.OverVSetpoint)
        {
            state = CHARGE_COMPLETE;
        }
        else
        {
            state = CHARGING;
        }
        
    }
    else
    {
        state = IDLE;
    }
    
}