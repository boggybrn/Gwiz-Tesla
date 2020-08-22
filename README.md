# Gwiz-TeslaBMS
Arduino compatible project to interface with the BMS slave board on Tesla Model S modules and to control a Reva G-Wiz charger. Note that this is intended to run on an STM32 Blue Pill board with appropriate surrounding hardware.

The modules are daisy-chained together with a TTL interface. The interface uses a Molex 15-97-5101 connector and runs at 612500 baud. The factory wiring to each module is comprised of two sets of 5 differently colored wires:

Red = 5V input to the module
Green = Gnd for power and signal
Gray = Fault output
Yellow = UART Wire
Blue = UART Wire
The fault output is active low. Use your own pull up to the fault line and if the line is pulled low then a fault has occurred.

Here is a PDF that explains how the wiring between modules and the master board is supposed to be: https://cdn.hackaday.io/files/10098432032832/wiring.pdf
