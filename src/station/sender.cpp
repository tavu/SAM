#include"sender.h"
#include"nodeMap.h"
#include"noise.h"

#define LOG_F "sender.log"

#include <pcap.h> /* if this gives you an error try pcap/pcap.h */
#include <arpa/inet.h>//ntohs
#include <netinet/if_ether.h>
#include"defs.h"
#include<stdlib.h>
#include <stdio.h>

#define debug(STRING) cout<<#STRING<<endl;

using namespace std;

sender::sender()
    :log(LOG_F)
{
    dev="ah";
}

int sender::run()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    struct pcap_pkthdr hdr; /* pcap.h */
    struct ether_header *eptr; /* net/ethernet.h */
//     struct bpf_program fp;         /* The compiled filter expression */
    char filter_exp[] = "port 23";

    pcap_t *descr = pcap_open_live(dev,BUFSIZ,0,1000,errbuf);

    if(descr==0)
    {
        log<<"Couldn't parse filter "<<filter_exp <<" "<<pcap_geterr(descr);
        return(1);
    }

    if(pcap_setdirection(descr, PCAP_D_OUT)!=0)
    {
        log<<"Couldn't set direction "<<pcap_geterr(descr);
    }

    while(1)
    {
        log<<"Start"<<endl;
        const u_char *packet = pcap_next(descr,&hdr);
        if(packet == NULL)
        {
            log<<"Didn't grab packet\n";
            continue;
        }
        printf("Grabbed packet of length %d\n",hdr.len);

        if(hdr.len<sizeof(struct ether_header) )
        {
            printf("Too short packet");
            continue;
        }
        eptr = (struct ether_header *) packet;

        if (ntohs (eptr->ether_type) == ETHERTYPE_IP)
        {
            printf("Ethernet type hex:%x dec:%d is an IP packet\n",
                   ntohs(eptr->ether_type),
                   ntohs(eptr->ether_type));
        } else if (ntohs (eptr->ether_type) == ETHERTYPE_ARP)
        {
            printf("Ethernet type hex:%x dec:%d is an ARP packet\n",
                   ntohs(eptr->ether_type),
                   ntohs(eptr->ether_type));
        }
        else
        {
            printf("Ethernet type %x not IP", ntohs(eptr->ether_type));
            continue;
        }

        u_char *ptr;
        ptr = eptr->ether_dhost;

        char macS[18];
        char *c=macS;
        for(int i=0; i<ETHER_ADDR_LEN; i++)
        {
            sprintf(c,"%X",*ptr++);
            if(c[1]=='\0')
            {
                c[1]=c[0];
                c[0]='0';
                c[2]='\0';
            }

            if(i != ETHER_ADDR_LEN -1)
            {
                c[2]=':';
                c[3]='\0';
            }
            c+=3;
        }

        string mac(macS);
        std::cout<<"MAC: "<<mac<<std::endl;

        int signal=getSignal(mac);

        if( signal==0 )
        {
            continue;
        }
        
        nMap()->lock();
        node *n=nMap()->nodeFromMac(mac);
        
        if(n==0)
        {
            n=node::nodeFromMac(mac);
            if(n==0)
            {
                nMap()->unlock();
                continue;
            }
            nMap()->addNode(n);
        }
        nMap()->unlock();
        n->addSignal(signal);
        n->msgCountIncr();




        int noise=Noise::instance()->getNoise();
        nMap()->lock();
        bool b=n->needSend(noise);
        nMap()->unlock();

        cout<<"\tSignal: " <<signal<<"\tNoise: "<<noise<<" "<<b<<endl;

        if(b)
        {
            soc->sendSignalMessage(n->ip(),signal,noise);
        }

    }
    return 0;
}

int sender::getSignal(std::string mac)
{
    char signal[4];

    string cmd = "iw dev ";
    cmd.append(WLAN);
    cmd.append(" station get ");
    cmd.append(mac);
    cmd.append("|grep signal:|awk '{print $2}'");

    FILE *output = popen(cmd.c_str(),"r");
    if(output == NULL)
    {
        cout<<"geting signal error null file"<<endl;
        return 0;
    }

    if(fgets(signal,4,output)==NULL)
    {
        cout<<"geting signal error null output"<<endl;
        pclose(output);
        return 0;
    }
    pclose(output);
    return atoi(signal);

}
