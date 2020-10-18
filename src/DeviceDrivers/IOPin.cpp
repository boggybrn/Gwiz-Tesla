#include "DeviceDrivers/IOPin.h"
#include "Logger.h"

void IOPin::doDigitalWrite(uint32_t val)
{
    digitalWrite(myPin, val);
}

int IOPin::doDigitalRead(void)
{
    return digitalRead(myPin);
}

void IOPin::doAnalogWrite(uint32_t value)
{
    analogWrite(myPin, value);
    Logger::console("   Pin %d set to %d\r\n", myPin, value);
}