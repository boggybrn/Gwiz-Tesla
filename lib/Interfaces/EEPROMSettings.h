#include <stdint.h>

typedef struct {
    uint8_t version;
    uint8_t checksum;
    uint8_t logLevel;
    float OverVSetpoint;
    float UnderVSetpoint;
    float OverTSetpoint;
    float UnderTSetpoint;
    float balanceVoltage;
    float balanceHyst;
    float balanceTollerance;
} EEPROMSettings;