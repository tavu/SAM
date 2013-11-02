/*
 * Main function for the Base station
 */

#include"stationReceiver.h"
#include"sender.h"
#include"nodeMap.h"
#include "noise.h"
#include"socketC.h"
#include"timeoutCheck.h"
#include"../common/optionsLoader.h"
#include <signal.h>
#include <cstdlib>
#include <unistd.h>

sender *Send;
stationReceiver *Rec;
socketC *Soc;
timeoutCheck *Chk;

void leave(int sig);

int main() {
	(void) signal(SIGINT, leave);
	(void) signal(SIGTERM, leave);

	optionsLoader::init();
	NodeMap::init();
	Noise::init();

	Soc = new socketC();
	Send = new sender();
	Rec = new stationReceiver();
	Chk = new timeoutCheck();
	Chk->setSocket(Soc);

	Soc->init();

	Send->setSocket(Soc);
	Rec->setSocket(Soc);

	Rec->start();
	Chk->start();
	Send->start();
	Send->join();
}

void leave(int sig) {
	Rec->cancel();
	Send->cancel();

	delete Rec;
	delete Send;
	NodeMap::clear();
	delete Soc;
	delete Chk;
	exit(0);
}
