#include"sender.h"
#include"nodeMap.h"
#include"noise.h"

#define LOG_F "sender.log"

#include <pcap.h> /* if this gives you an error try pcap/pcap.h */
#include <arpa/inet.h>//ntohs
#include <netinet/if_ether.h>


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
    
    pcap_t *descr = pcap_open_live(dev,BUFSIZ,0,1000,errbuf);
    while(1)
    {
        const u_char *packet = pcap_next(descr,&hdr);
        if(packet == NULL)
        {
           log<<"Didn't grab packet\n";
        }        
        eptr = (struct ether_header *) packet;        
        if (ntohs (eptr->ether_type) != ETHERTYPE_IP || ntohs (eptr->ether_type) != ETHERTYPE_ARP  )
        {
            log<<"type %x not IP", ntohs(eptr->ether_type);
            continue;
        }        
        
        u_char *ptr;ptr = eptr->ether_dhost;        
        int i=0;
        string mac;
        do
        {
            char macS[3];
            sprintf(macS,"%x",*ptr++);
            mac.append(macS,3);
            if(i != ETHER_ADDR_LEN)
            {
                mac.append(":");
            }
            
        }while(--i>0);
        
        nMap()->lock();
        node *n=nMap()->nodeFromMac(mac);
        nMap()->unlock();
        if(n==0)
        {
            log<<"\tUNKOWN MAC "<<mac<<endl;
            continue;
        }
        
        int signal=getSignal(mac);
        
        n->addSignal(signal);
        n->msgCountIncr();
        int noise=Noise::instance()->getNoise();
        
        nMap()->lock();
        if(n->needSend(noise) )
        {
            nMap()->unlock();
            
            soc->sendSignalMessage(n->ip(),signal,noise);
        }
        else
        {
            nMap()->unlock();
        }
        
    }
    return 0;
}

 int sender::getSignal(std::string mac)
 {
     string signal = "";
     
     string cmd = "iw dev ";
     cmd.append(WLAN);
     cmd.append(" station get ");
     cmd.append(mac);
     cmd.append("|grep signal:|awk '{print $2}'");
     
     FILE *output = popen(cmd.c_str(),"r");
     if(output == NULL)
     {
       return 0;
     }
     
     if(fgets(signal,4,output)==NULL)
    {
        pclose(output);
        return 0;
    }
    return atoi(signal.c_str());
     
 }