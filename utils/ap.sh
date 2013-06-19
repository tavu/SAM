wlan=ah
name=test
channel=11
ip="10.0.0.1"

phy=`iw list|grep Wiphy|awk '{print $2}'`


if [ "$1" == "del" ]; then
echo deleting interface
	iw dev $wlan del
	killall dhcpd
	exit
fi

echo creating interface "$wlan"
iw phy $phy interface add $wlan type managed
echo ""

echo setting channel to $channel
#iw dev $wlan set channel $channel
iwconfig $wlan channel $channel
echo ""

echo seting interface up
ifconfig $wlan $ip netmask 255.0.0.0 up
echo ""

#echo "setting to promisc mode"
#ifconfig $wlan promisc

echo Starting Hostapd
echo ""
hostapd -d /etc/hostapd/hostapd.conf > hostapd.log &

echo Starting DHCP Server
dhcpd ah




#Start dhclient to get an address
#dhclient $wlan
#sudo ip link set $wlan up
#sudo ip addr add 169.254.34.2/16 dev $wlan 
#sudo iwconfig $wlan key 1234567890
