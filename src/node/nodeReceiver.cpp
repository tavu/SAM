#include <stdio.h>
#include <string.h>
#include<iostream>
#include <stdlib.h>
#include <time.h>

#include"nodeReceiver.h"
#include"message.h"
#include"defs.h"

#include <signal.h>
#include <unistd.h>

//this is a comment
#define BUFF_S 3

using namespace std;

nodeReceiver::nodeReceiver() :Thread(),log(LOG_F)
{
    curr_tx=TX_MAX;
}

int nodeReceiver::run()
{
    log<<"Starting"<<endl;

    if(soc->bindSocket()!=0)
    {
        log<<"Could not bind socket"<<endl;
        perror("Could not bind socket");
        return 0;
    }

    while(1)
    {
        struct mechMes message=soc->received();

        log<<"[RECEIVED] "<<message.ip<<endl;

        if(message.m.type==HELLOW )
        {
            //TODO
            continue;
        }
        else if(message.m.type==SIGNAL_M)
        {
            log<<"Signal: "<<message.m.signal;
            log<<'\t'<<"Noise: "<<message.m.noise;
            log<<'\t'<<"SNR: "<<message.m.signal-message.m.noise<<endl;
            setPower(message.m.signal,message.m.noise );
            soc->sendAck(message.ip,message.m.signal,message.m.noise);
        }
    }
    return 0;
}

int nodeReceiver::setPower(int signal,int noise)
{
    int pathLoss=curr_tx*GAIN - signal;

    
    int tx_new=(PERF_SNR+noise+pathLoss)/GAIN;

    return setAbsPower(tx_new);
}


int nodeReceiver::setAbsPower(int tx_new)
{
    if(tx_new <TX_MIN)
        tx_new=TX_MIN;
    
    if(tx_new >TX_MAX)
        tx_new=TX_MAX;
    
    if(tx_new != curr_tx)
    {
        char foo[3];
        string cmd = "iwconfig ";
        cmd+=WLAN;
        cmd+=" txpower ";
        sprintf(foo,"%d",tx_new);
        cmd.append(foo);
        
        time_t t=time(NULL);
        if(system(cmd.c_str()) !=0)
        {
            cout<<"Error on system command"<<endl;
            return -1;
        }
        
        txLog.open(TX_LOG,std::ios::out | std::ios::app);
        int txl=curr_tx;
        txLog<<t<<'\t'<<txl;
        txl=tx_new;
        txLog<<'\t'<<txl<<endl;
        curr_tx=tx_new;
        txLog.close();
        
        log<<'\t'<<cmd<<endl;        
    }

    return 0;
}