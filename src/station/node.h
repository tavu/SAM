#ifndef NODE_H
#define NODE_H



#include"iostream"
#include<string>

class node
{
    public:
        node(std::string mac,std::string ip) :_mac(mac),_ip(ip)
        {
            _msgCount=1;
            ackSnr=-1;
        }
        
        node()
        {}

        void addSignal(int);

        std::string mac()
        {
            return _mac;
        }

        std::string ip()
        {
            return _ip;
        }

        bool needSend(int noise);
        
        int msgCount();        
        void msgCountIncr(); 

        static node* nodeFromMac(std::string mac);
        static node* nodeFromIp(std::string ip);


    private:
        std::string _mac;
        std::string _ip;
	short int hello_messages;
        char _signal;
        int ackSnr;
        int _msgCount;
};




#endif
