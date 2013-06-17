#include"node.h"
#include <cmath>
#include<stdlib.h>

#include"defs.h"
#include"noise.h"
#include <stdio.h>
        
using namespace std;

int node::msgCount()
{
    int i=_msgCount;
    _msgCount=0;
    return i;
}

void node::msgCountIncr()
{
    _msgCount++;
}

void node::addSignal(int s)
{
    _signal=s;
}

/*
void node::ackReceived(int ackSnr)
{
    this.ackSnr=ackSnr;
}
*/
bool node::needSend(int noise)
{      
    int snr=_signal-noise;
    
    if(_ackSnr>0 && (abs(_ackSnr - snr) < SNR_VARIATION) )
    {
        return false;
    }
    
    if(snr>0 &&  abs(PERF_SNR - snr) > SNR_VARIATION)
    {
        return true;
    }
    return false;

}

node* node::nodeFromIp(string ip)
{
    char mac_add[18];

    string cmd = "arp -n -i ";
    cmd.append(WLAN);
    cmd.append("|grep -i ");
    cmd.append(ip);
    cmd.append("|awk '{print $3}'");

    //   cout<<cmd.c_str()<<endl;

    FILE *fp = popen(cmd.c_str(),"r");
    if(fp==NULL)
    {
        return 0;
    }

//     mac_add=(char*)malloc(16*sizeof(char) );
    if(fgets(mac_add,18,fp)==NULL)
    {
        pclose(fp);
        return 0;
    }

    pclose(fp);

    int i=0;
    while (mac_add[i])
    {
        mac_add[i]=(char) ( toupper(mac_add[i]) );
        i++;
    }

    string mac=string(mac_add);


    return new node(mac,ip);

}

node* node::nodeFromMac(string mac)
{
    char ip_add[18];

    string cmd = "arp -n -i ";
    cmd.append(WLAN);
    cmd.append("|grep -i ");
    cmd.append(mac);
    cmd.append("|awk '{print $1}'");

    //   cout<<cmd.c_str()<<endl;

    FILE *fp = popen(cmd.c_str(),"r");
    if(fp==NULL)
    {
        return 0;
    }

//     mac_add=(char*)malloc(16*sizeof(char) );
    if(fgets(ip_add,18,fp)==NULL)
    {
        pclose(fp);
        return 0;
    }

    pclose(fp);

    char ips[18];
    sprintf(ips,"%s",ip_add);
    string ip=string(ips);

    return new node(mac,ip);

}
