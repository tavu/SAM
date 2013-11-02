#ifndef RECEIVER_H
#define RECEIVER_H

#include <pthread.h>
#include "socketC.h"
#include <fstream>
#include "thread.h"


/*Class nodeReceiver
 * This is the core class of every node  connected to the
 * base station.
 */
#define LOG_F "receiver.log"
#define TX_LOG "tx.log"


class nodeReceiver : public Thread {
public:
	nodeReceiver();

	virtual ~nodeReceiver() {
		log.close();
	}
	;

	int setPower(int signal, int noise);

	void setSocket(socketC *s) {
		soc = s;
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
