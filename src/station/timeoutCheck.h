#ifndef TIMEOUTCHECK_H
#define TIMEOUTCHECK_H

#include<thread.h>
#include <socketC.h>

class timeoutCheck :public Thread
{
    public:
        timeoutCheck();        
        
        void setSocket(socketC *s)
        {
            soc=s;
        }
        
    protected:
        int run();
        socketC *soc;
};
#endif