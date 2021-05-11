# mosaicHAT Arduino receiver
<img src="doc/mosaicHAT_Arduino.png" width="60%">

A basic GPS/GNSS receiver based on <a href="https://github.com/septentrio-gnss/mosaicHAT">mosaicHAT</a> and Arduino. The Arduino code reads GPS/GNSS data (NMEA format) messages from <a href="https://github.com/septentrio-gnss/mosaicHAT">mosaicHAT</a>, a Raspberry Pi compatible PCB based on <a href="https://www.septentrio.com/en/products/gnss-receivers/rover-base-receivers/receivers-module/mosaic">Septentrio's mosaic-X5</a>, and shows desired data on LCD display.

<img src="doc/mosaicHAT_receiver_.jpg" width="60%">

mosaicHAT Arduino: Making the mosaicHAT work with Arduino </br>
Author: (Jamal Sa'd) <jamalhazem127@gmail.com> </br>

## Design
The code is based on the following connections:

<img src="doc/receiver_schematic.png" width="60%">

## mosaic-X5 configuration
The Arduino program expects NMEA GGA messages from mosaicHAT serial (COM2). To configure <a href="https://www.septentrio.com/en/products/gnss-receivers/rover-base-receivers/receivers-module/mosaic">mosaic-X5</a>, connect the board to PC via USB and open mosaic webUI on default address **"192.168.3.1"**
 
- Go to the **Communication** tab and choose **Serial**.
- Change the baud rate of **COM2** to **9600**.
- Click Ok for changes to take effect.
- Go to **NMEA/SBF Out** and choose **New NMEA Stream**.
- Select **Serial** connection type then **COM2** as connection/port.
- Keep the default interval **(1 sec)** and select **GGA** as a message to output.
- Click Ok for changes to take effect.
- Now a popup message will ask if you would like to save the **current configuration as a boot configuration**. Choose Save.

### Deliverables on this project
This project makes the following deliverables for both integrators and designers of systems around Septentrio's mosaic modules.

|File|Description|
|--------|----------|
|mosaicHAT_Arduino/mosaicHAT_Arduino.ino| Arduino Sample code |


## Check the project on Instructables
<img src="doc/instructables-logo.png" width="60%">

All steps of making the project are available on instructables! Check: (https://www.instructables.com/Building-a-GNSS-Receiver-Using-MosaicHAT-and-Ardui/)
