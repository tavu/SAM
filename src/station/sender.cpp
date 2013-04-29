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
    struct bpf_program fp;         /* The compiled filter expression */    
    char filter_exp[] = "port 23";

    pcap_t *descr = pcap_open_live(dev,BUFSIZ,0,1000,errbuf);

    if(descr==0)
    {
        log<<"Couldn't parse filter "<<filter_exp <<" "<<pcap_geterr(descr);
        return(1);
    }
    /*
    if (pcap_compile(descr, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) 
    {
        log<<"Couldn't parse filter "<<filter_exp <<" "<<pcap_geterr(descr);
        return(2);
    }
    if (pcap_setfilter(descr, &fp) == -1) 
    {
        log<<"Couldn't install filter "<< filter_exp<<" "<<pcap_geterr(descr);
        return(2);
    }
    */
    while(1)
    {
	log<<"start";
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

        u_char *ptr;ptr = eptr->ether_dhost;

	char macS[18];
	char *c=macS;
        for(int i=0;i<ETHER_ADDR_LEN;i++)
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
	std::cout<<"MAC:"<<mac<<std::endl;

        nMap()->lock();
        node *n=nMap()->nodeFromMac(mac);
        nMap()->unlock();
        if(n==0)
        {
	    //TODO An den iparxei i MAC, den prepei na tin valoume?
	    //TODO Den mporoume na tsekaroume edw an i mac einai tou base station, gia na kanoume avoid ta
	    //paketa tou base station?
            cout<<"\tUNKOWN MAC "<<mac<<endl;
            continue;
        }
	cout<<"\tMAC FOUND!"<<endl;

        int signal=getSignal(mac);	

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
        else
        {
            nMap()->unlock();
        }
        
    }
    return 0;
}

 int sender::getSignal(std::string mac)
 {
     char signal[5];
     
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
     
    if(fgets(signal,5,output)==NULL)
    {
        pclose(output);
        return 0;
    }
    return atoi(signal);
     
 }
