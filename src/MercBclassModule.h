#pragma once
#include "config.h"
#include "BMSModule.h"

class MercBclassModule
{
public:
    MercBclassModule();
    void setModules(BMSModule *firstModule, BMSModule *secondModule);
    void printCellVotages();
    float getMercModuleVoltage();

private:
    float MercBclassModuleVolt;                    // Both Tesla module voltages added together

    BMSModule *moduleA = nullptr;
    BMSModule *moduleB = nullptr;
   
};