#!/bin/bash

LOG=stat.txt
time=1
totalTime=$1*60


date >>$LOG
echo ""
echo "Distance: $2">>$LOG

while [$totalTime -gt 0];do
	iwconfig ah | grep Tx-Power | awk '{print $1}'>> $LOG
	let totalTime--
	sleep $time
done

echo >>$LOG
echo >>$LOG