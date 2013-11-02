#ifndef NOISE_H
#define NOISE_H

#include"socketC.h"
#include"thread.h"

/*Class Noise
 * This class works in the background. Its goal is to
 * get the noise level read by the adapter via shell commands
 */
class Noise :public Thread
{
    public:
        static Noise* instance()
        {
            return _instance;
        }
        
        int getNoise();
        static void init();
         
        void setSocket(socketC *s)
        {
            soc=s;
        }
        
    private:
        static Noise *_instance;
        int getNoiseFromSystem();
        int _noise;
        socketC *soc;
        int run();
        Noise();
};

#endif
