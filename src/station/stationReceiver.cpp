#include"stationReceiver.h"
#include"message.h"
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

        log<<"[RECEIVED]"<<message.ip<<std::endl;

        if(message.m.type==HELLOW )
        {
            //TODO
            continue;
        }
        else if(message.m.type==HNDSH_A)//ack to handshake
        {
            //TODO
        }
    }
    return 0;
}

stationReceiver::stationReceiver()
{

}

