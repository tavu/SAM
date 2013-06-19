#!/bin/bash

LOG=stat.txt
time=1
totalTime=$1*60

date >>$LOG
echo ""
echo "Distance: $2">>$LOG

while [$totalTime -gt 0];do
	./snr.sh >> $LOG
	let currentTime--
	sleep $time
done

echo >>$LOG
echo >>$LOG

