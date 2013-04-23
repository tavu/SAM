#ifndef STATION_RECEVER_H 
#define STATION_RECEVER_H

#include <fstream>
#include"thread.h"
#include<socketC.h>
class stationReceiver :public Thread
{
    public:
       stationReceiver();
       ~stationReceiver()
       {
           log.close();
       }
         
       void setSocket(socketC *s)
        {
            soc=s;
        }
    protected:
        int run();
        std::ofstream log;
        socketC *soc;
};

#endif
