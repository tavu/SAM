#!/bin/bash

log=bitrates.log
wlan=ah
location=$1
currentTime=$(date +"%T")
txPower=`iwconfig $wlan | grep Tx-Power | awk '{print $2}'`
bitrate=`iwconfig $wlan | grep "Bit Rate" | awk '{print $1}'`

echo $currentTime >> $log
echo $location >> $log
echo -e $txPower"\t"$bitrate >> $log 

