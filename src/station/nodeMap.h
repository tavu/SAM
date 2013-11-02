#ifndef NODE_MAP_H
#define NODE_MAP_H

#include<string>
#include<map>
#include"node.h"
#include<pthread.h>
#include <string.h>

/*Class NodeMap
 * This class contains a list with all the nodes connected to the base station.
 */
class NodeMap
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
        friend NodeMap* nMap();

        NodeMap()
        {
            pthread_mutex_init(&mutex, NULL);
        }

        ~NodeMap()
        {
            pthread_mutex_destroy(&mutex);
        }
        
        typedef std::map<Key,Node*>::iterator nodeIter;

        Node* addNode(Node* n);
        Node* nodeFromIp(std::string ip);
        Node* nodeFromMac(std::string mac);

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

        Node* nodeFromIt(nodeIter &it)
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
            _nmap=new NodeMap();
        }
        
        void delete_node(Node* n);	
	 
        static void clear()
        {
            delete _nmap;
            _nmap=0;
        }
        
    private:
        pthread_mutex_t mutex;
        std::map<NodeMap::Key,Node*> ipMap;
        std::map<NodeMap::Key,Node*> macMap;

        static NodeMap* _nmap;                
};

NodeMap* nMap();

#endif
