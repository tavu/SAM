#ifndef TIMEOUTCHECK_H
#define TIMEOUTCHECK_H

#include<thread.h>
#include <socketC.h>
/*Class timeoutCheck
 * This class checks the nodes for their existence on a frequency defined
 * in the configuration file, and sends hello to every node in the nodes list.
 * Also, if a node hasn't responded to the hello messages, it deletes it from the list.
 */
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
