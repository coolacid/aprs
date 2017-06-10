#!/bin/env python
import aprslib, pprint

# Put the output from the APRS message into "message" and hope it works

message = "VE3YCA-4>APRS-0,DIGI2-1,DIGI1-1:/092231h4437.28N/07930.57Ws000/000/A=000897/Comment"

packet = aprslib.parse(message)

pprint.pprint(packet)
