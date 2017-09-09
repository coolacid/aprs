# aprs
Mini-APRS Transmitter

(Note alot of these notes are now VERY wrong -- I'll update these later)

This project is combining a bunch of pieces together to greate a small 1w APRS transmitter. This can be connected to an external RF AMP for extended coverage. 

Bits and Pieces:
- GYNEO6MV2 GPS Module ~ $5 USD
- DRA818V 2M Transiver ~ $15 USD
- ESP12E 8266 Devkit v2 ~ $5 USD
- Atmega 128 with Arduino Bootloader ~ $2 USD
- Total Cost (Not including extra bits and board): ~ $30 USD

# sendafsk 

Arduino Sketch that takes a serial APRS message and transmits it - Also, will take DRA818V commands and pass them on. 

This is strongly based on the Trackuino code (actually, most of it is from that project) - See https://github.com/trackuino/trackuino

# sketch 

(Needs to be renamed) 

8266 Sketch that Interfaces the GPS and sendafsk with a handy Wifi front-end. 

# Using ESP12E Devkit as Arduino

http://www.instructables.com/id/The-First-Usage-of-NodeMCU-ESP12E-DEVKIT-V2/

This project is using the same basis as http://www.f4huy.fr/?p=906 however, will probably be different and our own brand of weird. 


ESP12E Pinouts:
- D0 - GPS Fix LED
- D2 - GPS TX
- D3 - GPS RX

# AX25/AFSK Libraries

Eventually it would be nice to make the 8266 do the ASFK - but, there is pin limitations - so maybe the current way is best.

Current issue is getting AFSK working on the ESP8266 (ESP12E). This is a list of Libraries implementing this, however none work with the ESP.
- https://github.com/kronenpj/AX25 - AVR specific code ( Forked from: https://github.com/slepp/ax25 )
- https://github.com/trackuino/trackuino - AVR and PIC32 specific code

Ones that use a specific modem board:
- https://github.com/kicksat/ax25 ( HopeRF Board)
- https://github.com/markqvist/MicroModem ( Micromodem )

# APRS Nodes:
- q Codes in a path: http://www.aprs-is.net/q.aspx
- DIGI Paths: http://wa8lmf.net/DigiPaths/

# Notes for Rev2
- https://deeplyembedded.wordpress.com/2016/11/21/esp8266_spi/

# building

To build
`platformio run -e [enviroment:brains/sendafsk]`

To push
`platformio run -e [enviroment:brains/sendafsk] -t upload`
