#!/bin/bash

log=log
wlan=ah
location=$1
currentTime=$(date)
txPower=`iwconfig $wlan | grep Tx-Power | awk '{print $4" "$5}'`
bitrate=`iwconfig $wlan | grep "Bit Rate" | awk '{print $1" "$2" "$3}'`

echo $currentTime >> $log
echo Distance: $location >> $log
echo $txPower >> $log
echo $bitrate >> $log 

