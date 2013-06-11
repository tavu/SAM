#include"stationReceiver.h"
#include"message.h"
#include"nodeMap.h"

#define LOG_F "receiver.log"


stationReceiver::stationReceiver():log(LOG_F)
{
}


int stationReceiver::run()
{
    log<<"Starting"<<std::endl;

    if(soc->bindSocket()!=0)
    {
        log<<"could not bind socket"<<std::endl;
        return 0;
    }

    while(1)
    {
        struct mechMes message=soc->received();

        log<<"[RECEIVED] "<<message.ip<<std::endl;

        if(message.m.type==HELLOW )
        {
            //TODO Tha ginei to hello message?
            continue;
        }
        else if(message.m.type==SIG_ACK)
        {
            nMap()->lock();
            node *n=nMap()->nodeFromIp(message.ip);
            if(n==0)
            {
                nMap()->unlock();
                log<<"Received ack from null node";
            }
            n->setAckSnr(message.m.signal - message.m.noise);
            nMap()->unlock();
            
            
        }
    }
    return 0;
}

