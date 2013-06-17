#include"nodeMap.h"
#include"socketC.h"
using namespace std;


node* nodeMap::addNode(node* n)
{
	cout<<"ADD N:"<<n->mac()<<" "<<n->ip();
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
	cout<<"N "<<ip<<" "<<ip.size()<<endl;
	string str=ipMap.begin()->first.str();
        
	for(int i=0;i<str.size();i++)
	{
		cout<<"N2 "<<(int)str.c_str()[i]<<endl;
	}

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
	cout<<"fount"<<endl;
    return it->second;
}

nodeMap* nMap()
{
    return nodeMap::_nmap;
}


nodeMap* nodeMap::_nmap=0;
