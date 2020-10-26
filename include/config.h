#pragma once

#include <Arduino.h>
#include "EEPROMSettings.h"

//Set to the proper port for your USB connection - SerialUSB on Due (Native) or Serial for Due (Programming) or Teensy
#define SERIALCONSOLE   Serial
#define SerialUSB       Serial

//Define this to be the serial port the Tesla BMS modules are connected to.
//On the Due you need to use a USART port (Serial1, Serial2, Serial3) and update the call to serialSpecialInit if not Serial1
#define SERIAL  Serial3

//Define this to be the serial port to the WiFi module that runs the web interface
#define SERIALWIFI  Serial2
#define SERIALWIFI_BAUD 115200

//define the ports used to control the charger
#define CRG_AC_AVAIL_PORT   PB15
#define CHG_AC_AVAIL        0       // low signifies that AC is connected
#define CHG_CURRENT_PORT    PB14
#define CHG_VOLTAGE_PORT    PB13
#define CHG_FAN_PORT        PB4

#define REG_DEV_STATUS      0
#define REG_GPAI            1
#define REG_VCELL1          3
#define REG_VCELL2          5
#define REG_VCELL3          7
#define REG_VCELL4          9
#define REG_VCELL5          0xB
#define REG_VCELL6          0xD
#define REG_TEMPERATURE1    0xF
#define REG_TEMPERATURE2    0x11
#define REG_ALERT_STATUS    0x20
#define REG_FAULT_STATUS    0x21
#define REG_COV_FAULT       0x22
#define REG_CUV_FAULT       0x23
#define REG_ADC_CTRL        0x30
#define REG_IO_CTRL         0x31
#define REG_BAL_CTRL        0x32
#define REG_BAL_TIME        0x33
#define REG_ADC_CONV        0x34
#define REG_ADDR_CTRL       0x3B

#define MAX_MODULE_ADDR     0x3E

#define EEPROM_VERSION      0x13    //update any time EEPROM struct below is changed.
#define EEPROM_PAGE         0

#define DIN1                55
#define DIN2                54
#define DIN3                57
#define DIN4                56
#define DOUT4_H             2
#define DOUT4_L             3
#define DOUT3_H             4
#define DOUT3_L             5
#define DOUT2_H             6
#define DOUT2_L             7
#define DOUT1_H             8
#define DOUT1_L             9


