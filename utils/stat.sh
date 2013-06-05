#!/bin/bash

LOG=stat.txt
time=1

date >>$LOG

while true; do
	./snr.sh >> $LOG
	sleep $time
done

echo >>$LOG
echo >>$LOG

