#include "DeviceDrivers/IOPin.h"

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
}