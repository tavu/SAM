#include"noise.h"
#include"nodeMap.h"
#include <unistd.h>
#include<list>
#define TIME 5
#include"defs.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

Noise::Noise()
{
    _noise=getNoiseFromSystem();
}

int Noise::getNoise()
{
    return _noise;
}

void Noise::init()
{

    if(_instance==0)
    {
        _instance=new Noise();
    }
}

//TODO If Noise is not supported by the driver, exit the mechanism
int Noise::getNoiseFromSystem()
{
     char noise[4];
     
     string cmd = "iw dev ";
     cmd.append(WLAN);
     cmd.append(" survey dump |grep Noise: |awk '{print $2}'");
     
     FILE *output =popen(cmd.c_str(),"r");
     if(output == NULL)
     {
       return 0;
     }
     
    if(fgets(noise,4,output)==NULL)
    {
        pclose(output);
        return 0;
    }
    
    return atoi(noise);
}

int Noise::run()
{
    std::list<string> nodeList;
    while(1)
    {
        nMap()->lock();
        _noise=getNoiseFromSystem();
        
        for(nodeMap::nodeIter i=nMap()->ipBegin();i!=nMap()->ipEnd();i++)
        {
            node *n=nMap()->nodeFromIt(i);
            if(n->needSend(_noise) )
            {
                nodeList.push_back(n->ip() );
            }
        }
        nMap()->unlock();
/*     
        for (list<string>::iterator it=nodeList.begin(); it != nodeList.end(); ++it)
        {
            soc->sendSignalMessage(*it,_noise);
        }
*/
        sleep(TIME);
    }
    return 0;
}

Noise* Noise::_instance=0;

