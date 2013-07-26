#include"nodeMap.h"
#include"socketC.h"
using namespace std;


node* nodeMap::addNode(node* n)
{
    Key macK(n->mac());
    Key ipK(n->ip());
    
    ipMap[ipK]=n;
    macMap[macK]=n;

    return n;
}

node* nodeMap::nodeFromIp(string ip)
{
    Key k(ip);
    nodeIter it=ipMap.find(k);
    if(it==ipMap.end() )
    {
	string str=ipMap.begin()->first.str();
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


void nodeMap::delete_node(node* n)
{
    Key macK(n->mac());
    Key ipK(n->ip());
    ipMap.erase(ipK);
    macMap.erase(macK);
    delete n;
}

nodeMap* nodeMap::_nmap=0;
