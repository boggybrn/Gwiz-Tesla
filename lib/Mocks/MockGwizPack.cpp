#include "MockGwizPack.h"

float MockGwizPack::getGwizPackVoltage()
{
    return packVoltage;
}
float MockGwizPack::getHighestCellVoltage()
{
    return highestCellVoltage;
}
float MockGwizPack::getLowestCellVoltage()
{
    return lowestCellVoltage;
}
void MockGwizPack::setGwizPackVoltage(float voltage)
{
    packVoltage = voltage;
}
void MockGwizPack::setHighestCellVoltage(float voltage)
{
    highestCellVoltage = voltage;
}
void MockGwizPack::setLowestCellVoltage(float voltage)
{
    lowestCellVoltage = voltage;
}