/*
 * optionsLoader.cpp
 *
 *  Created on: Oct 30, 2013
 *      Author: nl0st
 */

/*Implementation of optionsLoader class.*/

#include "optionsLoader.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

optionsLoader::optionsLoader() {
	ifstream confFile;
	string line;
	string delimiter = "=";

	port = 0;
	gain = 0;
	preferredSNR = 0;
	SNRdeviaton = 0;
	helloMsgInterval = 0;

	confFile.open("../utils/sam.conf", ios::in);

	if (confFile.is_open()) {
		while (getline(confFile, line)) {
			if (line.find(delimiter) != string::npos) {
				string property = line.substr(0, line.find(delimiter));
				string value = line.substr(line.find(delimiter) + 1,
						line.size() - 1);

				if (property == "antenna_gain")
					gain = atoi(value.c_str());
				if (property == "port")
					port = atoi(value.c_str());
				if (property == "opt_snr")
					preferredSNR = atoi(value.c_str());
				if (property == "snr_deviation")
					SNRdeviaton = atoi(value.c_str());
				if (property == "interface")
					interface = value;
				if (property == "hello_msg_interval")
					helloMsgInterval = atoi(value.c_str());

			}
		}
		confFile.close();
	}
	doValidityCheck();

}

int optionsLoader::getGain() const {
	return gain;
}

int optionsLoader::getHelloMsgInterval() const {
	return helloMsgInterval;
}

string optionsLoader::getInterface() const {
	return interface;
}

int optionsLoader::getPort() const {
	return port;
}

int optionsLoader::getPrefferedSnr() const {
	return preferredSNR;
}

int optionsLoader::getSnRdeviaton() const {
	return SNRdeviaton;
}

optionsLoader::~optionsLoader() {
// TODO Auto-generated destructor stub
}

void optionsLoader::doValidityCheck() {

	if (port <= 0)
		port = 7000;
	if (gain <= 0)
		gain = 1;
	if (preferredSNR <= 0)
		preferredSNR = 30;
	if (SNRdeviaton <= 0)
		SNRdeviaton = 5;
	if (interface.empty())
		interface = "ah";
	if (helloMsgInterval <= 0)
		helloMsgInterval = 10;

	cout << endl;
	cout << "Setting antenna gain to " << gain << " dBi" << endl
			<< "Setting port number to " << port << endl
			<< "Setting preferred SNR to " << preferredSNR << " dB" << endl
			<< "Setting SNR deviation to " << SNRdeviaton << " dB" << endl
			<< "Active interface: " << interface << endl
			<< "Setting HELLO message interval to " << helloMsgInterval
			<< " seconds" << endl;

}

optionsLoader* optionsLoader::getInstance() {

	return instance;

}

void optionsLoader::init() {
	if (instance == 0) {
		instance = new optionsLoader();
	}
}

void optionsLoader::del() {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

optionsLoader* optionsLoader::instance = 0;

