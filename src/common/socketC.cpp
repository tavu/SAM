#include"socketC.h"
#include<stdlib.h>
#include<cstring>
#include<iostream>
using namespace std;

#include <arpa/inet.h>

#include"defs.h"
#include"message.h"

using namespace std;
void socketC::init()
{
    sockfd = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
}

int socketC::bindSocket()
{
    memset(&bindSa, 0, sizeof bindSa);
    bindSa.sin_family = PF_INET;
    bindSa.sin_port =htons(SPORT);
    bindSa.sin_addr.s_addr = INADDR_ANY;
//     socklen_t len = sizeof(peer);

    return bind(sockfd,(struct sockaddr *)&bindSa,sizeof(bindSa) );
}

struct mechMes socketC::received()
{
    struct sendSigMess m;
    while(1)
    {        
        std::cout<<"waiting message"<<std::endl;        
        memset(&m,0, sizeof(m) );
        if(recvfrom(sockfd,&m,sizeof(m),0,(struct sockaddr *)&peer,&len) > 0)
        {
            if(m.mech==MECH )
            {
                break ;
            }
        }
    }

    struct mechMes message;
    message.m=m;
    message.ip=std::string(inet_ntoa(peer.sin_addr) );

    cout<<"message received "<<message.m.type<<endl;

    return message;
}

int socketC::sendHsh(string ip)
{
//     char buff[3];
//     buff[0]=MECH;
//     buff[1]=HNDSH_R;
//     buff[2]='\0';
    sendSigMess m;
    m.mech=MECH;
    m.noise=0;
    m.noise=0;
    m.type=HNDSH_R;

    return sendMessage(ip,&m,sizeof(m) );
}



int socketC::sendAck(string ip,int signal, int noise )
{
    sendSigMess m;
    
    m.mech=MECH;
    m.signal=signal-noise;
    m.type=SIG_ACK;
    m.noise=noise;

    return sendMessage(ip,&m,sizeof(m) );
}

int socketC::sendHshAck(string ip)
{
//     char buff[3];
//     buff[0]=MECH;
//     buff[1]=HNDSH_A;
//     buff[2]=0;
    sendSigMess m;
    m.mech=MECH;
    m.signal=0;
    m.type=HNDSH_A;
    m.noise=0;

    return sendMessage(ip,&m,sizeof(m) );
}


int socketC::sendSignalMessage(string ip,int signal, int noise)
{
    cout<<"sending signal message"<<endl;
    struct sendSigMess m;
    m.mech=MECH;
    m.type=SIGNAL_M;
    m.signal=signal;
    m.noise=noise;

    return sendMessage(ip,&m,sizeof(m) );
}

int socketC::sendHellow(string ip)
{
//     char buff[2];
//     buff[0]=MECH;
//     buff[1]=HELLOW;

    struct sendSigMess m;
    m.mech=MECH;
    m.type=HELLOW;
    m.signal=0;
    m.noise=0;

    return sendMessage(ip,&m,sizeof(m));
}

int socketC::sendMessage(string ip,void *m, int size)
{
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = PF_INET;
    sa.sin_port = htons(SPORT);
    sa.sin_addr.s_addr = inet_addr(ip.c_str() );

    sendto(sockfd,m,size,0,(struct sockaddr *)&sa,sizeof(sa));

    return 0;
}
