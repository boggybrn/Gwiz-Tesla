#include "MercBclassModule.h"

const int cellsInModuleA = 4;
const int cellsInModuleB = 3;

MercBclassModule::MercBclassModule()
{
}

void MercBclassModule::setModules(BMSModule *firstModule, BMSModule *secondModule)
{
    moduleA = firstModule;
    moduleB = secondModule;
}

float MercBclassModule::getMercModuleVoltage()
{
    return moduleA->getModuleVoltage() + moduleB->getModuleVoltage();
}

float MercBclassModule::getLowestCellVoltage()
{
    float lowestVoltage = 5.0f;

    for (int cellNum = 0; cellNum < cellsInModuleA; cellNum++)
    {
        if (lowestVoltage > moduleA->getCellVoltage(cellNum))
        {
            lowestVoltage = moduleA->getCellVoltage(cellNum);
        }
    }
    for (int cellNum = 0; cellNum < cellsInModuleB; cellNum++)
    {
        if (lowestVoltage > moduleB->getCellVoltage(cellNum))
        {
            lowestVoltage = moduleB->getCellVoltage(cellNum);
        }
    }
    return lowestVoltage;
}

float MercBclassModule::getHighestCellVoltage()
{
    float highestVoltage = 0;

    for (int cellNum = 0; cellNum < cellsInModuleA; cellNum++)
    {
        if (highestVoltage < moduleA->getCellVoltage(cellNum))
        {
            highestVoltage = moduleA->getCellVoltage(cellNum);
        }
    }
    for (int cellNum = 0; cellNum < cellsInModuleB; cellNum++)
    {
        if (highestVoltage < moduleB->getCellVoltage(cellNum))
        {
            highestVoltage = moduleB->getCellVoltage(cellNum);
        }
    }
    return highestVoltage;
}

float MercBclassModule::getLowestTemperature()
{
    float lowestTemp = moduleA->getLowestTemp();

    if(lowestTemp > moduleB->getLowestTemp())
        lowestTemp =  moduleB->getLowestTemp();

    return lowestTemp;    
}

float MercBclassModule::getHighestTemperature()
{
    float highestTemp = moduleA->getHighestTemp();

    if(highestTemp > moduleB->getHighestTemp())
        highestTemp =  moduleB->getHighestTemp();

    return highestTemp; 
}

void MercBclassModule::printCellVotages()
{
    for (int cellNum = 0; cellNum < cellsInModuleA; cellNum++)
    {
        SerialUSB.print("  Cell");
        SerialUSB.print(cellNum);
        SerialUSB.print(": ");
        SerialUSB.print(moduleA->getCellVoltage(cellNum), 3);
        SerialUSB.print("V");
    }
    for (int cellNum = 0; cellNum < cellsInModuleB; cellNum++)
    {
        SerialUSB.print("  Cell");
        SerialUSB.print(cellNum + cellsInModuleA);
        SerialUSB.print(": ");
        SerialUSB.print(moduleB->getCellVoltage(cellNum), 3);
        SerialUSB.print("V");
    }
}