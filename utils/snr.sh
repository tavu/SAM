#!/bin/bash

dev=ah
mac=`iw dev $dev station dump |grep Station |awk '{print $2}' `

#echo $mac
signal=`iw dev $dev station get $mac |grep signal: |awk '{print $2}'`


noise=`iw dev $dev survey dump |grep noise: |awk '{print $2}'`

let snr=$signal-$noise
echo $snr
