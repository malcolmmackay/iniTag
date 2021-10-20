# RFM69HCW-868-S2 Partial HAT for pi Zero
This project includes KiCAD 5.0 CAD files to make a pi Zero HAT with connections from SPI0 device 0 to an RFM69HCW-868-S2 868 MHz transceiver. It was inspired by the OpenAPS project: https://github.com/openaps/openaps.

![Photo of pHAT connected to pi Zero](photo_version_1.jpg)

This board makes connections from the table on https://openaps.readthedocs.io/en/latest/docs/Gear%20Up/edison.html#hardware-information-for-pi-based-setups-with-rfm69hcw-experimental 

| Board | Connect | Connect | Connect | Connect | Connect | Connect | Connect | Connect |
| ----- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- |
| RPi | 3.3V | GND | MOSI | MISO | SCLK | | CEO_N | | 
| RPi PIN | 17 | 25 | 19 | 21 | 23 | 16 | 24 | 18 |
| RFM69HCW | VIN or 3.3V | GND | MOSI | MISO | SCK or CLK | G0 or DIO0 | CS or NSS | RST or RESET |

One of five prototypes made by Eurocircuits for £42 was tested successfully with OpenAPS after following instructions to switch to the development branch. 

