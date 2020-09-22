#ifndef __WIFI_WEB_GUI_H
#define __WIFI_WEB_GUI_H

#include <GwizPackInterface.h>

class WiFiWebGUI
{
private:
    GwizPackInterface *myPack;
    char cmdBuffer[80];
    int ptrBuffer;

public:
    WiFiWebGUI(GwizPackInterface *pack);
    void init(void);
    void service(void);
    void mySerialEvent(void);
    void handleWiFiCmd(void);

};

#endif  //__WIFI_WEB_GUI_H