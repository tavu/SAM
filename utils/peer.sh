wlan=ah
name=test
channel=11
ip="10.0.0.2"

phy=`iw list |grep Wiphy |awk '{print $2}'`

if [ "$1" == "del" ]; then
echo deleting interface
        iw dev $wlan del
	killall dhclient
        exit
fi

#iw dev wlan1 del

echo creating interface "$wlan"
iw phy $phy interface add $wlan type managed
echo ""


echo seting interface up
ifconfig $wlan up
ifconfig $wlan netmask 255.0.0.0
route add default gw 10.0.0.1
echo ""

echo setting channel to $channel
#iw dev $wlan set channel $channel
iwconfig $wlan channel $channel
echo ""

echo join the club
iwconfig $wlan essid $name


echo Getting ip using dhcp
dhclient $wlan &




#Start dhclient to get an address
#dhclient $wlan
#sudo ip link set $wlan up
#sudo ip addr add 10.0.0.0/16 dev $wlan 
#sudo iwconfig $wlan key 1234567890 
