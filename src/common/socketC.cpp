/*
 * Implementation of socketC class.
 */

#include"socketC.h"
#include<stdlib.h>
#include<cstring>
#include<iostream>
#include<arpa/inet.h>
#include"defs.h"
#include "optionsLoader.h"
#include"message.h"
#include<stdio.h>

using namespace std;

void socketC::init() {
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) {
		cout << "Could not create socket" << endl;
		exit(-1);
	}

}

int socketC::bindSocket() {
	memset(&bindSa, 0, sizeof bindSa);
	bindSa.sin_family = AF_INET;
	bindSa.sin_port = htons(optionsLoader::getInstance()->getPort());
	bindSa.sin_addr.s_addr = INADDR_ANY;
	len = sizeof(peer);

	return bind(sockfd, (struct sockaddr *) &bindSa, sizeof(bindSa));
}

struct mechMes socketC::received() {
	struct sendSigMess m;
	while (1) {
		std::cout << "Waiting for messages..." << std::endl;
		memset(&m, 0, sizeof(m));
		if (recvfrom(sockfd, &m, sizeof(m), 0, (struct sockaddr *) &peer, &len)
				> 0) {
			std::cout << "Message received !" << std::endl;
			if (m.mech == MECH) {
				break;
			}
		} else {
			perror("Receive Error!");
		}
	}

	struct mechMes message;
	message.m = m;
	message.ip = std::string(inet_ntoa(peer.sin_addr));

	cout << "Message received " << message.m.type << endl << " IP Address: "
			<< message.ip;

	return message;
}

int socketC::sendAck(string ip, int signal, int noise) {
	sendSigMess m;

	m.mech = MECH;
	m.signal = signal;
	m.type = SIG_ACK;
	m.noise = noise;

	return sendMessage(ip, &m, sizeof(m));
}

int socketC::sendSignalMessage(string ip, int signal, int noise) {
	cout << "Sending signal Message to adsress: " << ip << "..." << endl;
	struct sendSigMess m;
	m.mech = MECH;
	m.type = SIGNAL_M;
	m.signal = signal;
	m.noise = noise;

	return sendMessage(ip, &m, sizeof(m));
}

int socketC::sendHello(string ip) {
	struct sendSigMess m;
	m.mech = MECH;
	m.type = HELLO;
	m.signal = 0;
	m.noise = 0;

	return sendMessage(ip, &m, sizeof(m));
}

int socketC::sendMessage(string ip, void *m, int size) {
	struct sockaddr_in sa;
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(optionsLoader::getInstance()->getPort());
	sa.sin_addr.s_addr = inet_addr(ip.c_str());

	sendto(sockfd, m, size, 0, (struct sockaddr *) &sa, sizeof(sa));

	return 0;
}
