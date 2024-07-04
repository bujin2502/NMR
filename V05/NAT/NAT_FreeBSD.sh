#! /bin/sh

ipfw -q flush
cmd="ipfw add"
ks="keep-state"
skip="skipto 5000"
pif=eth0
good_tcpo="22,23,25,53,80,443,110"

$cmd allow all from any to any via eth1               # unutar LAN-a
$cmd allow all from any to any via lo0                # loopback
$cmd deny  all from any to 192.168.1.0/29 in via $pif # bez NAT-a
$cmd divert natd ip from any to any in via $pif	      # NAT
$cmd check-state

# ulaz port 25 - SMTP
$cmd $skip tcp from 10.0.0.10 to 192.168.1.5 25 setup $ks

# izlaz
$cmd $skip udp from any to any out via $pif $ks
$cmd $skip tcp from any to any $good_tcpo out via $pif setup $ks
$cmd $skip icmp from any to any out via $pif $ks
$cmd deny log all from any to any

$cmd 5000 divert natd ip from any to any out via $pif 
$cmd allow ip from any to any
