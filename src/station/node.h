#ifndef NODE_H
#define NODE_H

#include"iostream"
#include<string>


/*
 * Class node
 * This class represents a node that is connected to the base station
 */
class Node
{
    public:
        Node(std::string mac,std::string ip) :_mac(mac),_ip(ip)
        {
            _msgCount=1;
            _ackSnr=-1;
            std::cout<<"IP "<<ip<<" "<<ip.size()<<std::endl;
        }
        
        Node()
        {}

        void addSignal(int);
        
        int signal()
        {
            return _signal;
        }

        std::string mac()
        {
            return _mac;
        }

        std::string ip()
        {
            return _ip;
        }
        
        void setAckSnr(int snr)
        {
            _ackSnr=snr;
        }

        bool needSend(int noise);
        
        int msgCount();  
        void setMsgCount(int i);
        void msgCountIncr(); 

        static Node* nodeFromMac(std::string mac);
        static Node* nodeFromIp(std::string ip);

    private:
        std::string _mac;
        std::string _ip;
        char _signal;
        int _ackSnr;
        int _msgCount;
};




#endif
