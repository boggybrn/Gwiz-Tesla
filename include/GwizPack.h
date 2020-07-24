#pragma once
#include "config.h"
#include "MercBclassModule.h"
#include <GwizPackInterface.h>

class GwizPack : public GwizPackInterface
{
public:
    GwizPack(BMSModule *modules);
    float getGwizPackVoltage();
    void printPackDetails();
    float getHighestCellVoltage();
    float getLowestCellVoltage();

private:
    MercBclassModule chain1ModuleA;         // the pack is made up of two parallelled chains
    MercBclassModule chain1ModuleB;         // each containing two Mercedes B class modules in series    
    MercBclassModule chain2ModuleA;
    MercBclassModule chain2ModuleB;

    
   
};