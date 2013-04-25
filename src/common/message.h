#ifndef MESSAGE_H
#define MESSAGE_H

#define MECH            'M'
#define HELLOW          'h'
#define SIGNAL_M        'r'
#define SIG_ACK             'A'
#define HNDSH_R         'H'
#define HNDSH_A         'a'

#define MESSAGE_BUFF 3


struct sendSigMess
{
    char mech;
    char type;
    int signal;
    int noise;
};
/*
struct sendMess
{
    char mech;
    char type;
    int value;
};
*/

struct mechMes
{    
    std::string ip;    
    struct sendSigMess m;
};


#endif