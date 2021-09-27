#include <Bluetooth.h>
#include <config.h>
#include <ChargeController.h>

Bluetooth::Bluetooth(GwizPackInterface *pack, CurrentSensor *currentSensor, ChargeController *chargeControler)
{
    myPack = pack;
    myCurrentSensor = currentSensor;
    myChargeController = chargeControler;
}

void Bluetooth::init(void)
{
    SERIALWIFI.begin(SERIALWIFI_BAUD);
    ptrBuffer = 0;
    rn4871InfoMode = false;
}

void Bluetooth::service(void)
{
    if (SERIALWIFI.available())
    {
        mySerialEvent();
    }
}

void Bluetooth::mySerialEvent(void)
{
    int incoming;
    incoming = SERIALWIFI.read();
    if (incoming == -1)
    { //false alarm....
        return;
    }

    if (incoming == '%') //marks the start of information from the rn4871 module
    {
        if(rn4871InfoMode)
        {
            rn4871InfoMode = false;
            ptrBuffer = 0;
        } 
        else
        {
            rn4871InfoMode = true;
        }
        return;
    }
    if (!rn4871InfoMode)
    {
        if (incoming == 10 || incoming == 13)
        { //command done. Parse it.
            handleBluetoothCmd();
            ptrBuffer = 0; //reset line counter once the line has been processed
        }
        else
        {
            cmdBuffer[ptrBuffer++] = (unsigned char)incoming;
            if (ptrBuffer > 79)
                ptrBuffer = 79;
        }
    }
    
}

void Bluetooth::handleBluetoothCmd(void)
{
    int i;

    // SERIALWIFI.print("\nhello!\r\n");
    cmdBuffer[ptrBuffer] = 0; //make sure to null terminate
    String cmdString = String();

    i = 0;

    while (cmdBuffer[i] != ' ' && i < ptrBuffer)
    {
        cmdString.concat(String(cmdBuffer[i++]));
    }

    if (cmdString == String("get"))
    {
        i++; //skip over the space

        String argString = String();

        while (i < ptrBuffer)
        {
            while ((cmdBuffer[i] != ',' || cmdBuffer[i] == 0) && (i < ptrBuffer))
            {
                argString.concat(String(cmdBuffer[i++]));
            }
            if (argString == String("vbat"))
            {
                SERIALWIFI.print(myPack->getGwizPackVoltage(), 1);
                SERIALWIFI.print("\r\n");
            }
            else
            {
                if (argString == String("tbat"))
                {
                    SERIALWIFI.print(myPack->getHighestTemperature(), 1);
                    SERIALWIFI.print("\r\n");
                }
                else
                {
                    if (argString == String("ibat"))
                    {
                        SERIALWIFI.print(myCurrentSensor->getCurrentInAmps(), 2);
                        SERIALWIFI.print("\r\n");
                    }
                    else
                    {
                        if (argString == String("cbat"))
                        {
                            float chargeInAH = (float)(myCurrentSensor->getChargeInmASeconds() / 3600) / 1000; //return in AH for display
                            SERIALWIFI.print((float)(chargeInAH), 2);
                            SERIALWIFI.print("\r\n");
                        }
                    }
                }
            }
            i++; //skip over separator
            argString = String("");
        }
    }
    else if (cmdString == String("start"))
    {
        switch (myChargeController->manualStart())
        {
        case STARTED:
            SERIALWIFI.print("\nCharging Started\r\n");
            break;
        case TOO_COLD_TO_START:
            SERIALWIFI.print("\nToo cold to charge\r\n");
            break;
        case TOO_HOT_TO_START:
            SERIALWIFI.print("\nToo hot to charge\r\n");
            break;
        case NO_AC_CONNECTED:
            SERIALWIFI.print("\nNot plugged in to AC power\r\n");
            break;
        }
    }
    else if (cmdString == String("stop"))
    {
        myChargeController->manualStop();
        SERIALWIFI.print("\nCharging Stopped\r\n");
    }
    else
    {
        SERIALWIFI.print("\nUnknown Command\r\n");
    }
}