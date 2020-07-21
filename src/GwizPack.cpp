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
}

float GwizPack::getGwizPackVoltage()
{
    return chain1ModuleA.getMercModuleVoltage();    // since the chains are wired in parallel the voltage shoud be the same on both...
}

float GwizPack::getHighestCellVoltage()
{
    float highestCellVoltage = chain1ModuleA.getHighestCellVoltage();

    if(highestCellVoltage < chain1ModuleB.getHighestCellVoltage())
    {
        highestCellVoltage = chain1ModuleB.getHighestCellVoltage();
    }
    if(highestCellVoltage < chain2ModuleA.getHighestCellVoltage())
    {
        highestCellVoltage = chain2ModuleA.getHighestCellVoltage();
    }
    if(highestCellVoltage < chain2ModuleB.getHighestCellVoltage())
    {
        highestCellVoltage = chain2ModuleB.getHighestCellVoltage();
    }
    return highestCellVoltage;
}

float GwizPack::getLowestCellVoltage()
{
    float lowestCellVoltage = chain1ModuleA.getLowestCellVoltage();

    if(lowestCellVoltage > chain1ModuleB.getLowestCellVoltage())
    {
        lowestCellVoltage = chain1ModuleB.getLowestCellVoltage();
    }
    if(lowestCellVoltage > chain2ModuleA.getLowestCellVoltage())
    {
        lowestCellVoltage = chain2ModuleA.getLowestCellVoltage();
    }
    if(lowestCellVoltage > chain2ModuleB.getLowestCellVoltage())
    {
        lowestCellVoltage = chain2ModuleB.getLowestCellVoltage();
    }
    return lowestCellVoltage;
}

void GwizPack::printPackDetails()
{
    SerialUSB.print("Chain 1 voltage ");
    SerialUSB.print(chain1ModuleA.getMercModuleVoltage() + chain1ModuleB.getMercModuleVoltage(), 3);

    SerialUSB.print("  Chain 2 voltage ");
    SerialUSB.print(chain2ModuleA.getMercModuleVoltage() + chain2ModuleB.getMercModuleVoltage(), 3);

    SerialUSB.print("\n\rChain1 Module A voltage ");
    SerialUSB.print(chain1ModuleA.getMercModuleVoltage(), 3);
    chain1ModuleA.printCellVotages();

    SerialUSB.print("\n\rChain1 Module B voltage ");
    SerialUSB.print(chain1ModuleB.getMercModuleVoltage(), 3);
    chain1ModuleB.printCellVotages();

    SerialUSB.print("\n\rChain2 Module A voltage ");
    SerialUSB.print(chain2ModuleA.getMercModuleVoltage(), 3);
    chain2ModuleA.printCellVotages();

    SerialUSB.print("\n\rChain2 Module B voltage ");
    SerialUSB.print(chain2ModuleA.getMercModuleVoltage(), 3);
    chain2ModuleB.printCellVotages();

    SerialUSB.print("\n\rHighest cell voltage ");
    SerialUSB.print(getHighestCellVoltage(), 3);

    SerialUSB.print("\n\rLowest cell voltage ");
    SerialUSB.print(getLowestCellVoltage(), 3);

    SerialUSB.print("\n\r");
}
