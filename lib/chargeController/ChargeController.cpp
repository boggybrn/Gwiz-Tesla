#include <ChargeController.h>
#include <EEPROMSettings.h>

extern EEPROMSettings settings;

ChargeController::ChargeController(PinInterface *acPin, PinInterface *ccPin, PinInterface *vcPin, GwizPackInterface *pack)
{
    state = IDLE;
    acConnectedPin = acPin;
    currentControlPin = ccPin;
    voltageControlPin = vcPin;

    myPack = pack;
}

void ChargeController::init(void)
{
}

void ChargeController::service(void)
{
    if (acConnectedPin->doDigitalRead()) //anytime the AC cable is disconnected jump back to the idle state
    {
        stopCharging();
    }

    switch (state)
    {
    case IDLE: // in this state we are waiting for the AC charging cable to be plugged in
        if (!acConnectedPin->doDigitalRead())
        {
            if (myPack->getLowestTemperature() <= settings.UnderTSetpoint)
            {
                state = TOO_COLD_TO_CHARGE;
            }
            else
            {
                if (myPack->getHighestTemperature() >= settings.OverTSetpoint)
                {
                    state = TOO_HOT_TO_CHARGE;
                }
                else
                {
                    startCharging();
                }
            }
        }
        break;

    case CHARGING:
        if (myPack->getHighestCellVoltage() >= settings.OverVSetpoint)
        {
            stopCharging();
            state = CHARGE_COMPLETE;
        }
        else
        {
            if ((myPack->getHighestCellVoltage() >= settings.OverVSetpoint - currentReductionApproach) && (currentLevel < numCurrentLevels ))
            {   //reduce the current level as we approach the voltage limit
                currentLevel++;         
                chargingCurrent = current_levels[currentLevel];
                currentControlPin->doAnalogWrite(chargingCurrent);
            }
        }
        
        if (myPack->getLowestTemperature() <= settings.UnderTSetpoint)
        {
            stopCharging();
            state = TOO_COLD_TO_CHARGE;
        }
        break;

    case TOO_COLD_TO_CHARGE:
        if (myPack->getLowestTemperature() > settings.UnderTSetpoint) // battery pack has warmed up enough for charging to commence
        {
            startCharging();
        }
        break;

    case TOO_HOT_TO_CHARGE:
        if (myPack->getHighestTemperature() < settings.OverTSetpoint)
        {
            startCharging();
        }
        break;
    }
}

/*
    Below here are private functions
    ================================
*/

void ChargeController::startCharging(void)
{
    state = CHARGING;
    currentLevel = 0;
    chargingCurrent = current_levels[currentLevel];
    chargingVoltage = max_charging_voltage;
    currentControlPin->doAnalogWrite(chargingCurrent);
    voltageControlPin->doAnalogWrite(chargingVoltage);
}

void ChargeController::stopCharging(void)
{
    state = IDLE;
    chargingCurrent = min_charging_current;
    chargingVoltage = min_charging_voltage;
    currentControlPin->doAnalogWrite(chargingCurrent);
    voltageControlPin->doAnalogWrite(chargingVoltage);
}