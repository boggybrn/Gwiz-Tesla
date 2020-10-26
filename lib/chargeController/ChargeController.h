#ifndef __CHARGE_CONTROLLER_H
#define __CHARGE_CONTROLLER_H
#include <PinInterface.h>
#include <GwizPackInterface.h>

#define CHG_FAN_OFF 0
#define CHG_FAN_ON  1

typedef enum ChargerState 
{
    IDLE,
    CHARGING,
    CHARGE_COMPLETE,
    TOO_COLD_TO_CHARGE,
    TOO_HOT_TO_CHARGE
} ChargerState;

typedef enum ChargerStartError
{
    STARTED,
    TOO_COLD_TO_START,
    TOO_HOT_TO_START,
    NO_AC_CONNECTED
} ChargerStartError;

class ChargeController
{
private:
    PinInterface *acConnectedPin;
    PinInterface *currentControlPin;
    PinInterface *voltageControlPin;
    PinInterface *fanControlPin;
    GwizPackInterface *myPack;
    void startCharging(void);
    void stopCharging(void);
    uint32_t chargingCurrent;
    uint32_t chargingVoltage;
    const uint8_t numCurrentLevels = 5;
    const uint8_t current_levels[5] = {0x00, 0x50, 0xA0, 0xD0, 0xE7};   //increasing values limit the current more...
    const float currentReductionApproach = 0.04;       // how many volts below the limit current reduction should kick in
    uint8_t currentLevel = 0;
public:
    ChargerState state;
    ChargeController(PinInterface *acPin, PinInterface *ccPin, PinInterface *vcPin, PinInterface *fanPin, GwizPackInterface *pack);
    void init(void);
    void service(void);
    ChargerStartError manualStart(void);
    void manualStop(void);
    static const uint32_t max_charging_current = 0;    // the output of the control pins are inverted, hence the values here!
    static const uint32_t min_charging_current = 255;
    static const uint32_t max_charging_voltage = 0;    
    static const uint32_t min_charging_voltage = 255;
};

#endif