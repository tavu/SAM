#include"stationReceiver.h"
#include"sender.h"
#include"nodeMap.h"
#include "noise.h"
#include"socketC.h"
// #include"timeout.h"
#include <signal.h>
#include <cstdlib>
#include <unistd.h>

sender *Send;
stationReceiver *Rec;
socketC *Soc;
// timeoutChecker *Chk;

void leave(int sig);

int main()
{
    (void) signal(SIGINT,leave);
    (void) signal(SIGTERM,leave);

    nodeMap::init();
    Noise::init();
    Soc =new socketC();
    Send =new sender();
     Rec =new stationReceiver();
//     Chk = new timeoutChecker(Rec);

    Soc->init();

    Send->setSocket(Soc);
     Rec->setSocket(Soc);

     Rec->start();
//     Chk->start();
    Send->start();
    Send->join();
//     Rec->join(); 
}

void leave(int sig)
{
    Rec->cancel();
    Send->cancel();

    delete Rec;
    delete Send;
    nodeMap::clear();
    delete Soc;
//     delete Chk;
    exit (0);
}
