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

float MercBclassModule::getLowestTemperatureNow()
{
    float lowestTemp = moduleA->getTemperature(0);

    if(lowestTemp > moduleA->getTemperature(1))     //two temperature sensors per module - but it isn't clear if the second one does anything!
        lowestTemp =  moduleA->getTemperature(1);

    if(lowestTemp > moduleB->getTemperature(0))
        lowestTemp =  moduleB->getTemperature(0);

    if(lowestTemp > moduleB->getTemperature(1))
        lowestTemp =  moduleB->getTemperature(1);

    return lowestTemp;    
}

float MercBclassModule::getHighestTemperatureNow()
{
    float highestTemp = moduleA->getTemperature(0);

    if(highestTemp < moduleA->getTemperature(1))
        highestTemp =  moduleA->getTemperature(1);

    if(highestTemp < moduleB->getTemperature(0))
        highestTemp =  moduleB->getTemperature(0);

    if(highestTemp < moduleB->getTemperature(1))
        highestTemp =  moduleB->getTemperature(1);    

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