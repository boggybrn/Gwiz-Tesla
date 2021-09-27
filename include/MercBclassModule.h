#pragma once
#include "config.h"
#include "BMSModule.h"

class MercBclassModule
{
public:
    MercBclassModule();
    void setModules(BMSModule *firstModule, BMSModule *secondModule);
    void printCellVotages();
    void getCellVotages(String *);
    float getMercModuleVoltage();
    float getLowestCellVoltage();
    float getHighestCellVoltage();
    float getLowestTemperatureNow();
    float getHighestTemperatureNow();

private:
    float MercBclassModuleVolt;                    // Both Tesla module voltages added together

    BMSModule *moduleA = nullptr;
    BMSModule *moduleB = nullptr;
   
};