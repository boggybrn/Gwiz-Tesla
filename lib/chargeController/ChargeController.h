#ifndef __CHARGE_CONTROLLER_H
#define __CHARGE_CONTROLLER_H
#include <PinInterface.h>
#include <GwizPackInterface.h>

typedef enum ChargerState 
{
    IDLE,
    CHARGING,
    CHARGE_COMPLETE,
    TOO_COLD_TO_CHARGE,
    TOO_HOT_TO_CHARGE
} ChargerState;

class ChargeController
{
private:
    PinInterface *acConnectedPin;
    PinInterface *currentControlPin;
    PinInterface *voltageControlPin;
    GwizPackInterface *myPack;
    void startCharging(void);
    void stopCharging(void);
    uint32_t chargingCurrent;
    uint32_t chargingVoltage;
public:
    ChargerState state;
    ChargeController(PinInterface *acPin, PinInterface *ccPin, PinInterface *vcPin, GwizPackInterface *pack);
    void init(void);
    void service(void);
    static const uint32_t max_charging_current = 0;    // the output of the control pins are inverted, hence the values here!
    static const uint32_t min_charging_current = 255;
    static const uint32_t max_charging_voltage = 0;    
    static const uint32_t min_charging_voltage = 255;
};

#endif