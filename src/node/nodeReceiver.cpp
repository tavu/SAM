#include <stdio.h>
#include <string.h>
#include<iostream>
#include <stdlib.h>
#include <time.h>

#include"nodeReceiver.h"
#include"message.h"
#include"defs.h"
#include "../common/optionsLoader.h"

#include <signal.h>
#include <unistd.h>

/*Implementation of the nodeReceiver class*/

using namespace std;

nodeReceiver::nodeReceiver() :
		Thread(), log(LOG_F) {
	curr_tx = TX_MAX;
}

/*This is the basic method of this class.
 * The node is waiting for messages, and when one arrives, it cheks the flags.
 * ***If the flag is HELLO, the node send back to the base station a HELLO message to
 * inform the base that is alive.
 * ***If the flag is SIGNAL_M then the node has to change its transmission power based on the
 * information included in the received message.
 */
int nodeReceiver::run() {
	log << "Starting" << endl;

	if (soc->bindSocket() != 0) {
		log << "Could not bind socket" << endl;
		perror("Could not bind socket");
		return 0;
	}

	while (1) {
		struct mechMes message = soc->received();

		log << "[RECEIVED] " << message.ip << endl;

		if (message.m.type == HELLO) {
			soc->sendHello(message.ip);
			continue;
		} else if (message.m.type == SIGNAL_M) {
			log << "Signal: " << message.m.signal;
			log << '\t' << "Noise: " << message.m.noise;
			log << '\t' << "SNR: " << message.m.signal - message.m.noise
					<< endl;
			soc->sendAck(message.ip, message.m.signal, message.m.noise);
			setPower(message.m.signal, message.m.noise);
		}
	}
	return 0;
}

/*
 * This method sets the new transmission power based on the parameters given to it.
 */
int nodeReceiver::setPower(int signal, int noise) {
	int pathLoss = curr_tx * optionsLoader::getInstance()->getGain() - signal;

	int tx_new = (optionsLoader::getInstance()->getPrefferedSnr() + noise
			+ pathLoss) / optionsLoader::getInstance()->getGain();

	return setAbsPower(tx_new);
}

/*
 * Helper method for the power set
 */
int nodeReceiver::setAbsPower(int tx_new) {
	if (tx_new < TX_MIN)
		tx_new = TX_MIN;

	if (tx_new > TX_MAX)
		tx_new = TX_MAX;

	if (tx_new != curr_tx) {
		char foo[3];
		string cmd = "iwconfig ";
		cmd += optionsLoader::getInstance()->getInterface();
		cmd += " txpower ";
		sprintf(foo, "%d", tx_new);
		cmd.append(foo);

		time_t t = time(NULL);
		if (system(cmd.c_str()) != 0) {
			cout << "Error on system command" << endl;
			return -1;
		}

		txLog.open(TX_LOG, std::ios::out | std::ios::app);
		int txl = curr_tx;
		txLog << t << '\t' << txl;
		txl = tx_new;
		txLog << '\t' << txl << endl;
		curr_tx = tx_new;
		txLog.close();

		log << '\t' << cmd << endl;
	}

	return 0;
}
