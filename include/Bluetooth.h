#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <GwizPackInterface.h>
#include <CurrentSensor.h>
#include <ChargeController.h>

class Bluetooth
{
private:
    GwizPackInterface *myPack;
    CurrentSensor *myCurrentSensor;
    ChargeController *myChargeController;
    char cmdBuffer[80];
    int ptrBuffer;
    bool rn4871InfoMode;

public:
    Bluetooth(GwizPackInterface *pack, CurrentSensor *currentSensor, ChargeController *chargeController);
    void init(void);
    void service(void);
    void mySerialEvent(void);
    void handleBluetoothCmd(void);

};

#endif  //__BLUETOOTH_H