#ifndef MESSAGE_H
#define MESSAGE_H

/*message.h
 * Contains defintions for structures used by the mechanism.
 * 		**struct sendSigMess: Structure containing signal and message type information.
 * 		**struct mechMes: The actual structure sent as message by the mechanism.
 * Also, message flags are defined here:
 * 		**MECH --> Flag indicating the message is related to the mechanism.
 * 		**HELLO --> HELLO message
 * 		**SIGNAL_M --> Flag indicating power adaptation message
 * 		**SIG_ACK--> Flag indicating message acknowledgement
 */

#define MECH            'M'
#define HELLO         'h'
#define SIGNAL_M        'r'
#define SIG_ACK         'A'

struct sendSigMess {
	char mech;
	char type;
	int signal;
	int noise;
};

struct mechMes {
	std::string ip;
	struct sendSigMess m;
};

#endif
