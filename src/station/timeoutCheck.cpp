#include"timeoutCheck.h"
#include"nodeMap.h"
#include <list>
#include<defs.h>
#include<string.h>
#include"node.h"
using namespace std;

timeoutCheck::timeoutCheck()
{

}

int timeoutCheck::run()
{
    while(1)
    {
        sleep(HELLO_TIME);
        
        std::list<std::string> helloList;
        std::list<node*> rmList;
        
        nMap()->lock();    
        for(nodeMap::nodeIter i=nMap()->ipBegin();i!=nMap()->ipEnd();i++)
        {
            node *n=nMap()->nodeFromIt(i);
            int msgCount=n->msgCount();
            if(msgCount==-1)
            {
                rmList.push_back(n);
            }
            else if(msgCount==0)
            {
                n->setMsgCount(-1);
                helloList.push_back(n->ip());
            }
            else
            {
                n->setMsgCount(0);
            }
        }
        
        for (std::list<node*>::iterator it=rmList.begin(); it != rmList.end(); ++it)
        {
            nMap()->delete_node(*it);
        }
        
        nMap()->unlock();
        
         for (std::list<string>::iterator it=helloList.begin(); it != helloList.end(); ++it)
         {
             soc->sendHellow(*it);
         }        
    }
    return 0;
}
