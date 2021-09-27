#pragma once
#include "config.h"
#include "MercBclassModule.h"
#include <GwizPackInterface.h>


#define MODULES_IN_PACK 4

class GwizPack : public GwizPackInterface
{
public:
    GwizPack(BMSModule *modules);
    float getGwizPackVoltage();
    void getPackDetails(String *);
    void printPackDetails();
    float getHighestCellVoltage();
    float getLowestCellVoltage();
    float getLowestTemperature();
    float getHighestTemperature();

private:
    MercBclassModule chain1ModuleA;         // the pack is made up of two parallelled chains
    MercBclassModule chain1ModuleB;         // each containing two Mercedes B class modules in series    
    MercBclassModule chain2ModuleA;
    MercBclassModule chain2ModuleB;
    MercBclassModule *myModules[MODULES_IN_PACK];
};