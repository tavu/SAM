#include"stationReceiver.h"
#include"message.h"
#include"nodeMap.h"

#define LOG_F "receiver.log"

/*
 * implementation of stationReceiver class
 */
stationReceiver::stationReceiver() :
		log(LOG_F) {
}

int stationReceiver::run() {
	log << "Starting" << std::endl;

	if (soc->bindSocket() != 0) {
		log << "Could not bind socket" << std::endl;
		return 0;
	}

	while (1) {
		struct mechMes message = soc->received();

		log << "[RECEIVED] " << message.ip << std::endl;

		if (message.m.type == HELLO) {
			continue;
		} else if (message.m.type == SIG_ACK) {
			nMap()->lock();
			Node *n = nMap()->nodeFromIp(message.ip);
			if (n == 0) {
				nMap()->unlock();
				log << "Received ACK from null node";
			} else {
				int snr = message.m.signal - message.m.noise;
				log << "ACK SNR:" << snr << std::endl;
				n->setAckSnr(message.m.signal - message.m.noise);
				nMap()->unlock();
			}
		}
	}
	return 0;
}

