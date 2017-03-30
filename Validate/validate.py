#!/bin/env python
import aprslib, pprint

# Put the output from the APRS message into "message" and hope it works

message = "/302108h4437.28N/07930.56Ws000/001/A=000919"

packet = aprslib.parse("FAKE-4>APRS64,WIDE2*:%s" % message)

pprint.pprint(packet)
