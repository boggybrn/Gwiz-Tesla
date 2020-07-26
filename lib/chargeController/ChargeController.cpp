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
    if (acConnectedPin->doDigitalRead())        //anytime the AC cable is disconnected jump back to the idle state
    {
        state = IDLE;
    }

    switch (state)
    {
    case IDLE: // in this state we are waiting for the AC charging cable to be plugged in
        if (!acConnectedPin->doDigitalRead())
        {
            state = CHARGING;
        }
        break;

    case CHARGING:
        if (myPack->getHighestCellVoltage() >= settings.OverVSetpoint)
        {
            state = CHARGE_COMPLETE;
        }
        if (myPack->getLowestTemperature() <= settings.UnderTSetpoint)
        {
            state = TOO_COLD_TO_CHARGE;
        }
        break;

    case TOO_COLD_TO_CHARGE:
        if (myPack->getLowestTemperature() > settings.UnderTSetpoint)       // battery pack has warmed up enough for charging to commence
        {
            state = CHARGING;
        }
        break;
    }
}