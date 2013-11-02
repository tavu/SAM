/*
 * Implementation of class noise
 */
#include"noise.h"
#include"nodeMap.h"
#include <unistd.h>
#include<list>
#include"defs.h"
#include"../common/optionsLoader.h"
#include <stdlib.h>
#include <stdio.h>

#define TIME 5

using namespace std;

/*
 * Class Constructor
 * If the wireless adapter driver cannot calculate the noise level,
 * the application exits, since noise is a necessary property for
 * its functionality.
 */

Noise::Noise() {
	_noise = getNoiseFromSystem();
	if (_noise == 0) {
		perror("The driver does not support noise. Exiting...");
       exit(-1);
	}
}

int Noise::getNoise() {
	return _noise;
}

void Noise::init() {

	if (_instance == 0) {
		_instance = new Noise();
	}
}

int Noise::getNoiseFromSystem() {
	char noise[4];

	string cmd = "iw dev ";
	cmd.append(optionsLoader::getInstance()->getInterface());
	cmd.append(" survey dump |grep noise: |awk '{print $2}'");

	FILE *output = popen(cmd.c_str(), "r");
	if (output == NULL) {
		return 0;
	}

	if (fgets(noise, 4, output) == NULL) {
		pclose(output);
		return 0;
	}
	pclose(output);
	return atoi(noise);
}


/*Main function of class Noise
 * The method runs continuously in the background, reading the noise levels from the system.
 * Then it checks all the registered nodes, in case someone needs to adjust its transmission power.
 * If so, the node is copied to another map.
 * After the check, the method sends the corresponding mechanism messages to the nodes
 * that are contained in the above map.
 * Finally, it goes back to sleep for 5 seconds.
 */
int Noise::run() {
	while (1) {
		std::list<Node*> nodeList;
		_noise = getNoiseFromSystem();
		if (_noise == 0) {
			perror("The driver does not support noise. Exiting...");
			exit(-1);
		}

		nMap()->lock();
		for (NodeMap::nodeIter i = nMap()->ipBegin(); i != nMap()->ipEnd();
				i++) {
			Node *n = nMap()->nodeFromIt(i);
			if (n->needSend(_noise)) {
				nodeList.push_back(n);
			}

		}
		nMap()->unlock();

		for (list<Node*>::iterator it = nodeList.begin(); it != nodeList.end();
				++it) {
			soc->sendSignalMessage((*it)->ip(), (*it)->signal(), _noise);
		}

		sleep(TIME);
	}
	return 0;
}

Noise* Noise::_instance = 0;

