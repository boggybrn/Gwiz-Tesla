#include <PinInterface.h>
#include <Arduino.h>

class IOPin : public PinInterface
{
private:
    uint32_t myPin;

public:
    IOPin(uint32_t pin) { myPin = pin; };

public:
    void doDigitalWrite(uint32_t val);
    int doDigitalRead(void);
    void doAnalogWrite(uint32_t value);
};