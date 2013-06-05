#include"nodeMap.h"
#include"socketC.h"
using namespace std;


node* nodeMap::addNode(node* n)
{
    Key macK(n->mac());
    Key ipK(n->ip());
    
    ipMap[macK]=n;
    macMap[ipK]=n;

    return n;
}

node* nodeMap::nodeFromIp(string ip)
{
    Key k(ip);
    nodeIter it=ipMap.find(k);
    if(it==ipMap.end() )
    {
        return 0;
    }
    return it->second;
}

node* nodeMap::nodeFromMac(string mac)
{
    Key k(mac);
    nodeIter it=macMap.find(k);
    
    if(it==macMap.end() )
    {
        return 0;
    }
    return it->second;
}

nodeMap* nMap()
{
    return nodeMap::_nmap;
}


nodeMap* nodeMap::_nmap=0;
