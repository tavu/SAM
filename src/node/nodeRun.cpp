#include"nodeReceiver.h"
#include"socketC.h"
#include "../common/optionsLoader.h"
#include <signal.h>

/*
 * Main function of the node
 */

nodeReceiver *Rec;
socketC *Soc;

void leave(int sig);

int main() {
	(void) signal(SIGINT, leave);
	(void) signal(SIGTERM, leave);

	optionsLoader::init();
	Soc = new socketC();
	Soc->init();
	Rec = new nodeReceiver();
	Rec->setSocket(Soc);
	Rec->start();
	Rec->join();
	return 0;
}

void leave(int sig) {
	Rec->cancel();

	delete Rec;
	delete Soc;
}
