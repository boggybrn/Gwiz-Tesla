#if defined(__arm__) && defined(__SAM3X8E__)
#include <chip.h>
#endif

#include <Arduino.h>
#include "Logger.h"
#include "SerialConsole.h"
#include "BMSModuleManager.h"
#include "SystemIO.h"
#include "GwizPack.h"

//#define BMS_BAUD  612500
#define BMS_BAUD 617647
//#define BMS_BAUD  608695

HardwareSerial Serial3(PB11, PB10);

BMSModuleManager bms;
GwizPack gwiz(bms.modules);
EEPROMSettings settings;
SerialConsole console;
uint32_t lastUpdate;

void loadSettings()
{
    //EEPROM.read(EEPROM_PAGE, settings);

    // if (settings.version != EEPROM_VERSION) //if settings are not the current version then erase them and set defaults
    // {
    Logger::console("Resetting to factory defaults");
    settings.version = EEPROM_VERSION;
    settings.checksum = 0;
    settings.OverVSetpoint = 4.1f;
    settings.UnderVSetpoint = 3.1f;
    settings.OverTSetpoint = 65.0f;
    settings.UnderTSetpoint = -10.0f;
    settings.balanceVoltage = 3.9f;
    settings.balanceHyst = 0.04f;
    settings.logLevel = 2;
    //   EEPROM.write(EEPROM_PAGE, settings);
    // }
    // else {
    //     Logger::console("Using stored values from EEPROM");
    // }

    Logger::setLoglevel((Logger::LogLevel)settings.logLevel);
}

void setup()
{

    SERIALCONSOLE.begin(115200);
    SERIALCONSOLE.println("Starting up!");
    SERIAL.begin(BMS_BAUD);

    SERIALCONSOLE.println("Started serial interface to BMS.");

    //pinMode(13, INPUT);

    loadSettings();

    systemIO.setup();

    bms.renumberBoardIDs();

    //Logger::setLoglevel(Logger::Debug);

    lastUpdate = 0;

    bms.clearFaults();

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on

    // initialise the PWM pins for charger current control
    pinMode(CRG_AC_AVAIL_PORT, INPUT); // pin to detect when the charger is plugged in to 230V AC
    pinMode(CHG_CURRENT_PORT, OUTPUT); // pin to control charging current
    pinMode(CHG_VOLTAGE_PORT, OUTPUT); //pin to control charging voltage

    analogWrite(CHG_VOLTAGE_PORT, 255); // set the minimum voltage to ensure that the charger is off
    analogWrite(CHG_CURRENT_PORT, 225); // and set to the minimum current by default
}

void loop()
{
    // CAN_FRAME incoming;
    static bool ledState = false;
    static int chargerState = 0;
    
    console.loop();

    if (millis() > (lastUpdate + 1000))
    {
        lastUpdate = millis();
        // bms.balanceCells();
        bms.getAllVoltTemp();
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState); // toggle the LED
        if (digitalRead(CRG_AC_AVAIL_PORT))
        {
            if(chargerState != 1)
                SERIALCONSOLE.println("Charger AC disconnected");
            chargerState = 1;    
        }
        else
        {
            if(chargerState != 2)
                SERIALCONSOLE.println("Charger AC connected");
            chargerState = 2;    
        }
        
    }
}
