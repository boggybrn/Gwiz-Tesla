#ifndef __WIFI_WEB_GUI_H
#define __WIFI_WEB_GUI_H

#include <GwizPackInterface.h>
#include <CurrentSensor.h>

class WiFiWebGUI
{
private:
    GwizPackInterface *myPack;
    CurrentSensor *myCurrentSensor;
    char cmdBuffer[80];
    int ptrBuffer;

public:
    WiFiWebGUI(GwizPackInterface *pack, CurrentSensor *currentSensor);
    void init(void);
    void service(void);
    void mySerialEvent(void);
    void handleWiFiCmd(void);

};

#endif  //__WIFI_WEB_GUI_H