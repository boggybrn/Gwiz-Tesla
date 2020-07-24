#include <GwizPackInterface.h>

class MockGwizPack : public GwizPackInterface
{
public:
    float getGwizPackVoltage();
    float getHighestCellVoltage();
    float getLowestCellVoltage();
    void setGwizPackVoltage(float voltage);
    void setHighestCellVoltage(float voltage);
    void setLowestCellVoltage(float voltage);

private:
    float packVoltage;
    float highestCellVoltage;
    float lowestCellVoltage;
};

