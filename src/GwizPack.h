#pragma once
#include "config.h"
#include "MercBclassModule.h"

class GwizPack
{
public:
    GwizPack(BMSModule *modules);
    float getGwizPackVoltage();
    void printPackDetails();

private:
    MercBclassModule chain1ModuleA;         // the pack is made up of two parallelled chains
    MercBclassModule chain1ModuleB;         // each containing two Mercedes B class modules in series    
    MercBclassModule chain2ModuleA;
    MercBclassModule chain2ModuleB;

    
   
};