#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <fstream>
#include<socketC.h>
#include <thread.h>
#include<string>

/*Class Sender
 * This class grabs the received packets using the  libpcap library
 * Then it checks if the packet was received from an already known
 * node or a new one. Then it checks for power adjusting.
 */
class sender :public Thread
{
    public:
        sender();
        ~sender()
        {
            soc->closeFd();
            input.close();
        }
        int run();

        void setSocket(socketC *s)
        {
            soc=s;
        }

    private:
        static int getSignal(std::string mac);
        std::ifstream input;
        std::ofstream log;
        socketC *soc;
        
        const char *dev;
};

#endif
