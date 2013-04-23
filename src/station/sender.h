#ifndef SENDER_H
#define SENDER_H

#include <iostream>
#include <fstream>
#include<socketC.h>
#include <thread.h>
#include<string>

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
//         static int getNoise();
        
        std::ifstream input;
        std::ofstream log;
        socketC *soc;
        
        char *dev;
};

#endif