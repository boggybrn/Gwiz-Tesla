#include "GwizPack.h"

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
    return 0;
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

    SerialUSB.print("\n\r");
}
