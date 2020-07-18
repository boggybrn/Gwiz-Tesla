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
        SerialUSB.print(cellNum+cellsInModuleA);
        SerialUSB.print(": ");
        SerialUSB.print(moduleA->getCellVoltage(cellNum), 3);
        SerialUSB.print("V");
    }
}