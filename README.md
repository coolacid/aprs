# aprs
Mini-APRS Transmitter

(Note alot of these notes are now VERY wrong -- I'll update these later)

sendafsk - Arduino Sketch that takes a serial APRS message and transmits it - Also, will take DRA818V commands and pass them on. 
sketch - (Needs to be renamed) 8266 Sketch that Interfaces the GPS and sendafsk with a handy Wifi front-end. 

This project is combining a bunch of pieces together to greate a small 1w APRS transmitter. This can be connected to an external RF AMP for extended coverage. 

# Using ESP12E Devkit as Arduino

http://www.instructables.com/id/The-First-Usage-of-NodeMCU-ESP12E-DEVKIT-V2/

This project is using the same basis as http://www.f4huy.fr/?p=906 however, will probably be different and our own brand of weird. 

Bits and Pieces:
- GYNEO6MV2 GPS Module ~ $5-$10 USD on ebay ( http://www.ebay.ca/itm/GYNEO6MV2-GPS-Module-NEO-6M-GY-NEO6MV2-Board-with-Antenna-for-Arduino/182474575363 )
- DRA818V 2M Transiver ~ $12 USD on ebay ( http://www.ebay.ca/itm/DRA818V-144MHz-145MHz-146MHz-154MHz-174MHz-VHF-HAM-Radio-Module-Amateur-Radio-/152235583482 )
- ESP12E Devkit v2 ~ $4 USD on ebay ( http://www.ebay.ca/itm/ESP8266-ESP-12E-CH340G-WIFI-Network-Development-Board-Module-For-NodeMcu-Lua-/112230225390 )

ESP12E Pinouts:
- D0 - GPS Fix LED
- D2 - GPS TX
- D3 - GPS RX

# AX25/AFSK Libraries

Current issue is getting AFSK working on the ESP8266 (ESP12E). This is a list of Libraries implementing this, however none work with the ESP.
- https://github.com/kronenpj/AX25 - AVR specific code ( Forked from: https://github.com/slepp/ax25 )
- https://github.com/trackuino/trackuino - AVR and PIC32 specific code

Ones that use a specific modem board:
- https://github.com/kicksat/ax25 ( HopeRF Board)
- https://github.com/markqvist/MicroModem ( Micromodem )
