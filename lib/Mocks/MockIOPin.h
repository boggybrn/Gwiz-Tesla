#include <PinInterface.h>
#include <stdint.h>

class MockIOPin : public PinInterface
{

private:
    uint32_t myPin;
    uint32_t pinValue;

public:
    MockIOPin(uint32_t pin) { myPin = pin; };

    void doDigitalWrite(uint32_t val);
    int doDigitalRead(void);
    void doAnalogWrite(uint32_t value);

    // functions used in test cases
    uint32_t getPinValue(void);
    void setPinValue(uint32_t val);
    void init(void);
};