#include <WiFiWebGUI.h>
#include <config.h>
#include <ChargeController.h>
#include <EEPROM.h>
#include "BMSModuleManager.h"

extern EEPROMSettings settings;
extern BMSModuleManager bms;
extern bool autoBalance;

WiFiWebGUI::WiFiWebGUI(GwizPackInterface *pack, CurrentSensor *currentSensor, ChargeController *chargeControler)
{
    myPack = pack;
    myCurrentSensor = currentSensor;
    myChargeController = chargeControler;
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
    else if (cmdString == String("status"))
    {
        String status = "";
        myPack->getPackDetails(&status);
        SERIALWIFI.print(status);
    }
    else if (cmdString == String("settings"))
    {
        String reply = "";
        reply += "Max cell limit " + String(settings.OverVSetpoint) + "V\n";
        reply += "Max charging temperature " + String(settings.OverTSetpoint) + "C\n";
        reply += "Min charging temperature " + String(settings.UnderTSetpoint) + "C\n";
        reply += "Balancing tollerance " + String(settings.balanceTollerance) + "V\n";
        reply += "Default full capacity " + String(settings.chargeInmASeconds / (3600*1000)) + "Ah";
        if(autoBalance)
            reply += "\nAutobalance in progress\n";
        SERIALWIFI.print(reply);
    }
    else if (cmdString == String("VOLTLIMHI"))
    {
        i++; //skip over the space
        float newFloat = strtof((char *)(cmdBuffer + i), NULL);
        if (newFloat >= 3.7f && newFloat <= 4.2f)
        {
            settings.OverVSetpoint = newFloat;
            String reply = "";
            reply += "\nMax cell limit " + String(newFloat) + "V\r\n";
            SERIALWIFI.print(reply);
            EEPROM.put(EEPROM_PAGE, settings); 
        }
        else
        {
            SERIALWIFI.print("\nValue out of range\r\n");
        }
        
            
    }
    else if (cmdString == String("BAL"))
    {
        i++; //skip over the space
        int balanceTime = strtol((char *)(cmdBuffer + i), NULL, 0);
        if(balanceTime > 200)
            balanceTime = 200;
        String reply = "";
        
        if(bms.balanceCells(myPack->getLowestCellVoltage(), balanceTime, 1))
        {
            reply += "\nBalancing for " + String(balanceTime) + " seconds\r\n";
        }
        else
        {
            reply += "\nNo balancing needed - cells within balancing tollerance\r\n";
        }
        SERIALWIFI.print(reply);
    }
    else if (cmdString == String("AUTOBALON"))
    {
        autoBalance = true;
        SERIALWIFI.print("Autobalance started\n");
    }
    else if (cmdString == String("AUTOBALOFF"))
    {
        autoBalance = false;
        SERIALWIFI.print("Autobalance stopped\n");
    }
    else
    {
        SERIALWIFI.print("\nUnknown Command!\r\n");
    }
}