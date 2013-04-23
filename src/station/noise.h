#ifndef NOISE_H
#define NOISE_H

#include"socketC.h"
#include"thread.h"
class Noise
{
    public:
        static Noise* instance()
        {
            return _instance;
        }
        
        int getNoise();
        void init();
         
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
};

#endif