#!/bin/sh

# Usage: startNode node
startNode () {
#    himage $1 kill -9 -1 2> /dev/null
#    himage $1 tcpdrop -a 2> /dev/null
    for ifc in `himage $1 netstat -ai | fgrep '<Link' | cut -d' ' -f1 | tr -d '*'`; do
	if [ "$ifc" != "lo0" ]; then
	    echo ifconfig $ifc up
	    himage $1 ifconfig $ifc up
	fi
    done
    echo "Started node $1."
}

startNode $1@$eid
