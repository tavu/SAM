#ifndef RECEIVER_H
#define RECEIVER_H

#include <pthread.h>
#include "socketC.h"
#include <fstream>
#include "thread.h"

#define LOG_F "receiver.log"
#define TX_LOG "tx.log"
#define DB(STRING) cout<<#STRING<<endl;

class nodeReceiver :public Thread
{
    public:
        nodeReceiver();

        virtual ~nodeReceiver()
        {
            log.close();
        };

        int setPower(int signal , int noise);

        void setSocket(socketC *s)
        {
            soc=s;
        }

        int run();

    protected:

        int setAbsPower(int tx_new);
        std::ofstream log;
        socketC *soc;
        
    private:

        std::ofstream txLog;
        int curr_tx;
};

#endif