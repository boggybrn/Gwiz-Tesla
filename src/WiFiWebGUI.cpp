#include <WiFiWebGUI.h>
#include <config.h>

WiFiWebGUI::WiFiWebGUI(GwizPackInterface *pack)
{
    myPack = pack;
}

void WiFiWebGUI::init(void)
{
    SERIALWIFI.begin(SERIALWIFI_BAUD);
    ptrBuffer = 0;
}

void WiFiWebGUI::service(void)
{
    if (SERIALWIFI.available())
    {
        mySerialEvent();
    }
}

void WiFiWebGUI::mySerialEvent(void)
{
    int incoming;
    incoming = SERIALWIFI.read();
    if (incoming == -1)
    { //false alarm....
        return;
    }

    if (incoming == 10 || incoming == 13)
    { //command done. Parse it.
        handleWiFiCmd();
        ptrBuffer = 0; //reset line counter once the line has been processed
    }
    else
    {
        cmdBuffer[ptrBuffer++] = (unsigned char)incoming;
        if (ptrBuffer > 79)
            ptrBuffer = 79;
    }
}

void WiFiWebGUI::handleWiFiCmd(void)
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
                    SERIALWIFI.print("r\n");
                }
            }
            i++; //skip over separator
            argString = String("");
        }
    }
    else
    {
        SERIALWIFI.print("\nUnknown Command\r\n");
    }
}