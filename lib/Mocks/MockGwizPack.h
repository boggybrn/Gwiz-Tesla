#include <GwizPackInterface.h>

class MockGwizPack : public GwizPackInterface
{
public:
    float getGwizPackVoltage();
    float getHighestCellVoltage();
    float getLowestCellVoltage();
    float getLowestTemperature();
    float getHighestTemperature();
    void setGwizPackVoltage(float voltage);
    void setHighestCellVoltage(float voltage);
    void setLowestCellVoltage(float voltage);
    void setLowestTemperature(float temp);
    void setHighestTemperature(float temp);

private:
    float packVoltage;
    float highestCellVoltage;
    float lowestCellVoltage;
    float lowestTemperature;
    float highestTemperature;
};

