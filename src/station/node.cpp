#include"node.h"
#include <cmath>
#include<stdlib.h>

#include"defs.h"
#include"noise.h"
#include <stdio.h>
#include <string.h>
        
using namespace std;

int node::msgCount()
{
    return _msgCount;    
}

void node::setMsgCount(int i)
{
    _msgCount=i;
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
    char ip_add[20];

    string cmd = "arp -n -i ";
    cmd.append(WLAN);
    cmd.append("|grep -i ");
    cmd.append(mac);
    cmd.append("|awk '{print $1}'");

    FILE *fp = popen(cmd.c_str(),"r");
    if(fp==NULL)
    {
        return 0;
    }

    if(fgets(ip_add,20,fp)==NULL)
    {
        pclose(fp);
        return 0;
    }

    pclose(fp);

    string ip;
    ip.reserve(16);

    int size=strlen(ip_add);
    for(int i=0;i<size;i++)
    {
        if( isdigit(ip_add[i]) || ip_add[i]=='.' )
        {
            ip.append(ip_add+i,1);
        }
    }
    return new node(mac,ip);
}
