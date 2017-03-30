#!/bin/env python
import aprslib, pprint

# Put the output from the APRS message into "message" and hope it works

message = "302052h4437.28N/07930.55Ws000/001/A=000863"

packet = aprslib.parse("FAKE-4>APRS64,WIDE2*:/%s" % message)

pprint.pprint(packet)
