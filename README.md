# Gwiz-TeslaBMS
Arduino compatible project to interface with the BMS slave board on Tesla battery modules from a Mercedes B Class car and to control a Reva G-Wiz charger. Note that this is intended to run on an STM32 Blue Pill board with appropriate surrounding hardware. Details of the hardware can be found here: https://github.com/boggybrn/Gwiz-TeslaBMS-PCB

Inspirtion and code borrowed from: https://github.com/collin80/TeslaBMS and https://github.com/tomdebree/TeslaBMSV2

At present this charges the battery to a set voltage, but tapers the charging current as that voltage is approached. It is still somewhat a Work In Progress. It supports a serial interface to a PC - via an FTDI board to convert this to USB. It also supports a serial interface to an ESP8266 WiFi / web server module. Code for that is still being written but is basically as per https://github.com/jsphuebner/esp8266-web-interface

The Tesla / Mercedes modules are daisy-chained together with a TTL interface. The interface uses a Molex 15-97-5101 connector and runs at 612500 baud. The factory wiring to each module is comprised of two sets of 5 differently colored wires:

Red = 5V input to the module
Green = Gnd for power and signal
Gray = Fault output
Yellow = UART Wire
Blue = UART Wire
The fault output is active low. Use your own pull up to the fault line and if the line is pulled low then a fault has occurred.

Here is a PDF that explains how the wiring between modules and the master board is supposed to be: https://cdn.hackaday.io/files/10098432032832/wiring.pdf
