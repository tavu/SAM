#ifndef MESSAGE_H
#define MESSAGE_H

#define MECH            'M'
#define HELLOW          'h'
#define SIGNAL_M        'r'
#define ACK             'A'
#define HNDSH_R         'H'
#define HNDSH_A         'a'

#define MESSAGE_BUFF 3


struct sendMes
{
    char type;
    int signal;
    int noise;
};


struct mechMes
{
    std::string ip;    
    struct sendMes m;
};


#endif