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

float MockGwizPack::getLowestTemperature()
{
    return lowestTemperature;
}
float MockGwizPack::getHighestTemperature()
{
    return highestTemperature;
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

void MockGwizPack::setLowestTemperature(float temp)
{
    lowestTemperature = temp;
}

void MockGwizPack::setHighestTemperature(float temp)
{
    highestTemperature = temp;
}