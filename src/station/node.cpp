#include"node.h"
#include <cmath>
#include<stdlib.h>
#include "../common/optionsLoader.h"
#include"defs.h"
#include"noise.h"
#include <stdio.h>
#include <string.h>
        
using namespace std;


int Node::msgCount()
{
    return _msgCount;    
}

void Node::setMsgCount(int i)
{
    _msgCount=i;
}


void Node::msgCountIncr()
{
    _msgCount++;
}

void Node::addSignal(int s)
{
    _signal=s;
}

/*
 * Method that checks if a certain node has to change its transmission power
 */
bool Node::needSend(int noise)
{      
    int snr=_signal-noise;
    
    if(_ackSnr>0 && (abs(_ackSnr - snr) < optionsLoader::getInstance()->getSnRdeviaton()) )
    {
        return false;
    }
    
    if(snr>0 &&  abs(optionsLoader::getInstance()->getPrefferedSnr() - snr) > optionsLoader::getInstance()->getSnRdeviaton())
    {
        return true;
    }
    return false;

}

/*Helper method that a new Node*/

Node* Node::nodeFromIp(string ip)
{
    char mac_add[18];

    string cmd = "arp -n -i ";
    cmd.append(optionsLoader::getInstance()->getInterface());
    cmd.append("|grep -i ");
    cmd.append(ip);
    cmd.append("|awk '{print $3}'");

    FILE *fp = popen(cmd.c_str(),"r");
    if(fp==NULL)
    {
        return 0;
    }

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


    return new Node(mac,ip);

}

Node* Node::nodeFromMac(string mac)
{
    char ip_add[20];

    string cmd = "arp -n -i ";
    cmd.append(optionsLoader::getInstance()->getInterface());
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
    return new Node(mac,ip);
}
