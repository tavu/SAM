#include"nodeReceiver.h"
#include"socketC.h"
#include <signal.h>

nodeReceiver *Rec;
socketC *Soc;

void leave(int sig);

int main()
{
    (void) signal(SIGINT,leave);
    (void) signal(SIGTERM,leave);

    Soc =new socketC();

    Rec->setSocket(Soc);
    Rec->start();

    return 0;
}

void leave(int sig)
{
    Rec->cancel();

    delete Rec;
    delete Soc;
}
