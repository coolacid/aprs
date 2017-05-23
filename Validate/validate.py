#!/bin/env python
import aprslib, pprint

# Put the output from the APRS message into "message" and hope it works

message = "/232156h4437.28N/07930.57Ws000/000/A=000831"

packet = aprslib.parse("FAKE-4>APRS64,WIDE2*:%s" % message)

pprint.pprint(packet)
