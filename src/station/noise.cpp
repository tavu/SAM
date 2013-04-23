#include"noise.h"
#include"nodeMap.h"
#include <unistd.h>
#include<list>
#define TIME 5
using namespace std;

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

int Noise::getNoiseFromSystem()
{

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

