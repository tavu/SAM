/*
 * optionsLoader.h
 *
 *  Created on: Oct 30, 2013
 *      Author: nl0st
 */

#ifndef OPTIONSLOADER_H_
#define OPTIONSLOADER_H_

#include <stdlib.h>
#include <string>

using namespace std;


/* optionsLoader class definition.
 * This singleton class reads the configuration file sam.conf
 * located in the /utils directory and loads the property values that exist there.
 * If a property does not exist in the configuration file, the class initializes the corresponding
 * class member with a default value.
 */

class optionsLoader {

private:
	 int port;
	 int gain;
	 int preferredSNR;
	 int SNRdeviaton;
	 string interface;
	 int helloMsgInterval;
	static optionsLoader *instance;


public:
	optionsLoader();
	virtual ~optionsLoader();
	int getGain() const;
	int getHelloMsgInterval() const;
	string getInterface() const;
	int getPort() const;
	int getPrefferedSnr() const;
	int getSnRdeviaton() const;
	void doValidityCheck();
	static optionsLoader* getInstance();
	static void init();
	static void del();
};



#endif /* OPTIONSLOADER_H_ */
