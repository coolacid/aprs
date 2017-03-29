# aprs
Mini-APRS Transmitter

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

