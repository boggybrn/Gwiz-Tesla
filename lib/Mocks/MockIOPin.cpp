#ifdef UNIT_TEST
#include "MockIOPin.h"


void MockIOPin::setPinValue(uint32_t val)
{
    pinValue = val;
}

uint32_t MockIOPin::getPinValue(void)
{
    return pinValue;
}

void MockIOPin::doDigitalWrite(uint32_t val)
{
    pinValue = val;
}

int MockIOPin::doDigitalRead(void)
{
    return pinValue;
}

void MockIOPin::doAnalogWrite(uint32_t value)
{
    pinValue = value;
}

#endif