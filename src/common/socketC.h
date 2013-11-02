#ifndef SOCKETC_H
#define SOCKETC_H

#include<string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include"message.h"

/*Class socketC.
 * This class implements the socket and its functions.
 */
class socketC {
public:

	socketC() {
		init();
	}
	~socketC() {
		closeFd();
	}

	void init();
	int bindSocket();
	struct mechMes received();

	int sendSignalMessage(std::string ip, int signal, int noise);
	int sendHello(std::string ip);
	int sendAck(std::string ip, int signal, int noise);

	void closeFd() {
		close(sockfd);
	}

protected:
	int sendMessage(std::string ip, void *m, int size);

private:
	struct sockaddr_in peer, bindSa;
	socklen_t len;
	int sockfd;
};

#endif
