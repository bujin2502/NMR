#!/bin/sh

# Usage: stopNode node
stopNode () {
#    himage $1 kill -9 -1 2> /dev/null
#    himage $1 tcpdrop -a 2> /dev/null
    for ifc in `himage $1 netstat -i | fgrep '<Link' | cut -d' ' -f1`; do
	if [ "$ifc" != "lo0" ]; then
	    echo ifconfig $ifc down
	    himage $1 ifconfig $ifc down
	fi
    done
    echo "Stopped node $1."
}

stopNode $1@$eid

