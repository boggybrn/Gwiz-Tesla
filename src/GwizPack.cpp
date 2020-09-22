/*****************************************************************************************
 * The pack in the G-Wiz is made up of 4 Mercedes B-Class battery modules - wired as two
 * paralel chains each containing two modules.
 * 
 * This class models that configuration and provides pack level information eg. pack
 * voltage, highest and lowest cell voltages and (at some poit) highest and lowaest pack 
 * temperature readings.
 * 
 */ 

#include "GwizPack.h"
#include "MercBclassModule.h"

GwizPack::GwizPack(BMSModule *modules)
{
    // this provides the map of how the Tesla modules appear in the pack, so needs to
    // match the order in which the modules are wired in the daisy chain!
    chain1ModuleA.setModules(&modules[1], &modules[2]);
    chain1ModuleB.setModules(&modules[3], &modules[4]);
    chain2ModuleA.setModules(&modules[5], &modules[6]);
    chain2ModuleB.setModules(&modules[7], &modules[8]);

    // set up an array of pointers to these modules, for easy iteration through them
    myModules[0] = &chain1ModuleA;
    myModules[1] = &chain1ModuleB;
    myModules[2] = &chain2ModuleA;
    myModules[3] = &chain2ModuleB;

}

float GwizPack::getGwizPackVoltage()
{
    return chain1ModuleA.getMercModuleVoltage() + chain1ModuleB.getMercModuleVoltage();    // since the chains are wired in parallel the voltage shoud be the same on both...
}

float GwizPack::getLowestTemperature()
{
    float lowestTemperature = 100;

    for(int i = 0 ; i < MODULES_IN_PACK ; i++)
    {
        if(myModules[i]->getLowestTemperatureNow() < lowestTemperature)
        {
            lowestTemperature = myModules[i]->getLowestTemperatureNow();
        }
    }
    return lowestTemperature;
}

float GwizPack::getHighestTemperature()
{
    float highestTemperature = -50;

    for(int i = 0 ; i < MODULES_IN_PACK ; i++)
    {
        if(myModules[i]->getHighestTemperatureNow() > highestTemperature)
        {
            highestTemperature = myModules[i]->getHighestTemperatureNow();
        }
    }
    return highestTemperature;
}

float GwizPack::getHighestCellVoltage()
{
    float highestCellVoltage = 0;

    for(int i = 0 ; i < MODULES_IN_PACK ; i++)
    {
        if(myModules[i]->getHighestCellVoltage() > highestCellVoltage)
        {
            highestCellVoltage = myModules[i]->getHighestCellVoltage();
        }
    }
    return highestCellVoltage;
}

float GwizPack::getLowestCellVoltage()
{
    float lowestCellVoltage = 5;
    
    for(int i = 0 ; i < MODULES_IN_PACK ; i++)
    {
        if(myModules[i]->getLowestCellVoltage() < lowestCellVoltage)
        {
            lowestCellVoltage = myModules[i]->getLowestCellVoltage();
        }
    }
    return lowestCellVoltage;
}

void GwizPack::printPackDetails()
{
    SerialUSB.print("Chain 1 voltage ");
    SerialUSB.print(chain1ModuleA.getMercModuleVoltage() + chain1ModuleB.getMercModuleVoltage(), 3);

    SerialUSB.print("  Chain 2 voltage ");
    SerialUSB.print(chain2ModuleA.getMercModuleVoltage() + chain2ModuleB.getMercModuleVoltage(), 3);

    SerialUSB.print("\nChain1 Module A voltage ");
    SerialUSB.print(chain1ModuleA.getMercModuleVoltage(), 3);
    chain1ModuleA.printCellVotages();

    SerialUSB.print("\nChain1 Module B voltage ");
    SerialUSB.print(chain1ModuleB.getMercModuleVoltage(), 3);
    chain1ModuleB.printCellVotages();

    SerialUSB.print("\nChain2 Module A voltage ");
    SerialUSB.print(chain2ModuleA.getMercModuleVoltage(), 3);
    chain2ModuleA.printCellVotages();

    SerialUSB.print("\nChain2 Module B voltage ");
    SerialUSB.print(chain2ModuleA.getMercModuleVoltage(), 3);
    chain2ModuleB.printCellVotages();

    SerialUSB.print("\nHighest cell voltage ");
    SerialUSB.print(getHighestCellVoltage(), 3);

    SerialUSB.print("  Lowest cell voltage ");
    SerialUSB.print(getLowestCellVoltage(), 3);

    SerialUSB.print("  Cell voltage difference ");
    SerialUSB.print(getHighestCellVoltage() - getLowestCellVoltage(), 3);

    SerialUSB.print("\nHighest temperature ");
    SerialUSB.print(getHighestTemperature(), 2);

    SerialUSB.print("  Lowest temperature ");
    SerialUSB.print(getLowestTemperature(), 2);

    SerialUSB.print("\n");
}
