#include"nodeMap.h"
#include"socketC.h"
using namespace std;


Node* NodeMap::addNode(Node* n)
{
    Key macK(n->mac());
    Key ipK(n->ip());
    
    ipMap[ipK]=n;
    macMap[macK]=n;

    return n;
}

Node* NodeMap::nodeFromIp(string ip)
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

Node* NodeMap::nodeFromMac(string mac)
{
    Key k(mac);
    nodeIter it=macMap.find(k);
    
    if(it==macMap.end() )
    {
        return 0;
    }
    return it->second;
}

NodeMap* nMap()
{
    return NodeMap::_nmap;
}


void NodeMap::delete_node(Node* n)
{
    Key macK(n->mac());
    Key ipK(n->ip());
    ipMap.erase(ipK);
    macMap.erase(macK);
    delete n;
}

NodeMap* NodeMap::_nmap=0;
