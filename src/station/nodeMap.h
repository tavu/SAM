#ifndef NODE_MAP_H
#define NODE_MAP_H

#include<string>
#include<map>
#include"node.h"
#include<pthread.h>
#include <string.h>


class nodeMap
{
    private:
        class Key 
        {
            public:    
                Key(std::string s)
                {
                    this->s=s;
                }                
                
                bool operator<(const Key& other) const
                {
                    int diff = strcmp(s.c_str(), other.s.c_str());
                    return diff<0;
                }
		
		bool operator==(const Key& other) const
		{
			return strcmp(s.c_str(),other.s.c_str() )==0;
		}
                
                std::string str() const
                {
                    return s;
                }
            private:
                std::string s;
        };
        
    public:
        friend nodeMap* nMap();

        nodeMap()
        {
            pthread_mutex_init(&mutex, NULL);
        }

        ~nodeMap()
        {
            pthread_mutex_destroy(&mutex);
        }
        
        typedef std::map<Key,node*>::iterator nodeIter;

        node* addNode(node* n);
        node* nodeFromIp(std::string ip);
        node* nodeFromMac(std::string mac);

        int size()
        {
            return ipMap.size();
        }        

        nodeIter ipBegin()
        {
            return ipMap.begin();
        }

        nodeIter ipEnd()
        {
            return ipMap.end();
        }

        node* nodeFromIt(nodeIter &it)
        {
            return it->second;
        }

        void lock()
        {
            pthread_mutex_lock(&mutex);
        }

        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }

        static void init()
        {
            _nmap=new nodeMap();
        }
        
        void delete_node(node* n)
	{
	  ipMap.erase(n->ip());
	  macMap.erase(n->mac());
	}
	 
        static void clear()
        {
            delete _nmap;
            _nmap=0;
        }
        
    private:
        pthread_mutex_t mutex;
        std::map<nodeMap::Key,node*> ipMap;
        std::map<nodeMap::Key,node*> macMap;

        static nodeMap* _nmap;                
};

nodeMap* nMap();

#endif
